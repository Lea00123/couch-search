#ifndef CRAWLER_DB_H_
#define CRAWLER_DB_H_

#include <map>
#include <string>
#include <vector>

class CrawlerDB {
public:
    // Deleted copy constructor and assignment operator
    CrawlerDB(const CrawlerDB&) = delete;
    void operator=(const CrawlerDB&) = delete;

    /**
     * Get the singleton instance of the CrawlerDB.
     * @return A reference to the CrawlerDB instance.
     */
    static CrawlerDB& get_instance();

    /**
     * Read the database files and initialize the internal maps.
     */
    void read_DB();

    /**
     * Update the links map with the given URL and link counts.
     * @param a_url The URL to update.
     * @param a_links_count A map of links and their counts.
     */
    void update_links_map(const std::string& a_url, const std::map<std::string, int>& a_links_count);

    /**
     * Update the words map with the given word and URL counts.
     * @param a_word The word to update.
     * @param a_urls_count A map of URLs and their counts.
     */
    void update_words_map(const std::string& a_word, const std::map<std::string, int>& a_urls_count);

    /**
     * Write the current maps to the database files.
     */
    void write_DB();

    /**
     * Check if the given URL has been visited.
     * @param url The URL to check.
     * @return True if the URL has been visited, false otherwise.
     */
    bool is_visited(const std::string& url) const;

    /**
     * Get the links map.
     * @return A constant reference to the links map.
     */
    std::map<std::string, std::map<std::string, int>> get_links_map() const;

    /**
     * Get the words map.
     * @return A constant reference to the words map.
     */
    std::map<std::string, std::map<std::string, int>> get_words_map() const;

    /**
     * Get query results based on the provided query string.
     * @param query The query string to search for.
     * @param max_url The maximum number of URLs to return.
     * @return A vector of strings containing the query results.
     */
    std::vector<std::string> get_query_results(const std::string& query, int max_url) const;

private:
    // Private constructor for singleton implementation
    CrawlerDB();

    // Helper function to write a map to a file
    void write_map_to_file(const std::string& a_filename, const std::map<std::string, std::map<std::string, int>>& a_data_map);

    // Helper function to read a map from a file
    void read_map_from_file(const std::string& a_filename, std::map<std::string, std::map<std::string, int>>& a_data_map);

private:
    // URL to URLs counters
    std::map<std::string, std::map<std::string, int>> m_links_map;  

    // Word to URLs counters
    std::map<std::string, std::map<std::string, int>> m_words_map;

    // Database file paths
    const std::string m_database_links;
    const std::string m_database_words;
};

#endif  // CRAWLER_DB_H_
