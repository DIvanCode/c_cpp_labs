#include "decompressed_data.hpp"

decompressed_data::decompressed_data(std::size_t c_size,
                                     std::size_t dc_size,
                                     std::size_t a_size,
                                     std::string data):
    compressed_size(c_size),
    decompressed_size(dc_size),
    additional_size(a_size),
    data(std::move(data)) {}