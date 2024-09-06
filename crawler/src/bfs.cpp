#include "bfs.h"

#include <iostream>
#include <gumbo.h>
#include <algorithm>
#include <cctype>
#include <queue>

Bfs::Bfs(std::vector<std::string> const& a_start_urls, int a_max_depth, int a_max_pages)
    : CrawlingBase(a_start_urls)
    , m_max_depth(a_max_depth)
    , m_max_pages(a_max_pages)
{
}

void Bfs::start_crawling()
{
    std::queue<std::pair<std::string, int>> url_queue;
    std::set<std::string> visited;
    int pages_crawled = 0;

    for (const auto& url : m_start_urls) {
        url_queue.push({url, 0});
        visited.insert(url);
    }

    while (!url_queue.empty()) {
        
        //stop if we reached the max number of pages
        if (m_max_pages > 0 && pages_crawled >= m_max_pages) {
            break;
        }

        auto [current_url, current_depth] = url_queue.front();
        url_queue.pop();

        if (current_depth >= m_max_depth) {
            continue;
        }

        std::vector<std::string> m_words;
        std::vector<std::string> m_links;

        process_url(current_url, m_words, m_links);
        ++pages_crawled;

        for (const auto& link : m_links) {
            if (visited.find(link) == visited.end()) {
                visited.insert(link);
                url_queue.push({link, current_depth + 1});
            }
        }
    }
}

void Bfs::process_url(std::string const& url, std::vector<std::string>& m_words, std::vector<std::string>& m_links)
{
    std::string content = fetch_page_content(url);
    if (content.empty()) {
        std::cerr << "Failed to fetch or empty content for URL: " << url << std::endl;
        return;
    }
    
    parse_html(content, m_words, m_links);
    //TODO: update url to words count and url to links count
}

void Bfs::extract_words(std::string const& a_words)
{
    std::string word;
    for (std::string word : content) {
        if (std::isalnum(c)) {
            word += std::tolower(c);
        } else if (!word.empty()) {
            ++m_word_count[word];
            word.clear();
        }
    }
    if (!word.empty()) {
        ++m_word_count[word];
    }
}


