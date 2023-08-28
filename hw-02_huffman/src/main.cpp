#include <iostream>
#include "reader.hpp"
#include "writer.hpp"
#include "logger.hpp"
#include "huffman_archiver.hpp"
#include <cstring>

std::string read(const std::string &file_name) {
    reader r(file_name);
    return r.read();
}

void write(const std::string &file_name, const std::string &text) {
    writer w(file_name);
    w.write(text);
}

int main(int argc, char *argv[]) {
    std::string type;
    std::string in_file, out_file;

    int pos = 1;
    while (pos < argc) {
        if (strcmp(argv[pos], "-c") == 0) {
            type = "-c";
            ++pos;
        } else if (strcmp(argv[pos], "-u") == 0) {
            type = "-u";
            ++pos;
        } else if (strcmp(argv[pos], "-f") == 0) {
            in_file = argv[pos + 1];
            pos += 2;
        } else {
            out_file = argv[pos + 1];
            pos += 2;
        }
    }

    if (type == "-c") {
        std::string text = read(in_file);
        compressed_data c_data = huffman_archiver::compress(text);
        std::cout << c_data.source_size << "\n";
        std::cout << c_data.compressed_size << "\n";
        std::cout << c_data.additional_size << "\n";
        write(out_file, c_data.data);
    } else {
        std::string text = read(in_file);
        decompressed_data dc_data = huffman_archiver::decompress(text);
        std::cout << dc_data.compressed_size << "\n";
        std::cout << dc_data.decompressed_size << "\n";
        std::cout << dc_data.additional_size << "\n";
        write(out_file, dc_data.data);
    }
    return 0;
}