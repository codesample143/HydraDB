#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>

#define PAGE_SIZE 4096

//========================================
// Page Structures
//========================================
struct PageHeader {
    bool is_leaf;
    std::size_t num_keys;
    uint32_t parent_page_id;  // 0 if root
    uint32_t next_page_id;    // only used for leaf nodes
};

class Page {
private:
    PageHeader header;
    std::vector<std::string> K;   // separator keys (internal)
    std::vector<std::pair<std::string, std::vector<std::string>>> KV; // leaf
    std::vector<uint32_t> children; // child page ids
    std::size_t capacity;
    uint32_t page_id;

public:
    Page(bool leaf, std::size_t _capacity, uint32_t id);

    uint32_t getPageID();
    uint32_t getNextPageID();
    bool isLeaf() const;
    void insertKV(const std::string& key, const std::vector<std::string>& value);
    void storeChildPointer();
    Page split(uint32_t new_page_id, std::size_t capacity);
    void WritePageToDisk(const std::string& filename);
    static Page LoadFromDisk(uint32_t page_id, const std::string& filename, std::size_t capacity);

};
