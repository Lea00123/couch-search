#ifndef CRAWLING_BASE_H_
#define CRAWLING_BASE_H_

#include <gumbo.h>
#include <string>
#include <queue>

class CrawlingBase {
public:
    explicit CrawlingBase(std::vector<std::string> const& start_urls);
    virtual  ~CrawlingBase() = default;

    /**
     * Start the crawling process.
     */
    virtual void start_crawling() = 0;


protected:
    /**
     * Fetches the content of a given URL.
     * 
     * @param a_url The URL from which to fetch the content.
     * @return The content of the page as a string.
     */
    std::string fetch_page_content(std::string const& a_url);  

    /**
     * Parses the HTML content to extract text from specific tags.
     * 
     * @param html_content The HTML content to parse.
     * @return A vector of strings containing the text extracted from the tags: 
     *         <P>, <H1>, <H2>, <H3>, <H4>, and <TITLE>.
     */
    void parse_html(std::string const & a_html_content, std::vector<std::string>& a_words, std::vector<std::string>& a_links);

private:
    /**
     * Recursively extracts text from a GumboNode and its children.
     * 
     * @param node The GumboNode to process.
     * @param words A reference to a vector of strings where the extracted text will be stored.
     */
    void get_info(GumboNode* a_node, std::vector<std::string>& a_words, std::vector<std::string>& a_links);

    std::string extract_domain(const std::string& url);


protected:
    std::vector<std::string> m_start_urls;
};

#endif  // CRAWLING_BASE_H_