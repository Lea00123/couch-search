#include "crawler_db.h"
#include <iostream>
#include <fstream>


CrawlerDB::CrawlerDB()
    : m_database_links("/tmp/links.txt"), m_database_words("/tmp/words.txt")
{
    read_DB();
}

CrawlerDB& CrawlerDB::get_instance() 
{
    static CrawlerDB instance;
    return instance;
}

void CrawlerDB::write_DB() 
{
    write_map_to_file(m_database_links, m_links_map);
    write_map_to_file(m_database_words, m_words_map);
}


void CrawlerDB::read_DB() 
{
    m_links_map.clear();
    m_words_map.clear();
    read_map_from_file(m_database_links, m_links_map);
    read_map_from_file(m_database_words, m_words_map);
}


void CrawlerDB::update_links_map(const std::string& a_url, const std::map<std::string, int>& a_links_count)
{
    m_links_map[a_url] = a_links_count;
}


void CrawlerDB::update_words_map(const std::string& a_word, const std::map<std::string, int>& a_urls_count)
{
    m_words_map[a_word] = a_urls_count;
}


bool CrawlerDB::is_visited(const std::string& url) const
{
    return m_links_map.find(url)!= m_links_map.end();
}


std::map<std::string, std::map<std::string, int>> CrawlerDB::get_links_map() const
{
    return m_links_map;
}


std::map<std::string, std::map<std::string, int>> CrawlerDB::get_words_map() const
{
    return m_words_map;
}


void CrawlerDB::write_map_to_file(const std::string& a_filename, const std::map<std::string, std::map<std::string, int>>& a_data_map)
{
    std::ofstream outFile(a_filename); 

    if (!outFile) {
        std::cerr << "Error opening file for writing: " << a_filename << std::endl;
        return;
    }

    for (const auto& entry : a_data_map) {
        outFile << entry.first << "\n";
        for (const auto& item : entry.second) {
            outFile << item.first << ": " << item.second << "\n";
        }
        outFile << "\n";
    }

    outFile.close();    
}


void CrawlerDB::read_map_from_file(const std::string& a_filename, std::map<std::string, std::map<std::string, int>>& a_data_map)
{
    std::ifstream inFile(a_filename);

    if (!inFile) {
        return;
    }

    std::string key;
    while (std::getline(inFile, key)) {
        std::map<std::string, int> inner_map;   
        std::string line;

        // Read the inner map until the next key or EOF
        while (std::getline(inFile, line) && !line.empty()) {
            size_t colon_pos = line.find(": ");
            if (colon_pos != std::string::npos) {
                std::string item_key = line.substr(0, colon_pos);
                int count = std::stoi(line.substr(colon_pos + 1));
                inner_map[item_key] = count;
            }
        }

        a_data_map[key] = inner_map;
    }

    inFile.close();
}   