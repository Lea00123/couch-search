#ifndef DFS_H_
#define DFS_H_

#include "crawling_base.h"

#include <vector>

class Dfs : public CrawlingBase {
public:
    Dfs(CrawlerConfig& a_config, Parser& a_parser);
    CrawlerStats start_crawling() override;

private:
    void process_url(std::string const& a_url, std::vector<std::string>& a_words, std::vector<std::string>& a_links, int& a_ignored_links);
};


#endif // DFS_H