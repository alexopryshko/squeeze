#include "file.h"

bool file::open(const char* flags) {
    return (fileD = fopen(filePath, flags)) != NULL;
}

long file::getSize() {
    long lCurPos, lEndPos;
    lCurPos = ftell(fileD);
    fseek(fileD, 0, 2);
    lEndPos = ftell(fileD);
    fseek(fileD, lCurPos, 0);
    return lEndPos;
}

void file::close() {
    fclose(fileD);
}

bool file::isEnd() {
    return (bool) feof(fileD);
}