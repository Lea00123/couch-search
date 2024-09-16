#ifndef CRAWLING_BASE_
#define CRAWLING_BASE_

#include "crawler_config.h"
#include "parser.h"
#include <gumbo.h>
#include <string>
#include <queue>

struct CrawlerStats {
    int m_total_words = 0;
    int m_pages_crawled = 0;
    int m_ignored_links = 0;
};

class CrawlingBase  {
public:
    virtual ~CrawlingBase() {}
    virtual CrawlerStats start_crawling() = 0;
};


#endif  // CRAWLING_BASE_