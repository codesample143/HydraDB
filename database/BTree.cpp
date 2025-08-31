#include <BTree.hpp>

Page::Page(bool leaf, std::size_t _capacity, uint32_t id){
    capacity = _capacity;
    page_id = id;
    header.is_leaf = leaf;
    header.num_keys = 0;
    header.parent_page_id = 0;
    header.next_page_id = 0;

    if (header.is_leaf)
        KV.reserve(_capacity);
    else {
        K.reserve(_capacity);
        children.reserve(_capacity + 1);
    }
}

uint32_t Page::getNextPageID() {

}

bool Page::isLeaf() const {
    return header.is_leaf;
}

void Page::insertKV(const std::string& key, const std::vector<std::string>& value) {
    size_t index = 0;
    while (index < header.num_keys && KV[index].first < key)
        index++;

    if (index < header.num_keys && KV[index].first == key) {
        KV[index].second.insert(KV[index].second.end(), value.begin(), value.end());
        return;
    }

    KV.insert(KV.begin() + index, std::make_pair(key, value));
    header.num_keys++;

    if (header.num_keys > capacity)
        split(getNextPageID(), capacity);
}

void Page::storeChildPointer() {

}

Page Page::split(uint32_t new_page_id, std::size_t _capacity) {
    Page new_page(header.is_leaf, _capacity, new_page_id);
    size_t mid = header.num_keys / 2;
    new_page.KV.assign(KV.begin() + mid, KV.end());
    KV.erase(KV.begin() + mid, KV.end());

    if (header.is_leaf) {
        header.num_keys = KV.size();
        new_page.header.num_keys = new_page.KV.size();

        new_page.header.next_page_id = header.next_page_id;
        header.next_page_id = new_page.page_id;
    } else {
        new_page.children.assign(children.begin() + mid + 1, children.end());
        children.erase(children.begin() + mid + 1, children.end());

        header.num_keys = K.size();
        new_page.header.num_keys = new_page.K.size();
    }

    return new_page;
}

void Page::WritePageToDisk(const std::string& filename) {
    std::ofstream out(filename, std::ios::binary | std::ios::in | std::ios::out);
    if (!out.is_open())
        out.open(filename, std::ios::binary | std::ios::trunc);

    out.seekp((page_id - 1) * PAGE_SIZE);
    out.write(reinterpret_cast<const char*>(&header), sizeof(PageHeader));
}

Page Page::LoadFromDisk(uint32_t page_id, const std::string& filename, std::size_t capacity) {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
        throw std::runtime_error("Cannot open database file");

    in.seekg((page_id - 1) * PAGE_SIZE);
    PageHeader header;
    in.read(reinterpret_cast<char*>(&header), sizeof(PageHeader));

    Page page(header.is_leaf, capacity, page_id);
    page.header = header;
    return page;
}

uint32_t Page::getPageID(){
    return page_id;
}
