#include "squeeze.h"
#include "lib/huffman_tree.h"
#include "lib/utils.h"

void squeeze::compress(string source_file_path, string source_file_name, string destination_file_path) {
    file* source_file = new file((source_file_path + source_file_name).c_str());
    if (!source_file->open("rb"))
        return;
    file* destination_file = new file((destination_file_path + source_file_name + ".sqz").c_str());
    if (!destination_file->open("w+b"))
        return;

    unsigned char name_size = (unsigned char) source_file_name.length();
    destination_file->write(&name_size, 1);
    const char* file_name = source_file_name.c_str();
    destination_file->write(file_name, name_size);


    auto buf = charDistribution(source_file);
    source_file->setCursorToBegin();
    long size = source_file->getSize();
    saveCharDistributionToFile(destination_file, buf);
    destination_file->write(&size, 1);

    heap<node *> *_heap = new heap<node *>(buf);
    huffman_tree *_huffman_tree = new huffman_tree(_heap);
    _huffman_tree->createTree();
    _huffman_tree->createArray();

    unsigned char *charBuffer = new unsigned char();
    unsigned char *outputBuffer = new unsigned char();
    int position = 0;

    for (int i = 0; i < size; i++) {
        source_file->read(charBuffer, 1);
        node *_node = _huffman_tree->getNodeByCharCode((int) *charBuffer);

        int shift = 0;
        while (shift < _node->getDeep()) {
            if (position < 8 * sizeof(unsigned char)) {
                *outputBuffer <<= 1;
                if (_node->getCode(shift) == 1)
                    *outputBuffer |= 1;
                shift++;
                position++;
            }
            else {
                destination_file->write(outputBuffer, 1);
                *outputBuffer &= 0;
                position = 0;
            }
        }
    }
    if (position != 0) {
        *outputBuffer <<= (8 * sizeof(unsigned char) - position);
        destination_file->write(outputBuffer, 1);
    }
    delete _huffman_tree;
    delete charBuffer;
    delete outputBuffer;
}

void squeeze::decompress(string source_file_path, string source_file_name, string destination_file_path) {
    file* source_file = new file((source_file_path + source_file_name).c_str());
    if (!source_file->open("rb"))
        return;
    unsigned char *name_size = new unsigned char();
    source_file->read(name_size, 1);
    char* name_buf = new char[*name_size];
    source_file->read(name_buf, *name_size);
    string *destination_file_name = new string(name_buf);
    std::cout << *destination_file_name;
    file* destination_file = new file((destination_file_path + *destination_file_name).c_str());
    if (!destination_file->open("w+b"))
        return;
    auto buf = readCharDistributionFromFile(source_file);
    heap<node *> *_heap = new heap<node *>(buf);
    huffman_tree *_huffman_tree = new huffman_tree(_heap);
    _huffman_tree->createTree();
    node* _node = _huffman_tree->getHead();

    long* size = new long();
    source_file->read(size, 1);

    int byte_size = 8 * sizeof(unsigned char);
    unsigned char* charBuffer = new unsigned char();

    for (int i = 0; i < *size;) {
        source_file->read(charBuffer, 1);
        int* _buf = new int[byte_size];
        for (int j = byte_size - 1; j >=0; j--) {
            _buf[j] = *charBuffer & 1;
            *charBuffer >>= 1;
        }

        int shift = 0;
        while (shift < byte_size && i < *size) {
            if (_node->getLeft() != nullptr && _buf[shift] == 0)
                _node = _node->getLeft();
            if (_node->getRight() != nullptr && _buf[shift] == 1)
                _node = _node->getRight();
            if (_node->getLeft() == nullptr && _node->getRight() == nullptr) {
                auto character = _node->getCharacter();
                destination_file->write(&character, 1);
                _node = _huffman_tree->getHead();
                i++;
            }
            shift++;
        }
        delete[] _buf;
    }
    delete _huffman_tree;
    delete name_size;
    delete[] name_buf;
    delete destination_file_name;
}