#include "node.h"

node::node(unsigned int frequency, unsigned char character) {
    this->frequency = frequency;
    this->character = character;
}

bool operator<(node &operand1, node &operand2) {
    return operand1.frequency > operand2.frequency;
}

bool operator>(node &operand1, node &operand2) {
    return operand1.frequency < operand2.frequency;
}

unsigned int node::getFrequency() const {
    return frequency;
}

unsigned char node::getCharacter() const {
    return character;
}

int node::getCode(int pos) const {
    return _code[pos];
}

void node::setLeft(node *left) {
    node::left = left;
}

void node::setRight(node *right) {
    node::right = right;
}

void node::setFrequency(unsigned int frequency) {
    node::frequency = frequency;
}

void node::setCharacter(unsigned char character) {
    node::character = character;
}

void node::setCode(int* _code) {
    node::_code = _code;
}

node *node::getLeft() const {
    return left;
}

node *node::getRight() const {
    return right;
}

unsigned char node::getDeep() const {
    return deep;
}

void node::setDeep(unsigned char deep) {
    node::deep = deep;
}
