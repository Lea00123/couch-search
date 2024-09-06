#include "crawler_mng.h"

int main()
{
    CrawlerConfig config("../config.json");
    CrawlerManager manager(config);

    manager.start_crawling();
    

    return 0;
}