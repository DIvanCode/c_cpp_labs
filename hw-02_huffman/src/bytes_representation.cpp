#include <string>

namespace bytes_representation {

std::string uint32_t_to_bytes(uint32_t x) {
    std::string result;
    for (int i = 31; i >= 0; i -= 8) {
        char byte_value = 0;
        for (int bit = 0; bit <= 7; ++bit) {
            byte_value += ((x >> (i - bit) & 1) << (7 - bit));
        }
        result += byte_value;
    }
    return result;
}

char binary_string_to_byte(std::string s) {
    char byte_value = 0;
    for (int bit = 0; bit <= 7; ++bit) {
        byte_value += ((s[bit] - '0') << (7 - bit));
    }
    return byte_value;
}

uint32_t bytes_to_uint32_t(std::string s) {
    uint32_t x = 0;
    for (int i = 0; i < 32; ++i) {
        x += ((uint32_t) ((s[3 - i / 8] >> (i % 8)) & 1) << i);
    }
    return x;
}

std::string byte_to_binary_string(char x) {
    std::string result;
    for (int bit = 0; bit <= 7; ++bit) {
        result += char('0' + ((x >> (7 - bit)) & 1));
    }
    return result;
}

} // bytes_representation