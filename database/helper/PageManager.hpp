#include <string>
#include <iostream>
class PageManager {
    uint32_t next_page_id;
    PageManager();
    public:
        uint32_t getNextPageID() {
            return next_page_id++;
        }

        

        
};