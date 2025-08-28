//from https://github.com/solangii/b-plus-tree

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
    std::vector<std::string> K;
    std::vector<std::vector<std::string>> V;
    std::vector<uint32_t> children;
public:
    uint32_t page_id;
    Page(bool leaf, std::size_t _capacity, uint32_t _id){
        header.is_leaf = leaf;
        header.num_keys = 0;
        header.parent_page_id = 0;
        page_id = _id;

        K.reserve(_capacity);
        if(header.is_leaf){
            V.reserve(_capacity);
        } else {
            children.reserve(_capacity + 1);
        }

    };

    bool isLeaf(){
        return header.is_leaf;
    }

    void insertKV(const std::string& key, const std::vector<std::string>& value){

    }

    void storeChildPointer(){

    }

    Page split(uint32_t new_page_id, std::size_t capacity){
        
    }

};
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