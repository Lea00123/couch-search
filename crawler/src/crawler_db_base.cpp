#ifndef CRAWLING_DB_BASE_H_
#define CRAWLING_DB_BASE_H_

#include <map>
#include <string>
#include <vector>

class CrawlingDBBase {
public:
    virtual ~CrawlingDBBase() {}

    /**
     * Read the database and initialize the internal maps.
     */
    virtual void read_DB() = 0;

    /**
     * Update the links map with the given URL and link counts.
     */
    virtual void update_links_map(const std::string& a_url, const std::map<std::string, int>& a_links_count) = 0;

    /**
     * Update the words map with the given word and URL counts.
     */
    virtual void update_words_map(const std::string& a_word, const std::map<std::string, int>& a_urls_count) = 0;

    /**
     * Write the current maps to the database.
     */
    virtual void write_DB() = 0;

    /**
     * Check if the given URL has been visited.
     */
    virtual bool is_visited(const std::string& url) const = 0;

    /**
     * Get the links map.
     */
    virtual std::map<std::string, std::map<std::string, int>> get_links_map() const = 0;

    /**
     * Get the words map.
     */
    virtual std::map<std::string, std::map<std::string, int>> get_words_map() const = 0;

    /**
     * Get query results based on the provided query string.
     */
    virtual std::vector<std::string> get_query_results(const std::string& query, int max_url) const = 0;
};

#endif  // CRAWLING_DB_BASE_H_
