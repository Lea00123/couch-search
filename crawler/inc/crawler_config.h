#ifndef CRAWLER_CONFIG_H_
#define CRAWLER_CONFIG_H_

#include <string>
#include <vector>

class CrawlerConfig {
public:
public:
    CrawlerConfig(std::string const& a_config_file_path);

    /**
     * Get the list of start URLs from the configuration.
     * @return A constant reference to a vector of start URLs.
     */
    std::vector<std::string> const& get_start_urls() const;

    /**
     * Get the maximum number of pages to crawl.
     * @return The maximum number of pages to crawl.
     */
    int get_max_limit_pages() const;

    /**
     * Get the maximum depth for crawling.
     * @return The maximum depth for crawling.
     */
    int get_max_depth() const;

    /**
     * Get the crawling mode (BFS or DFS).
     * @return A constant reference to the crawling mode string.
     */
    std::string const& get_crawling_mode() const;

    /**
     * Get the database mode (SQL or FILE or Redis).
     * @return A constant reference to the database mode string.
     */
    std::string const& get_database_type() const;

private:
    std::vector<std::string> m_start_urls;
    int m_max_limit_pages;
    int m_max_depth;
    std::string m_crawling_mode;
    std::string m_database_type;

};

#endif  // CRAWLER_CONFIG_H_