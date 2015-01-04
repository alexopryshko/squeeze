#include <iostream>
#include <vector>
#include "fs/file.h"
#include "lib/node.h"
#include <string>

using std::vector;
using std::string;

class squeeze {
public:
    static void compress(string source_file_path, string source_file_name, string destination_file_path);
    static void decompress(string source_file_path, string source_file_name, string destination_file_path);
};