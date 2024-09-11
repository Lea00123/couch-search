#include "crawler_mng.h"
#include "parser.h"
#include "bfs.h"
#include "dfs.h"

#include <stdexcept>

CrawlerManager::CrawlerManager(std::string const& a_filename)
    : m_config(CrawlerConfig(a_filename))
    , m_parser(Parser())
{
    create_crawler();
}

void CrawlerManager::create_crawler() {
    std::string mode = m_config.get_crawling_mode(); 

    if (mode == "BFS") {
        m_crawler = std::make_unique<Bfs>(m_config, m_parser);
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
