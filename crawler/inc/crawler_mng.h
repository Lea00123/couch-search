#ifndef CRAWLER_MNG_H_
#define CRAWLER_MNG_H_

#include "crawler_config.h"
#include "crawling_base.h"
#include <memory>

class CrawlerManager {
public:
    CrawlerManager(CrawlerConfig const& config);

    // Starts the crawling process
    void start_crawling();

private:
    CrawlerConfig const& m_config;
    std::unique_ptr<CrawlingBase> m_crawler;
    
    void create_crawler();
};

#endif // CRAWLER_MANAGER_H_
