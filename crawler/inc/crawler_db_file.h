#ifndef CRAWLER_DB_FILE_H_
#define CRAWLER_DB_FILE_H_

#include "crawler_db_base.h"
#include <string>
#include <map>
#include <vector>
#include <fstream>

/**
 * @class CrawlerDBFile
 * @brief Class for managing a file-based database for the web crawler.
 * 
 * This class handles reading and writing links and words to/from files 
 * and provides the necessary functionality as defined in the CrawlerDBBase 
 * interface.
 */
class CrawlerDBFile : public CrawlerDBBase {
public:
    /**
     * @brief Constructs a CrawlerDBFile object with specified link and word file names.
     * @param links_file The filename for the links database.
     * @param words_file The filename for the words database.
     */
    CrawlerDBFile();

    /**
     * @brief Read the database and initialize the internal maps.
     */
    void read_DB() override;

    /**
     * @brief Update the links map with the given URL and link counts.
     * @param a_url The URL to update.
     * @param a_links_count A map of links and their respective counts.
     */
    void update_links_map(const std::string& a_url, const std::map<std::string, int>& a_links_count) override;

    /**
     * @brief Update the words map with the given word and URL counts.
     * @param a_word The word to update.
     * @param a_urls_count A map of URLs and their respective counts.
     */
    void update_words_map(const std::string& a_word, const std::map<std::string, int>& a_urls_count) override;

    /**
     * @brief Write the current maps to the database.
     */
    void write_DB() override;

    /**
     * @brief Check if the given URL has been visited.
     * @param url The URL to check.
     * @return True if the URL has been visited, false otherwise.
     */
    bool is_visited(const std::string& url) const override;

    /**
     * @brief Get the links map.
     * @return A map of links and their respective counts.
     */
    std::map<std::string, std::map<std::string, int>> get_links_map() const override;

    /**
     * @brief Get the words map.
     * @return A map of words and their respective counts.
     */
    std::map<std::string, std::map<std::string, int>> get_words_map() const override;

    /**
     * @brief Get query results based on the provided query string.
     * @param query The query string to search for.
     * @param max_url The maximum number of URLs to return.
     * @return A vector of URLs that match the query.
     */
    std::vector<std::string> get_query_results(const std::string& query, int max_url) const override;

    /**
     * @brief Get the singleton instance of CrawlerDBFile.
     * @param links_file The filename for the links database.
     * @param words_file The filename for the words database.
     * @return Reference to the singleton instance.
     */
    static CrawlerDBFile& get_instance();

private:
    std::string m_database_links;  ///< Filename for the links database.
    std::string m_database_words;   ///< Filename for the words database.
    std::map<std::string, std::map<std::string, int>> m_links_map;  ///< Internal map to store links and counts.
    std::map<std::string, std::map<std::string, int>> m_words_map;   ///< Internal map to store words and counts.

    /**
     * @brief Write the map data to a file.
     * @param filename The filename to write to.
     * @param map_data The map data to write.
     */
    void write_map_to_file(const std::string& filename, const std::map<std::string, std::map<std::string, int>>& map_data);

    /**
     * @brief Read map data from a file.
     * @param filename The filename to read from.
     * @param map_data The map data to fill.
     */
    void read_map_from_file(const std::string& filename, std::map<std::string, std::map<std::string, int>>& map_data);
};

#endif  // CRAWLER_DB_FILE_H_
