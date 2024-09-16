#ifndef CRAWLER_MNG_H_
#define CRAWLER_MNG_H_

#include "crawler_config.h"
#include "crawling_base.h"
#include "parser.h"
#include <memory>

class CrawlerManager {
public:
    CrawlerManager(std::string const& a_filename);

    // Starts the crawling process
    CrawlerStats start_crawling();

private:
    CrawlerConfig m_config;
    std::unique_ptr<CrawlingBase> m_crawler;
    Parser m_parser;
    
    void create_crawler();
};

#endif // CRAWLER_MANAGER_H_

