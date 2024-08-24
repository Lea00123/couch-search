### **Couch Search Engine**

**Overview**
Couch Search Engine is a C++17 project that crawls websites and provides a search engine to query pages based on specific terms.
It ranks results by importance and stores data in a MySQL or Redis database.

**Features**
Crawling: Configurable BFS or DFS crawl, with options for max depth, page limits, and crawl scope (server, domain, or internet-wide).
Search Engine: Handles positive and negative search terms, returns case-insensitive results, and ranks pages by link importance.
Storage: Indexes links between pages and word occurrences, storing the data in a database.

**Configuration**
Set up the crawler using a config file specifying:
**Start URLs**
Max pages and depth
Crawl mode (BFS/DFS)
Crawl scope
