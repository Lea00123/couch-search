#include "crawler.h"

#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include "gumbo.h"

using namespace curlpp::options;

Crawler::Crawler(CrawlerConfig const& a_config)
: m_config(a_config)
{
}


std::string Crawler::fetch_page_content(std::string const& a_url)
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


std::vector<std::string> Crawler::parse_html(std::string const & a_html_content)
{
    std::vector<std::string> words;
    GumboOutput* output = gumbo_parse(a_html_content.c_str());
    get_text(output->root, words);
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    return words;
}


void Crawler::get_text(GumboNode* a_node, std::vector<std::string>& a_words)
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

            get_text(child, a_words);
        }
    } else {
        for (unsigned int i = 0; i < children->length; ++i) {
            GumboNode* child = static_cast<GumboNode*>(children->data[i]);
            get_text(child, a_words);
        }
    }
     
}

