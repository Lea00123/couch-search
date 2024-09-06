#include "crawler_mng.h"
#include "bfs.h"
#include "dfs.h"

#include <stdexcept>

CrawlerManager::CrawlerManager(CrawlerConfig const& config)
: m_config(config)
{
    create_crawler();
}

void CrawlerManager::create_crawler() {
    std::string mode = m_config.get_crawling_mode(); 
    std::vector<std::string> start_urls = m_config.get_start_urls();  
    int max_depth = m_config.get_max_depth();
    int max_pages = m_config.get_max_limit_pages();

    if (mode == "BFS") {
        m_crawler = std::make_unique<Bfs>(start_urls, max_depth, max_pages);
    } else if (mode == "DFS") {
        // m_crawler = std::make_unique<Dfs>(start_urls);
    } else {
        throw std::runtime_error("Unknown crawling mode: " + mode);
    }
}

void CrawlerManager::start_crawling()
{
    if (m_crawler) {
        m_crawler->start_crawling();
    }
}
