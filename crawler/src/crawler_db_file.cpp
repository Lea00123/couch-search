#include "crawler_db_file.h"
#include <sstream>

CrawlerDBFile::CrawlerDBFile()
    : m_database_links("/tmp/words.txt"), m_database_words("/tmp/links.txt") {
    read_DB();
}

void CrawlerDBFile::read_DB() {
    m_links_map.clear();
    m_words_map.clear();
    read_map_from_file(m_database_links, m_links_map);
    read_map_from_file(m_database_words, m_words_map);
}

void CrawlerDBFile::update_links_map(const std::string& a_url, const std::map<std::string, int>& a_links_count) {
    m_links_map[a_url] = a_links_count;
}

void CrawlerDBFile::update_words_map(const std::string& a_word, const std::map<std::string, int>& a_urls_count) {
    m_words_map[a_word] = a_urls_count;
}

void CrawlerDBFile::write_DB() {
    write_map_to_file(m_database_links, m_links_map);
    write_map_to_file(m_database_words, m_words_map);
}

bool CrawlerDBFile::is_visited(const std::string& url) const {
    return m_links_map.find(url) != m_links_map.end();
}

std::map<std::string, std::map<std::string, int>> CrawlerDBFile::get_links_map() const {
    return m_links_map;
}

std::map<std::string, std::map<std::string, int>> CrawlerDBFile::get_words_map() const {
    return m_words_map;
}

std::vector<std::string> CrawlerDBFile::get_query_results(const std::string& query, int max_url) const {
    // Add custom query logic here
    return {};
}

void CrawlerDBFile::write_map_to_file(const std::string& filename, const std::map<std::string, std::map<std::string, int>>& map_data) {
    std::ofstream file(filename);
    if (!file) return;
    for (const auto& pair : map_data) {
        file << pair.first << "\n";
        for (const auto& inner_pair : pair.second) {
            file << inner_pair.first << ": " << inner_pair.second << "\n";
        }
        file << "\n";
    }
}

void CrawlerDBFile::read_map_from_file(const std::string& filename, std::map<std::string, std::map<std::string, int>>& map_data) {
    std::ifstream file(filename);
    if (!file) return;
    std::string line;
    std::string key;
    while (std::getline(file, key)) {
        std::map<std::string, int> inner_map;
        while (std::getline(file, line) && !line.empty()) {
            auto pos = line.find(": ");
            if (pos != std::string::npos) {
                std::string item_key = line.substr(0, pos);
                int count = std::stoi(line.substr(pos + 2));
                inner_map[item_key] = count;
            }
        }
        map_data[key] = inner_map;
    }
}

// Implementation of the singleton instance
CrawlerDBFile& CrawlerDBFile::get_instance() {
    static CrawlerDBFile instance;
    return instance;
}
