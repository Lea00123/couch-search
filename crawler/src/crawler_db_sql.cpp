#include "crawler_db_sql.h"
#include <stdexcept>
#include <iostream>
#include <memory>
#include <map>
#include <vector>

class MockMYSQL {
public:
    void init() {
        std::cout << "Mock MySQL initialized.\n";
    }
};

CrawlerDBSQL::CrawlerDBSQL(const std::string& a_connection_string)
    : m_connection_string(a_connection_string),
      m_connection(std::make_unique<MockMYSQL>()) { // Initialize with unique_ptr
    m_connection->init(); // Call mock init
    std::cout << "Connected to database (mock)\n";
}

CrawlerDBSQL::~CrawlerDBSQL() {
    if (m_connection) {
        std::cout << "Database connection closed (mock)\n";
    }
}

void CrawlerDBSQL::read_DB() {
    std::cout << "Reading from database (mock)... (no actual data)\n";
}

void CrawlerDBSQL::update_links_map(const std::string& a_url, const std::map<std::string, int>& a_links_count) {
    for (const auto& [link, count] : a_links_count) {
        // Simulate a query for links
        std::string query = "INSERT INTO links (url, count) VALUES ('" + link + "', " + std::to_string(count) + ")";
        execute_query(query);
        std::cout << "Inserted link: " << link << " with count: " << count << " into the database.\n";
    }
    m_links_map[a_url] = a_links_count; // Update the internal map
}

void CrawlerDBSQL::update_words_map(const std::string& a_word, const std::map<std::string, int>& a_urls_count) {
    for (const auto& [url, count] : a_urls_count) {
        // Simulate a query for words
        std::string query = "INSERT INTO words (word, url, count) VALUES ('" + a_word + "', '" + url + "', " + std::to_string(count) + ")";
        execute_query(query);
        std::cout << "Inserted word: " << a_word << " with url: " << url << " and count: " << count << " into the database.\n";
    }
    m_words_map[a_word] = a_urls_count; // Update the internal map
}

void CrawlerDBSQL::write_DB() {
    std::cout << "Writing to database (mock)\n";
}

bool CrawlerDBSQL::is_visited(const std::string& url) const {
    // Mock behavior for checking if a URL has been visited
    return m_links_map.find(url) != m_links_map.end();
}

std::map<std::string, std::map<std::string, int>> CrawlerDBSQL::get_links_map() const {
    return m_links_map;
}

std::map<std::string, std::map<std::string, int>> CrawlerDBSQL::get_words_map() const {
    return m_words_map;
}

std::vector<std::string> CrawlerDBSQL::get_query_results(const std::string& query, int max_url) const {
    // Return a mock result
    std::cout << "Executing query (mock): " << query << std::endl;
    return { "mock_result1", "mock_result2" }; // Placeholder
}

void CrawlerDBSQL::execute_query(const std::string& query) {
    // Simulate executing a query
    if (query.empty()) {
        throw std::runtime_error("Query is empty");
    }
    std::cout << "Executing query (mock): " << query << std::endl;
}

CrawlerDBSQL& CrawlerDBSQL::get_instance() {
    static CrawlerDBSQL instance("mock_connection_string");
    return instance;
}
