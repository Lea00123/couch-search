#ifndef BFS_H_
#define BFS_H_

#include "crawling_base.h"
#include <queue> 
#include <vector>
#include <set>

class Bfs : public CrawlingBase {
public:
    Bfs(std::vector<std::string> const& start_urls, int a_maxm_depth, int a_max_pages);
    void start_crawling() override;

private:
    void process_url(std::string const& url, std::vector<std::string>& m_words, std::vector<std::string>& m_links);

private:
    int m_max_depth;
    int m_max_pages;
};


#endif // BFS_H_
