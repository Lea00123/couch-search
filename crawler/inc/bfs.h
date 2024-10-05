#ifndef BFS_H_
#define BFS_H_

#include "crawling_base.h"
#include "crawler_db_base.h"

#include <queue>
#include <vector>
#include <set>

class Bfs : public CrawlingBase {
public:
    Bfs(CrawlerConfig& a_config, Parser& a_parser, CrawlerDBBase* a_crawler_db);
    CrawlerStats start_crawling() override;

private:
    void process_url(std::string const& a_url, std::vector<std::string>& a_words, std::vector<std::string>& a_links, int& a_ignored_links);
};

#endif // BFS_H_
