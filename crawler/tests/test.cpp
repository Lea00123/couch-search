#include "crawler_mng.h"

int main()
{
    CrawlerManager manager("../config.json");

    manager.start_crawling();
    

    return 0;
}