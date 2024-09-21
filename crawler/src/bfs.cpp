#include "bfs.h"
#include "crawler_config.h"
#include "parser.h"


#include <iostream>
#include <gumbo.h>
#include <algorithm>
#include <cctype>
#include <queue>

Bfs::Bfs(CrawlerConfig& a_config, Parser& a_parser)
    : CrawlingBase(a_config, a_parser)
{
}

CrawlerStats Bfs::start_crawling()
{
    std::queue<std::pair<std::string, int>> url_queue;
    std::set<std::string> visited;
    CrawlerStats statistic;

    for (const auto& url : m_config.get_start_urls()) {
        url_queue.push({url, 0});
        visited.insert(url);
    }

    int max_pages = m_config.get_max_limit_pages();
    int m_max_depth = m_config.get_max_depth();

    while (!url_queue.empty()) {
        
        //stop if we reached the max number of pages
        if (max_pages > 0 && statistic.m_pages_crawled >= max_pages) {
            break;
        }

        auto [current_url, current_depth] = url_queue.front();
        url_queue.pop();

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
                url_queue.push({link, current_depth + 1});
            }
        }
    }

    std::cout << "Crawling complete!" << std::endl;
    std::cout << "Total words indexed: " << statistic.m_total_words << std::endl;
    std::cout << "Total pages crawled: " << statistic.m_pages_crawled << std::endl;
    std::cout << "Total ignored links: " << statistic.m_ignored_links << std::endl;

    return statistic;
}

void Bfs::process_url(std::string const& a_url, std::vector<std::string>& a_words, std::vector<std::string>& a_links, int& a_ignored_links)
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


// void Bfs::extract_words(std::string const& a_words)
// {
//     std::string word;
//     for (std::string word : content) {
//         if (std::isalnum(c)) {
//             word += std::tolower(c);
//         } else if (!word.empty()) {
//             ++m_word_count[word];
//             word.clear();
//         }
//     }
//     if (!word.empty()) {
//         ++m_word_count[word];
//     }
// }


