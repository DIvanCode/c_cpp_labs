cmake_minimum_required(VERSION 3.16)

set(X_PROJECT_NAME hw-02_huffman)

set(COMMON_SOURCES_SRC
        reader.cpp
        writer.cpp
        logger.cpp
        bytes_representation.cpp
        compressed_data.cpp
        decompressed_data.cpp
        huffman_tree_node.cpp
        huffman_tree.cpp
        huffman_archiver.cpp)

set(COMMON_SOURCES_INCLUDE
        reader.hpp
        writer.hpp
        logger.hpp
        bytes_representation.hpp
        compressed_data.hpp
        decompressed_data.hpp
        huffman_tree_node.hpp
        huffman_tree.hpp
        huffman_archiver.hpp)

set(PROJECT_MAIN src/main.cpp)
set(PROJECT_TEST test/doctest.hpp test/test.cpp)

list(TRANSFORM COMMON_SOURCES_SRC PREPEND src/)
list(TRANSFORM COMMON_SOURCES_INCLUDE PREPEND include/)

set(COMMON_SOURCES ${COMMON_SOURCES_SRC} ${COMMON_SOURCES_INCLUDE})

project(${X_PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror)

set(MAIN_SOURCES ${PROJECT_MAIN} ${COMMON_SOURCES})
set(TEST_SOURCES ${PROJECT_TEST} ${COMMON_SOURCES})

add_executable(${X_PROJECT_NAME} ${MAIN_SOURCES})
target_include_directories(${X_PROJECT_NAME} PRIVATE include)

add_executable(${X_PROJECT_NAME}-test ${TEST_SOURCES})
target_include_directories(${X_PROJECT_NAME}-test PRIVATE include)