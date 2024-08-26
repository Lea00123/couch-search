#ifndef CRAWLER_H_
#define CRAWLER_H_

#include "crawler_config.h"
#include <gumbo.h>

#include <string>
#include <queue>

class Crawler {
public:
    Crawler(CrawlerConfig const& a_config);

    /**
     * Start the crawling process.
     */
    void start_crawling();

private:
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
    std::vector<std::string> parse_html(std::string const& html_content);

    /**
     * Recursively extracts text from a GumboNode and its children.
     * 
     * @param node The GumboNode to process.
     * @param words A reference to a vector of strings where the extracted text will be stored.
     */
    void get_text(GumboNode* node, std::vector<std::string>& words);

    void crawling_bfs();
    void crawling_dfs();

    



private:
    CrawlerConfig m_config;
    std::queue<std::string> m_queue;
};

#endif  // CRAWLER_H_