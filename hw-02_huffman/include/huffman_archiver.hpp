#pragma once

#include "compressed_data.hpp"
#include "decompressed_data.hpp"

#include <vector>

namespace huffman_archiver {
    std::vector<int> calculate_amounts(const std::string &source);

    compressed_data compress(const std::string &source);
    decompressed_data decompress(const std::string &source);
}