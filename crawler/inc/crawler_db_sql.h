// crawler_db_sql.h
#ifndef CRAWLER_DB_SQL_H_
#define CRAWLER_DB_SQL_H_

#include "crawler_db_base.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class MockMYSQL;  // Forward declaration of your mock database class

class CrawlerDBSQL : public CrawlerDBBase {
public:
    CrawlerDBSQL(const std::string& a_connection_string);
    ~CrawlerDBSQL() override;

    void read_DB() override;
    // Missing update_links_map method implementation
    void update_words_map(const std::string& a_word, const std::map<std::string, int>& a_urls_count) override;
    void write_DB() override;
    bool is_visited(const std::string& url) const override;
    std::map<std::string, std::map<std::string, int>> get_links_map() const override;
    std::map<std::string, std::map<std::string, int>> get_words_map() const override;
    std::vector<std::string> get_query_results(const std::string& query, int max_url) const override;
};


#endif  // CRAWLER_DB_SQL_H_
