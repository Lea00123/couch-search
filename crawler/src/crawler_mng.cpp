#include "crawler_mng.h"
#include "parser.h"
#include "bfs.h"
#include "dfs.h"
#include "crawler_db_file.h"  
#include "crawler_db_sql.h"  

#include <stdexcept>

CrawlerManager::CrawlerManager(std::string const& a_filename)
    : m_config(CrawlerConfig(a_filename))
    , m_parser(Parser())
{
    create_crawler();
}

void CrawlerManager::create_crawler() {
    std::string mode = m_config.get_crawling_mode();
    std::string db_type = m_config.get_database_type(); 
    CrawlerDBBase* crawler_db = nullptr;

    if (db_type == "FILE") {
        // std::string links_file = "links.txt"; 
        // std::string words_file = "words.txt"; 
        crawler_db = &CrawlerDBFile::get_instance();
    // } else if (db_type == "MYSQL") {
    //     std::string sql_connection_string = "crawler_db"; 
    //     crawler_db = &CrawlerDBSQL::get_instance(sql_connection_string); 
    } else {
        throw std::runtime_error("Unknown database type: " + db_type);
    }

    // Pass crawler_db directly as a pointer
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
