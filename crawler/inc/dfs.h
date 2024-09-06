#ifndef DFS_H_
#define DFS_H_

#include "crawling_base.h"
#include <vector>

class Dfs : public CrawlingBase {
public:
    Dfs(CrawlerConfig const& a_config);
    void start_crawling() override;

private:


private:
    std::vector<std::vector<int>> adjacencyist;
    std::vector<bool> visited;
};


#endif // DFS_H