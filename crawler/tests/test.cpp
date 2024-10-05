#include "crawler_mng.h"
#include "crawler_db_base.h"
#include "crawler_db_file.h"
#include "crawler_db_sql.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <map>

// Utility functions for testing
void remove_if_file_exists(const std::string& filename) {
    if (std::ifstream file(filename); file.good()) {
        std::remove(filename.c_str());
    }
}

void print_map(const std::map<std::string, std::map<std::string, int>>& data_map)
{
    for (const auto& outer_entry : data_map) {
        std::cout << outer_entry.first << ":\n";
        for (const auto& inner_entry : outer_entry.second) {
            std::cout << "  " << inner_entry.first << ": " << inner_entry.second << "\n"; 
        }
        std::cout << "\n";
    }
}


// Tests    
TEST(CrawlerTest, TestCrawlerBFSWordsFile) {
    CrawlerManager manager_bfs("../config_test_bfs.json");
    std::string filename_link = "/tmp/links.txt";
    std::string filename_word = "/tmp/words.txt";

    remove_if_file_exists(filename_link);
    remove_if_file_exists(filename_word);

    CrawlerStats statistic_bfs = manager_bfs.start_crawling();

    CrawlerDBBase& db  = CrawlerDBFile::get_instance();
    std::map<std::string, std::map<std::string, int>> result_words_map = db.get_words_map();

    // Define expected results for testing
     std::map<std::string, std::map<std::string, int>> expected_results = {
        {"https://harrypotter.fandom.com/oc/wiki/", {{"a", 2}, {"advertise", 1}, {"apps", 1}, {"community", 3}}},
        {"https://harrypotter.fandom.com/wiki/Abraham_Ronen", {{"a", 21}, {"about", 2}, {"abraham", 5}}},
    };

    for (const auto& [expected_url, expected_word_counts] : expected_results) {
        auto it = result_words_map.find(expected_url);
        ASSERT_NE(it, result_words_map.end()) << "Expected URL '" << expected_url << "' not found.";
            
        const auto& actual_word_counts = it->second;

        // Check if the actual word counts match the expected word counts
        for (const auto& [word, count] : expected_word_counts) {
            auto actual_it = actual_word_counts.find(word);
            ASSERT_NE(actual_it, actual_word_counts.end()) << "Expected word '" << word << "' for URL '" << expected_url << "' not found.";
            ASSERT_EQ(actual_it->second, count) << "For URL '" << expected_url << "', expected count for word '" << word 
                << "' is " << count << ", but found " << actual_it->second << ".";
        }
    }

     ASSERT_EQ(statistic_bfs.m_pages_crawled, 164);
}

TEST(CrawlerTest, TestCrawlerDFSWords) {
    CrawlerManager manager_dfs("../config_test_dfs.json");
    std::string filename_link = "/tmp/links.txt";
    std::string filename_word = "/tmp/words.txt";

    remove_if_file_exists(filename_link);
    remove_if_file_exists(filename_word);

    CrawlerDBBase& db  = CrawlerDBFile::get_instance();
    std::map<std::string, std::map<std::string, int>> result_words_map = db.get_words_map();

    // Define expected results for testing
     std::map<std::string, std::map<std::string, int>> expected_results = {
        {"https://harrypotter.fandom.com/oc/wiki/", {{"a", 2}, {"advertise", 1}, {"apps", 1}, {"community", 3}}},
        {"https://harrypotter.fandom.com/wiki/Abraham_Ronen", {{"a", 21}, {"about", 2}, {"abraham", 5}}},
    };

    for (const auto& [expected_url, expected_word_counts] : expected_results) {
        auto it = result_words_map.find(expected_url);
        ASSERT_NE(it, result_words_map.end()) << "Expected URL '" << expected_url << "' not found.";
            
        const auto& actual_word_counts = it->second;

        // Check if the actual word counts match the expected word counts
        for (const auto& [word, count] : expected_word_counts) {
            auto actual_it = actual_word_counts.find(word);
            ASSERT_NE(actual_it, actual_word_counts.end()) << "Expected word '" << word << "' for URL '" << expected_url << "' not found.";
            ASSERT_EQ(actual_it->second, count) << "For URL '" << expected_url << "', expected count for word '" << word 
                << "' is " << count << ", but found " << actual_it->second << ".";
        }
    }
}

