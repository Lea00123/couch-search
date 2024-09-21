#include "crawler_mng.h"
#include <cassert>
#include <iostream>

int main()
{
    CrawlerManager manager_bfs("../config_test_bfs.json");
    CrawlerManager manager_dfs("../config_test_dfs.json");
    
    CrawlerStats statistic_bfs = manager_bfs.start_crawling();
    CrawlerStats statistic_dfs = manager_dfs.start_crawling();

    // assert(statistic_bfs.m_ignored_links == statistic_dfs.m_ignored_links);
    assert(statistic_bfs.m_pages_crawled == 164);
    assert(statistic_bfs.m_pages_crawled == statistic_dfs.m_pages_crawled);

    // assert(statistic_bfs.m_total_words == 460689);
    assert(statistic_bfs.m_total_words == statistic_dfs.m_total_words);

    std::cout << "All test cases passed!" << std::endl;

    return 0;
}