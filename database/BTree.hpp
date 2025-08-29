
#include <vector>
#include <cstdint>
#define PAGE_SIZE 4096


struct PageHeader {
    bool is_leaf;
    std::size_t num_keys;
    uint32_t parent_page_id;  // or nullptr if root
    uint32_t next_page_id;    // only used for leaf nodes
};

class Page{
private:
    PageHeader header;
    std::vector<std::string> K;   // separator keys
    std::vector<std::pair<std::string, std::vector<std::string>>> KV;
    std::vector<uint32_t> children;
    std::size_t capacity;
public:
    Page(bool leaf, std::size_t _capacity, uint32_t page_id){
        header.is_leaf = leaf;
        header.num_keys = 0;
        header.parent_page_id = 0;
        page_id = getNextPageID();
        capacity = _capacity;

        if(header.is_leaf) {
            KV.reserve(_capacity);       // leaf stores key-value pairs
        } else {
            K.reserve(_capacity);        // internal keys
            children.reserve(_capacity + 1); // child pointers
        }

    };

    uint32_t getNextPageID(){

    }

    bool isLeaf(){
        return header.is_leaf;
    }

    void insertKV(const std::string& key, const std::vector<std::string>& value){
        //add logic for split if inserting a KV would exceed capacity
        int index = 0;
        /**
         * As long as the index remains less than the number of keys and the value of the key remains in sorted order to minimize splitting,
         * we can increment "index". Perhaps a better word for this could be position. 
         */
        while(index < header.num_keys && KV[index].first < key){ //should consider what this is doing in terms of indexing, we wait for sorted ordr
            index++; 
        }

        // 2. Key exists → append to vector
        if(index < header.num_keys && KV[index].first == key){
            KV[index].second.insert(KV[index].second.end(), value.begin(), value.end());
            return;
        }

        KV.insert(KV.begin() + index, std::make_pair(key, value));
        header.num_keys++;

        if(header.num_keys > capacity){
            split(getNextPageID(), capacity); //gets the next pageID(simply increments at the moment, but you need to probably define page?)
            return;
        }
    }

    void storeChildPointer(){

    }
    /**
     *  Leaf split → promotes first key of the right half.
        Internal split → promotes the middle key.
        Root split → creates a new root and grows the tree.
    */
    Page split(uint32_t new_page_id, std::size_t capacity){
        /**
         * Create a new Page, give it the new_page_id. You also need to check if it's a leaf page, internal page, or root. 
         */
        Page new_page(true, capacity, new_page_id);
        int mid = header.num_keys / 2;

        new_page.KV.assign(KV.begin() + mid, KV.end()); //paritioning the page
        KV.erase(KV.begin() + mid, KV.end());

        //main issue is that you have to reassign the pointers but you don't currently have pointers to the original page after you split?
        if(new_page.isLeaf()){
            //input data, write to page and store in leaf?
            
        } else if(children.size() == 0){ //checks if it's root, but this should be the old page not the new_page
            children.emplace_back(new_page_id); //give the pointer as pageid? 
        } else { //this is a non root node and non leaf node, meaning that this page will hold pointers to leaf nodes which have data

        }
        //this is NOT DONE DO NOT PUSH THIS TO PROD OK U DUMBASS

        return new_page;

    }

};

//from https://github.com/solangii/b-plus-tree
//will not become necessary until I create in-memory functionality
template <typename T>
struct Node{
    bool is_leaf;             // true if the node is a leaf (no children), false if it's an internal node
    std::size_t degree;       // maximum number of children the node can have (tree order)
    std::size_t size;         // current number of items (keys) in this node
    T* item;                  // array of keys (data stored in this node)
    Node<T>** children;       // array of pointers to child nodes
    Node<T>* parent;          // pointer to the parent node (nullptr if root)
    //might remove this, i want disk not in-memory
public:
    Node(std::size_t _degree){
        this->is_leaf = false;
        this->degree = _degree;
        this->size = 0;

        T* _item = new T[degree - 1];
        for(int i=0; i<degree-1; i++){
            _item[i] = 0;
        }
        this->item = _item;

        Node<T>** _children = new Node<T>*[degree];
        for(int i=0; i<degree; i++){
            _children[i] = nullptr;
        }

        this->children = _children;
        this->parent = nullptr;

    }
};

template <typename T>
class BPlusTree {
    Node<T>* root;
    std::size_t degree;
public:
    BPlusTree(std::size_t _degree){
        (*this).root = nullptr;
        (*this).degree = _degree;
    }

    ~BPlusTree(){
        std::cout << "B+ tree was destroyed (not really until you define clear)";
    }

    Node<T>* BPlusTreeSearch(Node<T>* node, T key){
        if(node == nullptr){
            return nullptr;
        } else {
            Node<T>* pointer = node;
            while(!(*pointer).is_leaf){
                
            }
        }
    }

};