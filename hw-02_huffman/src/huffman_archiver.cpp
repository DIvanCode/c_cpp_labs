#include "huffman_archiver.hpp"

#include "logger.hpp"
#include "bytes_representation.hpp"
#include "huffman_tree.hpp"

namespace huffman_archiver {

std::vector<int> calculate_amounts(const std::string &source) {
    logger::log("started calculating amounts");

    std::vector<int> amounts(256);
    for (char x: source) {
        amounts[x + 128]++;
    }

    logger::log("amounts calculated");
    return amounts;
}

compressed_data compress(const std::string &source) {
    logger::log("compress starts");

    std::vector<int> amounts = calculate_amounts(source);

    huffman_tree tree(amounts);
    tree.build();

    std::string binary_result;
    for (char x: source) {
        binary_result += tree.get_code(x);
    }
    while (binary_result.size() % 8 != 0) {
        binary_result += '0';
    }

    size_t result_bytes = binary_result.size() / 8;
    std::string result;
    for (size_t i = 0; i < binary_result.size(); i += 8) {
        result += bytes_representation::binary_string_to_byte(binary_result.substr(i, 8));
    }

    std::string tree_info = tree.form_additional_info();
    size_t additional_size = tree_info.size() + 12;
    result = bytes_representation::uint32_t_to_bytes(source.size()) +
             bytes_representation::uint32_t_to_bytes(result_bytes + additional_size) +
             bytes_representation::uint32_t_to_bytes(additional_size) +
             tree_info + result;

    logger::log("compress ends");

    return {source.size(),
            result_bytes,
            additional_size,
            result};
}

decompressed_data decompress(const std::string &source) {
    logger::log("decompress starts");

    size_t decompressed_size = bytes_representation::bytes_to_uint32_t(source.substr(0, 4));
    size_t compressed_size = bytes_representation::bytes_to_uint32_t(source.substr(4, 4));
    size_t additional_size = bytes_representation::bytes_to_uint32_t(source.substr(8, 4));

    std::string cnt_nes_bytes = {0, 0, source[12], source[13]};
    size_t cnt_nes = bytes_representation::bytes_to_uint32_t(cnt_nes_bytes);

    std::string code_bytes = {0, 0, source[14], source[15]};
    size_t code_length = bytes_representation::bytes_to_uint32_t(code_bytes);


    std::vector<std::string> codes(256);
    for (size_t i = 0; i < cnt_nes; ++i) {
        char x = char(source[16 + (3 + code_length) * i] - 128);

        std::string code_size_bytes = {0, 0,
                                       source[16 + (3 + code_length) * i + 1],
                                       source[16 + (3 + code_length) * i + 2]};
        size_t code_size = bytes_representation::
            bytes_to_uint32_t(code_size_bytes);

        std::string code;
        for (size_t b = 0; b < code_length; ++b) {
            code += bytes_representation::
                    byte_to_binary_string(source[16 + (3 + code_length) * i + 3 + b]);
        }

        codes[int(x) + 128] = code.substr(8 * code_length - code_size, code_size);
    }

    huffman_tree tree(256);
    for (int i = -128; i < 128; ++i) {
        if (codes[i + 128].size() > 0) {
            tree.add_path(codes[i + 128], char(i));
        }
    }

    std::string text = source.substr(additional_size, source.size() - additional_size);

    std::string result;
    huffman_tree_node *node = tree.root();
    for (char b: text) {
        std::string current_byte = bytes_representation::byte_to_binary_string(b);
        for (char x: current_byte) {
            if (x == '0') {
                node = node->left_child();
            } else {
                node = node->right_child();
            }

            if (!node->left_child() && !node->right_child()) {
                result += char(int(node->node_id()) - 128);
                if (result.size() == decompressed_size) {
                    break;
                }

                node = tree.root();
            }
        }
    }
    logger::log("decompress ends");
    return {compressed_size - additional_size,
            decompressed_size,
            additional_size,
            result};
}

} // huffman_archiver