TEST(CrawlerTest, TestCrawlerBFSLinks) {
    CrawlerManager manager_links("../config_test_bfs.json");
    std::string filename_link = "/tmp/links.txt";
    std::string filename_word = "/tmp/words.txt";

    remove_if_file_exists(filename_link);
    remove_if_file_exists(filename_word);

    manager_links.start_crawling();

    CrawlerDBBase& db  = CrawlerDBFile::get_instance();
    std::map<std::string, std::map<std::string, int>> result_links_map = db.get_links_map();

    // Define expected results for testing
    std::map<std::string, std::map<std::string, int>> expected_results = {
        {"https://harrypotter.fandom.com/wiki/Category:Books_(real-world)", {{"https://harrypotter.fandom.com/wiki/Category:Books_(real-world)", 6}}},
        {"https://harrypotter.fandom.com/wiki/Category:Directors_(real-world)", {{"https://harrypotter.fandom.com/wiki/Category:Directors_(real-world)", 2}}},
        {"https://harrypotter.fandom.com/wiki/Category:Films_(real-world)", {{"https://harrypotter.fandom.com/wiki/Category:Films_(real-world)", 4}}},
        {"https://harrypotter.fandom.com/wiki/Category:Individuals", {{"https://harrypotter.fandom.com/wiki/Category:Individuals", 2}}},
        {"https://harrypotter.fandom.com/wiki/Category:Video_games_(real-world)", {{"https://harrypotter.fandom.com/wiki/Category:Video_games_(real-world)", 4}}},
        {"https://harrypotter.fandom.com/wiki/Cerberus_Langarm", {{"https://harrypotter.fandom.com/wiki/Cerberus_Langarm", 2}}},
        {"https://harrypotter.fandom.com/wiki/Chiara_Lobosca", {{"https://harrypotter.fandom.com/wiki/Chiara_Lobosca", 2}}},
        {"https://harrypotter.fandom.com/wiki/Chris_Columbus", {{"https://harrypotter.fandom.com/wiki/Chris_Columbus", 2}}},
        {"https://harrypotter.fandom.com/wiki/Colby_Frey", {{"https://harrypotter.fandom.com/wiki/Colby_Frey", 2}}},
    };

    for (const auto& [expected_url, expected_link_counts] : expected_results) {
        auto it = result_links_map.find(expected_url);
        ASSERT_NE(it, result_links_map.end()) << "Expected URL '" << expected_url << "' not found.";
        
        const auto& actual_link_counts = it->second;

        // Check if the actual link counts match the expected link counts
        for (const auto& [link, count] : expected_link_counts) {
            auto actual_it = actual_link_counts.find(link);
            ASSERT_NE(actual_it, actual_link_counts.end()) << "Expected link '" << link << "' for URL '" << expected_url << "' not found.";
            ASSERT_EQ(actual_it->second, count) << "For URL '" << expected_url << "', expected count for link '" << link 
                << "' is " << count << ", but found " << actual_it->second << ".";
        }
    }
}


