#ifndef CRAWLING_BASE_
#define CRAWLING_BASE_

#include "crawler_config.h"
#include "crawler_db.h"
#include "parser.h"
#include <gumbo.h>
#include <string>
#include <queue>

struct CrawlerStats {
    int m_total_words = 0;
    int m_pages_crawled = 0;
    int m_ignored_links = 0;
};

class CrawlingBase {
public:
    CrawlingBase(CrawlerConfig& a_config, Parser& a_parser, CrawlerDB& a_crawler_db)
    : m_config(a_config), m_parser(a_parser), m_crawler_db(a_crawler_db) {}

    virtual ~CrawlingBase() {}
    virtual CrawlerStats start_crawling() = 0;

protected:
    CrawlerConfig& m_config;
    Parser& m_parser;
    CrawlerDB& m_crawler_db;
};


#endif  // CRAWLING_BASE_