#include "crawler_config.h"

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using json = nlohmann::json;

CrawlerConfig::CrawlerConfig(std::string const& a_config_file_path)
{
    std::ifstream config_file(a_config_file_path);
    if (!config_file.is_open()) {
        throw std::runtime_error("Could not open config file");
    }

    json data = json::parse(config_file);

    m_start_urls = data["start_urls"].get<std::vector<std::string>>();
    m_max_depth = data["max_depth"].get<int>();
    m_max_limit_pages = data["max_pages"].get<int>();
    m_crawling_mode = data["crawl_mode"].get<std::string>();
}

std::vector<std::string> const& CrawlerConfig::get_start_urls() const
{
    return m_start_urls;
}

int CrawlerConfig::get_max_depth() const
{
    return m_max_depth;
}

int CrawlerConfig::get_max_limit_pages() const
{
    return m_max_limit_pages;
}

std::string const& CrawlerConfig::get_crawling_mode() const
{
    return m_crawling_mode;
}

