#include "dfs.h"
#include <iostream>
#include <stack>
#include <set>

Dfs::Dfs(CrawlerConfig& a_config, Parser& a_parser)
    : CrawlingBase(a_config, a_parser)
{
}

CrawlerStats Dfs::start_crawling()
{
    std::stack<std::pair<std::string, int>> url_stack;
    std::set<std::string> visited;
    CrawlerStats statistic;

    for (const auto& url : m_config.get_start_urls()) {
        url_stack.push({url, 0});
        visited.insert(url);
    }

    int max_pages = m_config.get_max_limit_pages();
    int m_max_depth = m_config.get_max_depth();

    while (!url_stack.empty()) {
    
        //stop if we reached the max number of pages
        if (max_pages > 0 && statistic.m_pages_crawled >= max_pages) {
            break;
        }

        auto [current_url, current_depth] = url_stack.top();
        url_stack.pop();

        if (current_depth >= m_max_depth) {
            continue;
        }

        std::vector<std::string> words;
        std::vector<std::string> links;

        process_url(current_url, words, links, statistic.m_ignored_links);
        ++statistic.m_pages_crawled;
        statistic.m_total_words += words.size();

        for (const auto& link : links) {
            if (visited.find(link) == visited.end()) {
                visited.insert(link);
                url_stack.push({link, current_depth + 1});
            }
        }
    }

    std::cout << "Crawling complete!" << std::endl;
    std::cout << "Total words indexed: " << statistic.m_total_words << std::endl;
    std::cout << "Total pages crawled: " << statistic.m_pages_crawled << std::endl;
    std::cout << "Total ignored links: " << statistic.m_ignored_links << std::endl;

    return statistic;
}

void Dfs::process_url(std::string const& a_url, std::vector<std::string>& a_words, std::vector<std::string>& a_links, int& a_ignored_links)
{
    std::string content = m_parser.fetch_page_content(a_url);
    std::vector<std::string> all_links;
    std::string start_domain = m_parser.extract_domain(a_url);

    if (content.empty()) {
        return;
    }
    

    m_parser.parse_html(content, a_words, all_links);

    for (std::string link : all_links) {
        std::string link_domain = m_parser.extract_domain(link);

        if (link_domain == start_domain) {
            a_links.push_back(link);
        } else {
            ++a_ignored_links;
        }
    }
    //TODO: update url to words count and url to links count
}