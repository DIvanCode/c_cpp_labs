#pragma once

#include <string>

namespace bytes_representation {
    std::string uint32_t_to_bytes(uint32_t x);
    char binary_string_to_byte(std::string s);

    uint32_t bytes_to_uint32_t(std::string s);
    std::string byte_to_binary_string(char x);
}