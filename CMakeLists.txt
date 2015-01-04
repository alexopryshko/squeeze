cmake_minimum_required(VERSION 2.8.4)
project(squeeze)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SOURCE_FILES
    src/main.cpp
    src/lib/heap.cpp
    src/squeeze.cpp
    src/fs/file.cpp
    src/lib/node.cpp
    src/lib/huffman_tree.cpp
    src/lib/utils.cpp
)

add_executable(squeeze ${SOURCE_FILES})