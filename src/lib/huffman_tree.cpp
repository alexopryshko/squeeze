#include "huffman_tree.h"
#include "math.h"

void huffman_tree::createTree() {
    if (_heap == nullptr)
        return;

    while (!_heap->isEmpty()) {
        node* node_buf_first = _heap->extractMax();
        if (_heap->isEmpty()) {
            head = node_buf_first;
            return;
        }
        node* node_buf_second = _heap->extractMax();
        node* parent_node = new node;

        parent_node->setLeft(node_buf_first);
        parent_node->setRight(node_buf_second);
        parent_node->setFrequency(node_buf_first->getFrequency() + node_buf_second->getFrequency());

        _heap->add(parent_node);
    }
}

void huffman_tree::createArray() {
    if (huffman_array != nullptr) {
        delete[] huffman_array;
    }
    int size = static_cast<int>(pow(2, 8 * sizeof(unsigned char)));
    huffman_array = new node*[size];
    this->generateCodesToChars(head, 0, 0);
}

void huffman_tree::generateCodesToChars(node* _head, int code, unsigned char deep) {
    int toLeftChild = code << 1;
    int toRightChild = code << 1;
    toRightChild |= 1;

    if (_head->getLeft() != nullptr) {
        huffman_tree::generateCodesToChars(_head->getLeft(), toLeftChild, (unsigned char) (deep + 1));
    }
    if (_head->getRight() != nullptr) {
        huffman_tree::generateCodesToChars(_head->getRight(), toRightChild, (unsigned char) (deep + 1));
    }
    if (_head->getLeft() == nullptr && _head->getRight() == nullptr) {
        int* _buf = new int[deep];
        for (int i = deep - 1; i >= 0; i--) {
            _buf[i] = code & 1;
            code >>= 1;
        }
        _head->setCode(_buf);
        _head->setDeep(deep);
        huffman_array[(int)_head->getCharacter()] = _head;
    }
}

node* huffman_tree::getNodeByCharCode(int code) {
    if (huffman_array != nullptr) {
        return huffman_array[code];
    }
    else {
        return nullptr;
    }
}

node* huffman_tree::getHead() const {
    return head;
}

void huffman_tree::removeTree(node* _node) {
    if (_node->getLeft() != nullptr)
        removeTree(_node->getLeft());
    if (_node->getRight() != nullptr)
        removeTree(_node->getRight());
    delete _node;
}