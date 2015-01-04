#pragma once
#include <stdio.h>

class file {
public:

    file(const char* filePath) {
        this->filePath = filePath;
    }

    bool open(const char* flags);
    void close();

    template <typename type>
    void read(type* data, size_t length);
    template <typename type>
    void write(type* bytes, size_t length);

    void setCursorToBegin() {fseek(fileD, 0, 0);};
    long getSize();
    bool isEnd();

private:
    const char* filePath;
    FILE* fileD = NULL;
};

template<typename type>
void file::read(type *data, size_t length) {
    fread(data, sizeof(type), length, fileD);
}

template<typename type>
void file::write(type *bytes, size_t length) {
    fwrite(bytes, sizeof(type), length, fileD);
}