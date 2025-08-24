//from https://github.com/solangii/b-plus-tree

#include <vector>
#include <cstdint>
#define PAGE_SIZE = 4096


template <typename T>
struct Node{
    bool is_leaf;             // true if the node is a leaf (no children), false if it's an internal node
    std::size_t degree;       // maximum number of children the node can have (tree order)
    std::size_t size;         // current number of items (keys) in this node
    T* item;                  // array of keys (data stored in this node)
    Node<T>** children;       // array of pointers to child nodes
    Node<T>* parent;          // pointer to the parent node (nullptr if root)
public:
    Node(std::size_t _degree){
        this->is_leaf = false;
        this->degree = degree;
        this->size = 0;

        T* _item = new T[degree - 1];

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