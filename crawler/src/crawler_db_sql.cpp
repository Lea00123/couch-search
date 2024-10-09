#include "crawler_db_sql.h"
#include <stdexcept>
#include <iostream>
#include <memory>
#include <map>
#include <vector>

CrawlerDBMySQL::CrawlerDBMySQL() 
{
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "user", "password");
    con->setSchema("crawler_db");
}

CrawlerDBMySQL::~CrawlerDBMySQL() 
{
    delete con;
}


void CrawlerDBMySQL::read_DB() 
{
    // Read links
    const std::string link_query = "SELECT source_link_id, linked_link_id, count FROM link_link_counts";
    populate_map(link_query, "source_link_id", "linked_link_id", "count", m_links_map);

    // Read words
    const std::string word_query = "SELECT url, word, count FROM link_word_counts";
    populate_map(word_query, "url", "word", "count", m_words_map);
}


// void CrawlerDBFile::update_links_map(const std::string& a_url, const std::map<std::string, int>& a_links_count) {
//     m_links_map[a_url] = a_links_count;
// }


// void CrawlerDBFile::update_words_map(const std::string& a_word, const std::map<std::string, int>& a_urls_count) {
//     m_words_map[a_word] = a_urls_count;
// }



void CrawlerDBMySQL::write_DB() 
{
    // Use the consolidated function to write links and words
    write_to_DB(m_links_map, "link_link_counts", "source_link_id", "linked_link_id");
    write_to_DB(m_words_map, "link_word_counts", "url", "word");
}


void CrawlerDBMySQL::populate_map(const std::string& query,
                                   const std::string& a_key,
                                   const std::string& a_first_value,
                                   const std::string& a_second_value_count,
                                   std::map<std::string, std::map<std::string, int>>& map)
{
    sql::Statement* stmt = con->createStatement();
    sql::ResultSet* res = stmt->executeQuery(query);

    while (res->next()) {
        std::string key = res->getString(a_key);
        std::string value = res->getString(a_first_value);
        int count = res->getInt(a_second_value_count);

        map[key][value] = count;
    }

    delete res;
    delete stmt;
}


void CrawlerDBMySQL::write_to_DB(const std::map<std::string, std::map<std::string, int>>& map, 
                                   const std::string& table_name, 
                                   const std::string& key_column, 
                                   const std::string& value_column) 
{
    
    const std::string query = "INSERT INTO " + table_name + " (" + key_column + ", " + value_column + ", count) "
                              "VALUES (?, ?, ?) ON DUPLICATE KEY UPDATE count = ?";

    sql::PreparedStatement* pstmt = con->prepareStatement(query);

    for (const auto& [key, value_map] : map) {
        for (const auto& [value, count] : value_map) {
            pstmt->setString(1, key);
            pstmt->setString(2, value);
            pstmt->setInt(3, count);
            pstmt->setInt(4, count);

            pstmt->executeUpdate();
        }
    }

    delete pstmt;
}






