#include "utils.h"
#include "math.h"

vector<node*>* charDistribution(file* _file) {
    int byte = static_cast<int>(pow(2, 8 * sizeof(unsigned char)));
    unsigned int *buffer = new unsigned int[byte];

    for (int i = 0; i < byte; i++) {
        buffer[i] = 0;
    }

    unsigned char* charBuffer = new unsigned char();
    long size = _file->getSize();
    for (int i = 0; i < size; i++) {
        _file->read(charBuffer, sizeof(unsigned char));
        buffer[(int)*charBuffer]++;
    }

    vector<node*>* result = new vector<node*>();
    for (int i = 0; i < byte; i++) {
        if (buffer[i] != 0) {
            result->push_back(new node(buffer[i], (unsigned char)i));
        }
    }

    delete charBuffer;
    delete [] buffer;
    return result;
}

void saveCharDistributionToFile(file* _file, vector<node*>* char_distribution) {
    unsigned long size = char_distribution->size();
    _file->write(&size, 1);
    for (auto item : *char_distribution) {
        auto char_buf = item->getCharacter();
        auto freq_buf = item->getFrequency();
        _file->write(&char_buf, 1);
        _file->write(&freq_buf, 1);
    }
}

vector<node*>* readCharDistributionFromFile(file* _file) {
    unsigned long *size = new unsigned long();
    _file->read(size, 1);
    vector<node*>* result = new vector<node*>();
    for (int i = 0; i < *size; i++) {
        unsigned char* char_buf = new unsigned char();
        unsigned int* freq_buf = new unsigned int();
        _file->read(char_buf, 1);
        _file->read(freq_buf, 1);
        result->push_back(new node(*freq_buf, *char_buf));
    }
    delete size;
    return result;
}