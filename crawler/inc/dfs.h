#ifndef DFS_H_
#define DFS_H_

#include "crawling_base.h"
#include "crawler_config.h"  
#include "parser.h"        
#include "crawler_db.h"      

#include <vector>
#include <string>

class Dfs : public CrawlingBase {
public:
    Dfs(CrawlerConfig& a_config, Parser& a_parser, CrawlerDB& a_crawler_db);
    CrawlerStats start_crawling() override;

private:
    void process_url(std::string const& a_url, std::vector<std::string>& a_words, std::vector<std::string>& a_links, int& a_ignored_links);
};

#endif // DFS_H_
