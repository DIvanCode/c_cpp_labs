#pragma once

#include <cstddef>
#include <string>

struct compressed_data {
public:
    std::size_t source_size;
    std::size_t compressed_size;
    std::size_t additional_size;
    std::string data;

    compressed_data(std::size_t s_size,
                    std::size_t c_size,
                    std::size_t a_size,
                    std::string data);
};