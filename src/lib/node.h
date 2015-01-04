#pragma once

class node {
public:
    node() {}

    node (unsigned int frequency, unsigned char character);

    friend bool operator < (node &operand1, node &operand2);
    friend bool operator > (node &operand1, node &operand2);

    unsigned int getFrequency() const;
    unsigned char getCharacter() const;
    int getCode(int pos) const;
    unsigned char getDeep() const;
    node *getLeft() const;
    node *getRight() const;

    void setDeep(unsigned char deep);
    void setLeft(node *left);
    void setRight(node *right);
    void setFrequency(unsigned int frequency);
    void setCharacter(unsigned char character);

    void setCode(int* _code);

    ~node() {
        delete[] _code;
    }

private:
    unsigned int frequency = 0;
    unsigned char character = 0;
    unsigned char deep = 0;
    int* _code = nullptr;

    node* left = nullptr;
    node* right = nullptr;
};