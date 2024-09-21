#include <map>
#include <string>
#include <vector>

class CrawlerDB {
public:
    CrawlerDB(const std::string& a_database_links, const std::string& a_database_words);

    void read_DB();

    // Function to update the links map
    void update_links_map(const std::string& a_url, const std::map<std::string, int>& a_links_count);

    // Function to update the word map
    void update_words_map(const std::string& a_word, const std::map<std::string, int>& a_urls_count);

    // Function to write to te database
    void write_DB();

    // Function to check if a URL has been visited
    bool is_visited(const std::string& url) const;

    // Function to get links map
    std::map<std::string, std::map<std::string, int>> get_links_map() const;

    // Function to get words map
    std::map<std::string, std::map<std::string, int>> get_words_map() const;

    // Function to get query results
    std::vector<std::string> get_query_results(const std::string& query, int max_url) const;

private:
    void write_map_to_file(const std::string& a_filename, const std::map<std::string, std::map<std::string, int>>& a_data_map);
    void read_map_from_file(const std::string& a_filename, std::map<std::string, std::map<std::string, int>>& a_data_map);

private:    
    // URL to urls counters
    std::map<std::string, std::map<std::string, int>> m_links_map;

    //Word to urls word counters
    std::map<std::string, std::map<std::string, int>> m_words_map;
    std::string m_database_links;
    std::string m_database_words;
};
