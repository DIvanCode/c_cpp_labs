#ifndef LAB10_BIN_MANIP_H_INCLUDED
#define LAB10_BIN_MANIP_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstring>

namespace bin_manip {
    struct write_le_int32 {
        int32_t value;

        explicit write_le_int32(int32_t value) : value(value) {}

        friend std::ofstream &operator<<(std::ofstream &out, const write_le_int32 &x);
    };

    struct read_le_int32 {
        int32_t *ptr;

        explicit read_le_int32(int32_t &ptr) : ptr(&ptr) {}

        friend std::ifstream &operator>>(std::ifstream &in, const read_le_int32 &x);
    };

    struct write_bool {
        bool value;

        explicit write_bool(bool value) : value(value) {}

        friend std::ofstream &operator<<(std::ofstream &out, const write_bool &x);
    };

    struct read_bool {
        bool *ptr;

        explicit read_bool(bool &ptr) : ptr(&ptr) {}

        friend std::ifstream &operator>>(std::ifstream &in, const read_bool &x);
    };

    struct write_c_str {
        char *value;

        explicit write_c_str(char *value) : value(value) {}

        friend std::ofstream &operator<<(std::ofstream &out, const write_c_str &x);
    };

    struct read_c_str {
        char **ptr;
        size_t size;

        explicit read_c_str(char *&ptr, size_t size) : ptr(&ptr), size(size) {}

        friend std::ifstream &operator>>(std::ifstream &in, const read_c_str &x);
    };
}

#endif
