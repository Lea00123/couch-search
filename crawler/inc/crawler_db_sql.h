#ifndef CRAWLER_DB_SQL_H_
#define CRAWLER_DB_SQL_H_

#include "crawler_db_base.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

class CrawlerDBMySQL : public CrawlerDBBase {
public:
    CrawlerDBMySQL();
    virtual ~CrawlerDBMySQL();

    void read_DB();
    void write_DB();
    void populate_map(const std::string& query, const std::string& a_key,
                      const std::string& a_first_value, const std::string& a_second_value_count,
                      std::map<std::string, std::map<std::string, int>>& map);
    void write_links_to_DB(const std::map<std::string, std::map<std::string, int>>& map);
    void write_to_DB(const std::map<std::string, std::map<std::string, int>>& map,
                     const std::string& table_name, const std::string& key_column, const std::string& value_column);
    
    // Declare member variables
    sql::mysql::MySQL_Driver* driver; // Add this line
    sql::Connection* con; 
    std::map<std::string, std::map<std::string, int>> m_links_map;
    std::map<std::string, std::map<std::string, int>> m_words_map;
};



#endif  // CRAWLER_DB_SQL_H_
