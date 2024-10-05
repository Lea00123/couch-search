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
    CrawlerDB& crawler_db = CrawlerDB::get_instance();

    if (mode == "BFS") {
        m_crawler = std::make_unique<Bfs>(m_config, m_parser, crawler_db);
    } else if (mode == "DFS") {
        m_crawler = std::make_unique<Dfs>(m_config, m_parser, crawler_db);
    } else {
        throw std::runtime_error("Unknown crawling mode: " + mode);
    }
}

CrawlerStats CrawlerManager::start_crawling()
{
    if (m_crawler) {
        return m_crawler->start_crawling();
    }

    return CrawlerStats();
}
