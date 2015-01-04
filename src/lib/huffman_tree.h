#pragma once

#include "node.h"
#include "heap.h"

class huffman_tree {
public:

    huffman_tree(heap<node*>* _heap) {
        this->_heap = _heap;
    }
    ~huffman_tree() {
        delete _heap;
        delete[] huffman_array;
        removeTree(head);
    }

    void createTree();
    void createArray();
    node* getNodeByCharCode(int code);

    node *getHead() const;



private:
    heap<node*>* _heap = nullptr;
    node* head = nullptr;
    node** huffman_array = nullptr;

    void generateCodesToChars(node* _head, int code, unsigned char deep);
    void removeTree(node* _node);
};