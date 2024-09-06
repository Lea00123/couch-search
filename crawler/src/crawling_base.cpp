#include "crawling_base.h"
#include "gumbo.h"

#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <string>
#include <regex>


using namespace curlpp::options;

CrawlingBase::CrawlingBase(std::vector<std::string> const& start_urls)
    : m_start_urls(start_urls)
{
}


std::string CrawlingBase::fetch_page_content(std::string const& a_url)
{
    try {
        curlpp::Easy my_request;
        my_request.setOpt<curlpp::options::Url>(a_url);

        std::ostringstream os;
        os << my_request;       
        return os.str();
        
    } catch(curlpp::RuntimeError &e) {
		std::cout << e.what() << std::endl;
	} catch(curlpp::LogicError &e) {
		std::cout << e.what() << std::endl;
	}

    return "";
}


void CrawlingBase::parse_html(std::string const & a_html_content, std::vector<std::string>& a_words, std::vector<std::string>& a_links)
{
    
    if (a_html_content.empty()) {
        std::cerr << "Error: Empty HTML content." << std::endl;
        return;
    }

    GumboOutput* output = gumbo_parse(a_html_content.c_str());
    if (!output) {
        std::cerr << "Error: Failed to parse HTML." << std::endl;
        return;
    }

    get_info(output->root, a_words, a_links);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
}


void CrawlingBase::get_info(GumboNode* a_node, std::vector<std::string>& a_words, std::vector<std::string>& a_links)
{
    if (a_node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
    
    GumboTag tag = a_node->v.element.tag;  
    GumboVector* children = &a_node->v.element.children;

    if (tag == GUMBO_TAG_P || tag == GUMBO_TAG_H1 || tag == GUMBO_TAG_H2 ||
        tag == GUMBO_TAG_H3 || tag == GUMBO_TAG_H4 || tag == GUMBO_TAG_TITLE) {

        for (unsigned int i = 0; i < children->length; ++i) {
            GumboNode* child = static_cast<GumboNode*>(children->data[i]);
            if (child->type == GUMBO_NODE_TEXT && child->v.text.text) {
                a_words.push_back(std::string(child->v.text.text));
            }
        }
    } else if (tag == GUMBO_TAG_A) {
        GumboAttribute* href = gumbo_get_attribute(&a_node->v.element.attributes, "href");
        if (href) {
            std::string link_domain = extract_domain(href->value);
            std::string start_domain = extract_domain(m_start_urls[0]);

            if (link_domain == start_domain) {
                a_links.push_back(href->value);
            } 
        }
    }
   
    for (unsigned int i = 0; i < children->length; ++i) {
        GumboNode* child = static_cast<GumboNode*>(children->data[i]);
        get_info(child, a_words, a_links);
    }
}   

std::string CrawlingBase::extract_domain(const std::string& url)
{
    const std::regex domain_regex(R"((http[s]?:\/\/)?([^\/\s]+))");
    std::smatch match;

    if (std::regex_search(url, match, domain_regex)) {
        return match[2].str(); 
    }
    return "";
}