TEST(CrawlerTest, TestCrawlerDFSLinks) {
    CrawlerManager manager_links("../config_test_dfs.json");
    std::string filename_link = "/tmp/links.txt";
    std::string filename_word = "/tmp/words.txt";

    remove_if_file_exists(filename_link);
    remove_if_file_exists(filename_word);

    manager_links.start_crawling();

    CrawlerDBBase& db  = CrawlerDBFile::get_instance();
    std::map<std::string, std::map<std::string, int>> result_links_map = db.get_links_map();

    // Define expected results for testing
    std::map<std::string, std::map<std::string, int>> expected_results = {
        {"https://harrypotter.fandom.com/wiki/Category:Books_(real-world)", {{"https://harrypotter.fandom.com/wiki/Category:Books_(real-world)", 6}}},
        {"https://harrypotter.fandom.com/wiki/Category:Directors_(real-world)", {{"https://harrypotter.fandom.com/wiki/Category:Directors_(real-world)", 2}}},
        {"https://harrypotter.fandom.com/wiki/Category:Films_(real-world)", {{"https://harrypotter.fandom.com/wiki/Category:Films_(real-world)", 4}}},
        {"https://harrypotter.fandom.com/wiki/Category:Individuals", {{"https://harrypotter.fandom.com/wiki/Category:Individuals", 2}}},
        {"https://harrypotter.fandom.com/wiki/Category:Video_games_(real-world)", {{"https://harrypotter.fandom.com/wiki/Category:Video_games_(real-world)", 4}}},
        {"https://harrypotter.fandom.com/wiki/Cerberus_Langarm", {{"https://harrypotter.fandom.com/wiki/Cerberus_Langarm", 2}}},
        {"https://harrypotter.fandom.com/wiki/Chiara_Lobosca", {{"https://harrypotter.fandom.com/wiki/Chiara_Lobosca", 2}}},
        {"https://harrypotter.fandom.com/wiki/Chris_Columbus", {{"https://harrypotter.fandom.com/wiki/Chris_Columbus", 2}}},
        {"https://harrypotter.fandom.com/wiki/Colby_Frey", {{"https://harrypotter.fandom.com/wiki/Colby_Frey", 2}}},
    };

    for (const auto& [expected_url, expected_link_counts] : expected_results) {
        auto it = result_links_map.find(expected_url);
        ASSERT_NE(it, result_links_map.end()) << "Expected URL '" << expected_url << "' not found.";
        
        const auto& actual_link_counts = it->second;

        // Check if the actual link counts match the expected link counts
        for (const auto& [link, count] : expected_link_counts) {
            auto actual_it = actual_link_counts.find(link);
            ASSERT_NE(actual_it, actual_link_counts.end()) << "Expected link '" << link << "' for URL '" << expected_url << "' not found.";
            ASSERT_EQ(actual_it->second, count) << "For URL '" << expected_url << "', expected count for link '" << link 
                << "' is " << count << ", but found " << actual_it->second << ".";
        }
    }
}


TEST(CrawlerTest, CompareCrawlerBFSAndDFS) {
    CrawlerManager manager_bfs("../config_test_bfs.json");
    CrawlerManager manager_dfs("../config_test_dfs.json");

    CrawlerStats statistic_bfs = manager_bfs.start_crawling();
    CrawlerStats statistic_dfs = manager_dfs.start_crawling();

    ASSERT_EQ(statistic_bfs.m_pages_crawled, statistic_dfs.m_pages_crawled);
}


// Database tests
TEST(CrawlerDBTest, TestDBWriteAndRead) {
    std::string filename_link = "/tmp/links.txt";
    std::string filename_word = "/tmp/words.txt";

    remove_if_file_exists(filename_link);
    remove_if_file_exists(filename_word);
    
    CrawlerDBBase& db  = CrawlerDBFile::get_instance();
    db.read_DB();


    std::map<std::string, std::map<std::string, int>> links_map = {
        {"http://example.com", {{"page1", 1}, {"page2", 2}}},
        {"http://example.org", {{"page3", 3}, {"page4", 4}}}
    };

    std::map<std::string, std::map<std::string, int>> words_map = {
        {"Hello", {{"http://www.lea.co.il", 1}, {"http://www.lea2.co.il", 2}}},
        {"Eyal", {{"http://example3.org", 3}, {"http://example4.org", 4}}}
    };

    // Update maps in the database
    for (const auto& item : links_map) {
        db.update_links_map(item.first, item.second);
    }

    for (const auto& item : words_map) {
        db.update_words_map(item.first, item.second);
    }

    db.write_DB();
    db.read_DB();

    // Verify maps
    auto result_links_map = db.get_links_map();
    auto result_words_map = db.get_words_map();

    EXPECT_EQ(links_map, result_links_map);
    EXPECT_EQ(words_map, result_words_map);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
