#include "crawler_mng.h"
#include "crawler_db.h"
#include <cassert>
#include <iostream>
#include <fstream>

void print_map(const std::map<std::string, std::map<std::string, int>>& data_map) {
    for (const auto& outer_entry : data_map) {
        std::cout << outer_entry.first << ":\n"; // Print the key of the outer map
        for (const auto& inner_entry : outer_entry.second) {
            std::cout << "  " << inner_entry.first << ": " << inner_entry.second << "\n"; // Print inner map key-value pairs
        }
        std::cout << "\n"; // Extra line for better readability
    }
}


bool file_exists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}


void TestCrawler()
{
    CrawlerManager manager_bfs("../config_test_bfs.json");
    CrawlerManager manager_dfs("../config_test_dfs.json");
    
    CrawlerStats statistic_bfs = manager_bfs.start_crawling();
    CrawlerStats statistic_dfs = manager_dfs.start_crawling();

    // assert(statistic_bfs.m_ignored_links == statistic_dfs.m_ignored_links);
    assert(statistic_bfs.m_pages_crawled == 164);
    assert(statistic_bfs.m_pages_crawled == statistic_dfs.m_pages_crawled);

    // assert(statistic_bfs.m_total_words == 460689);
    // assert(statistic_bfs.m_total_words == statistic_dfs.m_total_words);

    
}

void TestDB()
{
   std::string filename_link =  "/tmp/links.txt";
    std::string filename_word = "/tmp/words.txt";

    if(file_exists(filename_link))
    {
        std::remove(filename_link.c_str());
    }

    if(file_exists(filename_word))
    {
        std::remove(filename_word.c_str());
    }

    CrawlerDB db(filename_link, filename_word);

    std::map<std::string, std::map<std::string, int>> links_map = {
        {"http://example.com", {{"page1", 1}, {"page2", 2}}},
        {"http://example.org", {{"page3", 3}, {"page4", 4}}}
    };

    // Corrected initialization for words_map
    std::map<std::string, std::map<std::string, int>> words_map = {
        {"Hello", {{"http://www.lea.co.il", 1}, {"http://www.lea2.co.il", 2}}},
        {"Eyal", {{"http://example3.org", 3}, {"http://example4.org", 4}}}
    };
    
    for (const auto& item : links_map)
    {
        db.update_links_map(item.first, item.second);
    }

    for (const auto& item : words_map)
    {
        db.update_words_map(item.first, item.second);
    }

    std::map<std::string, std::map<std::string, int>> result_links_map;
    std::map<std::string, std::map<std::string, int>> result_words_map;

    db.write_DB();
    db.read_DB();

    // Check if the read maps match the original maps
    result_links_map = db.get_links_map(); 
    result_words_map = db.get_words_map();

    // Print the results
    std::cout << "Expected Words Map:\n";
    print_map(words_map);

    std::cout << "\nResult Words Map:\n";
    print_map(result_words_map);

    std::cout << "\nExpected Links Map:\n";
    print_map(links_map);

    std::cout << "\nResult Links Map:\n";
    print_map(result_links_map);

    // Assert links_map equals result_links_map
    assert(links_map == result_links_map && "Links map does not match expected result");

    // Assert words_map equals result_words_map
    assert(words_map == result_words_map && "Words map does not match expected result");
}

int main()
{
    //TestCrawler();
    TestDB();

    std::cout << "All test cases passed!" << std::endl;

    return 0;
}