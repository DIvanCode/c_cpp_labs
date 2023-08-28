#include "compressed_data.hpp"

compressed_data::compressed_data(std::size_t s_size,
                                 std::size_t c_size,
                                 std::size_t a_size,
                                 std::string data):
    source_size(s_size),
    compressed_size(c_size),
    additional_size(a_size),
    data(std::move(data)) {}