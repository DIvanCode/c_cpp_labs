#pragma once

#include <cstddef>
#include <string>

struct decompressed_data {
public:
    std::size_t compressed_size;
    std::size_t decompressed_size;
    std::size_t additional_size;
    std::string data;

    decompressed_data(std::size_t c_size,
                      std::size_t dc_size,
                      std::size_t a_size,
                      std::string data);
};