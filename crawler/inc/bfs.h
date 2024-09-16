#ifndef BFS_H_
#define BFS_H_

#include "crawling_base.h"

#include <queue> 
#include <vector>
#include <set>

class Bfs : public CrawlingBase {
public:
    Bfs(CrawlerConfig& a_config, Parser& a_parser);
    CrawlerStats start_crawling() override;

private:
    void process_url(std::string const& a_url, std::vector<std::string>& a_words, std::vector<std::string>& a_links, int& a_ignored_links);

private:
    CrawlerConfig& m_config;
    Parser& m_parser;
};


#endif // BFS_H_
