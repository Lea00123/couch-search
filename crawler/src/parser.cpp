#include "parser.h"
#include "gumbo.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <string>
#include <regex>
#include <algorithm>
#include <sstream>   
#include <vector>  
#include <cctype> 


using namespace curlpp::options;


std::string Parser::fetch_page_content(std::string const& a_url)
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


void Parser::parse_html(std::string const & a_html_content, std::vector<std::string>& a_words, std::vector<std::string>& a_links)
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


void Parser::get_info(GumboNode* a_node, std::vector<std::string>& a_words, std::vector<std::string>& a_links)
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
                std::vector<std::string> words = string_to_words(child->v.text.text);
                a_words.insert(a_words.end(), words.begin(), words.end());
            }
        }
    } else if (tag == GUMBO_TAG_A) {
        GumboAttribute* href = gumbo_get_attribute(&a_node->v.element.attributes, "href");
        if (href) {
            a_links.push_back(href->value);
        }
    }
   
    for (unsigned int i = 0; i < children->length; ++i) {
        GumboNode* child = static_cast<GumboNode*>(children->data[i]);
        get_info(child, a_words, a_links);
    }
} 
  

std::string Parser::extract_domain(const std::string& url)
{
    const std::regex domain_regex(R"((http[s]?:\/\/)?([^\/\s]+))");
    std::smatch match;

    if (std::regex_search(url, match, domain_regex)) {
        return match[2].str(); 
    }

    return "";
}

std::vector<std::string> Parser::string_to_words(const std::string& str)
{
    std::istringstream stream(str);
    std::string word;
    std::vector<std::string> words;

    while (stream >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), [] (unsigned char c) { 
            return !std::isalnum(c); }), word.end());

        std::transform(word.begin(), word.end(), word.begin(), 
                       [](unsigned char c) { return std::tolower(c); });

        if (!word.empty())
        {
            words.push_back(word);
        }
    }

    return words;
}
