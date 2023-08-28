#include "bin_manip.h"

namespace bin_manip {
    std::ofstream &operator<<(std::ofstream &out, const write_le_int32 &x) {
        out.write((char *) &x.value, sizeof(x.value));
        return out;
    }

    std::ifstream &operator>>(std::ifstream &in, const read_le_int32 &x) {
        in.read((char *) &(*x.ptr), sizeof(*x.ptr));
        return in;
    }

    std::ofstream &operator<<(std::ofstream &out, const write_bool &x) {
        out.write((char *) &x.value, sizeof(x.value));
        return out;
    }

    std::ifstream &operator>>(std::ifstream &in, const read_bool &x) {
        in.read((char *) &(*x.ptr), sizeof(*x.ptr));
        return in;
    }

    std::ofstream &operator<<(std::ofstream &out, const write_c_str &x) {
        for (size_t i = 0; i <= strlen(x.value); ++i) {
            out.write((char *) &(x.value[i]), sizeof(x.value[i]));

            if (x.value[i] == '\0')
                break;
        }

        return out;
    }

    std::ifstream &operator>>(std::ifstream &in, const read_c_str &x) {
        delete[] *x.ptr;

        *x.ptr = new char[x.size];
        std::fill(*x.ptr, *x.ptr + x.size, '\0');

        for (size_t i = 0; i < x.size; ++i) {
            char c;
            in.read((char *) &c, sizeof(c));
            (*x.ptr)[i] = c;

            if (c == '\0')
                break;
        }

        return in;
    }
}