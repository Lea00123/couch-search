#ifndef CRAWLING_BASE_
#define CRAWLING_BASE_

#include <gumbo.h>
#include <string>
#include <queue>

class CrawlingBase  {
public:
    virtual ~CrawlingBase() {}
    virtual void start_crawling() = 0;
};

#endif  // CRAWLING_BASE_