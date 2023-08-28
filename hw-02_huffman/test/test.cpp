#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"


#include "reader.hpp"
#include "writer.hpp"

TEST_CASE("reader-writer test-1") {
    reader r1("test/files/tmp");
    std::string text1 = r1.read();

    writer w("test/files/tmp");
    w.write(text1);

    reader r2("test/files/tmp");
    std::string text2 = r2.read();

    CHECK(text1 == text2);
}

TEST_CASE("reader-writer test-2") {
    writer w("test/files/tmp");

    std::string text1;
    for (int i = -128; i < 128; ++i) {
        text1.push_back(char(i));
    }

    w.write(text1);

    reader r("test/files/tmp");
    std::string text2 = r.read();

    CHECK(text1 == text2);
}

TEST_CASE("reader-writer test-3") {
    writer w("test/files/tmp");
    std::string text1;
    w.write(text1);

    reader r("test/files/tmp");
    std::string text2 = r.read();

    CHECK(text1 == text2);
}

TEST_CASE("reader-writer test-4") {
    writer w("test/files/tmp");
    std::string text1 = "031=ewqe\n023i10f=w-0eir0w\r\n 341290541=4120  АОФЫЛОАТФЫЛОТОТЛФЫ -412!*(){}";
    w.write(text1);

    reader r("test/files/tmp");
    std::string text2 = r.read();

    CHECK(text1 == text2);
}

TEST_CASE("reader-writer test-5") {
    reader r1("test/files/empty");
    std::string text1 = r1.read();

    writer w("test/files/empty");
    w.write(text1);

    reader r2("test/files/empty");
    std::string text2 = r2.read();

    CHECK(text1 == text2);
}


#include "bytes_representation.hpp"

TEST_CASE("bytes_representation test-1") {
    size_t x = 0;
    std::string correct = {char(0),
                           char(0),
                           char(0),
                           char(0)};

    std::string result = bytes_representation::uint32_t_to_bytes(x);

    CHECK(result == correct);
}

TEST_CASE("bytes_representation test-2") {
    uint32_t x = 10;
    std::string correct = {char(0),
                           char(0),
                           char(0),
                           char(10)};

    std::string result = bytes_representation::uint32_t_to_bytes(x);

    CHECK(result == correct);
}

TEST_CASE("bytes_representation test-3") {
    uint32_t x = 312873312;
    std::string correct = {char(x / (256 * 256 * 256) % 256),
                           char(x / (256 * 256) % 256),
                           char(x / 256 % 256),
                           char(x % 256)};

    std::string result = bytes_representation::uint32_t_to_bytes(x);

    CHECK(result == correct);
}

TEST_CASE("bytes_representation test-4") {
    std::string x = "00000000";
    char correct = 0;

    char result = bytes_representation::binary_string_to_byte(x);

    CHECK(result == correct);
}


TEST_CASE("bytes_representation test-5") {
    std::string x = "01011100";
    char correct = char(4+8+16+64);

    char result = bytes_representation::binary_string_to_byte(x);

    CHECK(result == correct);
}

TEST_CASE("bytes_representation test-6") {
    std::string x = "11011100";
    char correct = char(4+8+16+64+128);

    char result = bytes_representation::binary_string_to_byte(x);

    CHECK(result == correct);
}

TEST_CASE("bytes_representation test-7") {
    uint32_t correct = 0;
    std::string x = {char(0),
                     char(0),
                     char(0),
                     char(0)};

    uint32_t result = bytes_representation::bytes_to_uint32_t(x);

    CHECK(result == correct);
}

TEST_CASE("bytes_representation test-8") {
    uint32_t correct = 10;
    std::string x = {char(0),
                     char(0),
                     char(0),
                     char(10)};

    uint32_t result = bytes_representation::bytes_to_uint32_t(x);

    CHECK(result == correct);
}

TEST_CASE("bytes_representation test-9") {
    uint32_t correct = 312873312;
    std::string x = {char(correct / (256 * 256 * 256) % 256),
                     char(correct / (256 * 256) % 256),
                     char(correct / 256 % 256),
                     char(correct % 256)};

    uint32_t result = bytes_representation::bytes_to_uint32_t(x);

    CHECK(result == correct);
}

TEST_CASE("bytes_representation test-10") {
    char x = 0;
    std::string correct = "00000000";

    std::string result = bytes_representation::byte_to_binary_string(x);

    CHECK(result == correct);
}


TEST_CASE("bytes_representation test-11") {
    char x = char(4+8+16+64);
    std::string correct = "01011100";

    std::string result = bytes_representation::byte_to_binary_string(x);

    CHECK(result == correct);
}

TEST_CASE("bytes_representation test-12") {
    char x = char(4+8+16+64+128);
    std::string correct = "11011100";

    std::string result = bytes_representation::byte_to_binary_string(x);

    CHECK(result == correct);
}


#include "huffman_tree_node.hpp"

TEST_CASE("huffman_tree_node test-1") {
    huffman_tree_node node(0, 10);

    CHECK(node.node_id() == 0);
    CHECK(node.total_amount() == 10);
    CHECK(node.parent() == nullptr);
    CHECK(node.left_child() == nullptr);
    CHECK(node.right_child() == nullptr);
    CHECK(node.incoming_edge_value() == false);
}

TEST_CASE("huffman_tree_node test-2") {
    huffman_tree_node node(10000, 0);

    CHECK(node.node_id() == 10000);
    CHECK(node.total_amount() == 0);
    CHECK(node.parent() == nullptr);
    CHECK(node.left_child() == nullptr);
    CHECK(node.right_child() == nullptr);
    CHECK(node.incoming_edge_value() == false);
}

TEST_CASE("huffman_tree_node test-3") {
    huffman_tree_node node(938217, 19732819);

    CHECK(node.node_id() == 938217);
    CHECK(node.total_amount() == 19732819);
    CHECK(node.parent() == nullptr);
    CHECK(node.left_child() == nullptr);
    CHECK(node.right_child() == nullptr);
    CHECK(node.incoming_edge_value() == false);
}

TEST_CASE("huffman_tree_node test-4") {
    huffman_tree_node *node = new huffman_tree_node(0, 10);

    CHECK(node->node_id() == 0);
    CHECK(node->total_amount() == 10);
    CHECK(node->parent() == nullptr);
    CHECK(node->left_child() == nullptr);
    CHECK(node->right_child() == nullptr);
    CHECK(node->incoming_edge_value() == false);
}

TEST_CASE("huffman_tree_node test-5") {
    huffman_tree_node *node = new huffman_tree_node(10000, 0);

    CHECK(node->node_id() == 10000);
    CHECK(node->total_amount() == 0);
    CHECK(node->parent() == nullptr);
    CHECK(node->left_child() == nullptr);
    CHECK(node->right_child() == nullptr);
    CHECK(node->incoming_edge_value() == false);
}

TEST_CASE("huffman_tree_node test-6") {
    huffman_tree_node *node = new huffman_tree_node(938217, 19732819);

    CHECK(node->node_id() == 938217);
    CHECK(node->total_amount() == 19732819);
    CHECK(node->parent() == nullptr);
    CHECK(node->left_child() == nullptr);
    CHECK(node->right_child() == nullptr);
    CHECK(node->incoming_edge_value() == false);
}

TEST_CASE("huffman_tree_node test-7") {
    huffman_tree_node *node = new huffman_tree_node(0, 1);
    huffman_tree_node *parent = new huffman_tree_node(1, 2);

    node->set_parent(parent, false);

    CHECK(node->node_id() == 0);
    CHECK(node->total_amount() == 1);
    CHECK(node->parent() == parent);
    CHECK(node->left_child() == nullptr);
    CHECK(node->right_child() == nullptr);
    CHECK(node->incoming_edge_value() == false);
}

TEST_CASE("huffman_tree_node test-8") {
    huffman_tree_node *node = new huffman_tree_node(0, 1);
    huffman_tree_node *parent = new huffman_tree_node(1, 2);

    node->set_parent(parent, true);

    CHECK(node->node_id() == 0);
    CHECK(node->total_amount() == 1);
    CHECK(node->parent() == parent);
    CHECK(node->left_child() == nullptr);
    CHECK(node->right_child() == nullptr);
    CHECK(node->incoming_edge_value() == true);
}

TEST_CASE("huffman_tree_node test-9") {
    huffman_tree_node *node = new huffman_tree_node(0, 1);
    huffman_tree_node *left_child = new huffman_tree_node(1, 2);

    node->set_left_child(left_child);

    CHECK(node->node_id() == 0);
    CHECK(node->total_amount() == 1);
    CHECK(node->parent() == nullptr);
    CHECK(node->left_child() == left_child);
    CHECK(node->right_child() == nullptr);
    CHECK(node->incoming_edge_value() == false);
}

TEST_CASE("huffman_tree_node test-10") {
    huffman_tree_node *node = new huffman_tree_node(0, 1);
    huffman_tree_node *right_child = new huffman_tree_node(1, 2);

    node->set_right_child(right_child);

    CHECK(node->node_id() == 0);
    CHECK(node->total_amount() == 1);
    CHECK(node->parent() == nullptr);
    CHECK(node->left_child() == nullptr);
    CHECK(node->right_child() == right_child);
    CHECK(node->incoming_edge_value() == false);
}

TEST_CASE("huffman_tree_node test-11") {
    huffman_tree_node *node = new huffman_tree_node(0, 1);
    huffman_tree_node *left_child = new huffman_tree_node(1, 2);
    huffman_tree_node *right_child = new huffman_tree_node(2, 10);
    huffman_tree_node *parent = new huffman_tree_node(2, 10);

    node->set_parent(parent, false);
    node->set_left_child(left_child);
    node->set_right_child(right_child);

    CHECK(node->node_id() == 0);
    CHECK(node->total_amount() == 1);
    CHECK(node->parent() == parent);
    CHECK(node->left_child() == left_child);
    CHECK(node->right_child() == right_child);
    CHECK(node->incoming_edge_value() == false);
}

TEST_CASE("huffman_tree_node test-12") {
    huffman_tree_node *node = new huffman_tree_node(0, 1);
    huffman_tree_node *left_child = new huffman_tree_node(1, 2);
    huffman_tree_node *right_child = new huffman_tree_node(2, 10);
    huffman_tree_node *parent = new huffman_tree_node(2, 10);

    node->set_parent(parent, true);
    node->set_left_child(left_child);
    node->set_right_child(right_child);

    CHECK(node->node_id() == 0);
    CHECK(node->total_amount() == 1);
    CHECK(node->parent() == parent);
    CHECK(node->left_child() == left_child);
    CHECK(node->right_child() == right_child);
    CHECK(node->incoming_edge_value() == true);
}

TEST_CASE("huffman_tree_node test-13") {
    huffman_tree_node *node1 = new huffman_tree_node(1, 10);
    huffman_tree_node *node2 = new huffman_tree_node(2, 11);

    CHECK(node1 < node2);
}

TEST_CASE("huffman_tree_node test-14") {
    huffman_tree_node *node1 = new huffman_tree_node(1, 10);
    huffman_tree_node *node2 = new huffman_tree_node(2, 10);

    CHECK(node1 < node2);
}


#include "huffman_tree.hpp"
#include <vector>
#include <unordered_map>

TEST_CASE("huffman_tree test-1") {
    std::vector<int> amounts(256, 0);

    huffman_tree tree(amounts);
    tree.build();

    for (int i = -128; i < 128; ++i) {
        std::string code = tree.get_code(char(i));

        CHECK(code.size() == 0);
    }
}

TEST_CASE("huffman_tree test-2") {
    std::vector<int> amounts(256, 1);

    huffman_tree tree(amounts);
    tree.build();

    for (int i = -128; i < 128; ++i) {
        std::string code = tree.get_code(char(i));

        std::string correct_code;
        for (int bit = 0; bit < 8; ++bit) {
            correct_code += char('0' + ((i + 128) >> (7 - bit) & 1));
        }

        CHECK(code == correct_code);
    }
}

TEST_CASE("huffman_tree test-3") {
    std::string text = "aaaaa";

    std::unordered_map<char, std::string> correct_codes;
    correct_codes['a'] = "0";

    std::vector<int> amounts(256, 0);
    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    for (int i = -128; i < 128; ++i) {
        std::string code = tree.get_code(char(i));

        if (amounts[i + 128] == 0) {
            CHECK(code.size() == 0);
            continue;
        }

        CHECK(code == correct_codes[char(i)]);
    }
}


TEST_CASE("huffman_tree test-4") {
    std::string text = "abacaba";

    std::unordered_map<char, std::string> correct_codes;
    correct_codes['a'] = "1";
    correct_codes['b'] = "01";
    correct_codes['c'] = "00";

    std::vector<int> amounts(256, 0);
    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    for (int i = -128; i < 128; ++i) {
        std::string code = tree.get_code(char(i));

        if (amounts[i + 128] == 0) {
            CHECK(code.size() == 0);
            continue;
        }

        CHECK(code == correct_codes[char(i)]);
    }
}

TEST_CASE("huffman_tree test-5") {
    std::string text = "abaccabba";

    std::unordered_map<char, std::string> correct_codes;
    correct_codes['a'] = "0";
    correct_codes['b'] = "11";
    correct_codes['c'] = "10";

    std::vector<int> amounts(256, 0);
    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    for (int i = -128; i < 128; ++i) {
        std::string code = tree.get_code(char(i));

        if (amounts[i + 128] == 0) {
            CHECK(code.size() == 0);
            continue;
        }

        CHECK(code == correct_codes[char(i)]);
    }
}

TEST_CASE("huffman_tree test-6") {
    std::string text = "Hello, World! My name is Ivan)";

    std::unordered_map<char, std::string> correct_codes;
    correct_codes[' '] = "111";
    correct_codes['!'] = "10000";
    correct_codes[')'] = "10001";
    correct_codes[','] = "10010";
    correct_codes['H'] = "10011";
    correct_codes['I'] = "10100";
    correct_codes['M'] = "10101";
    correct_codes['W'] = "10110";
    correct_codes['a'] = "0100";
    correct_codes['d'] = "10111";
    correct_codes['e'] = "0101";
    correct_codes['i'] = "11000";
    correct_codes['l'] = "001";
    correct_codes['m'] = "11001";
    correct_codes['n'] = "0110";
    correct_codes['o'] = "0111";
    correct_codes['r'] = "11010";
    correct_codes['s'] = "11011";
    correct_codes['v'] = "0000";
    correct_codes['y'] = "0001";

    std::vector<int> amounts(256, 0);
    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    for (int i = -128; i < 128; ++i) {
        std::string code = tree.get_code(char(i));

        if (amounts[i + 128] == 0) {
            CHECK(code.size() == 0);
            continue;
        }

        CHECK(code == correct_codes[char(i)]);
    }
}

TEST_CASE("huffman_tree test-7") {
    std::vector<int> amounts(256, 0);

    huffman_tree tree(amounts);
    tree.build();

    std::string result = tree.form_additional_info();
    std::string correct = {char(0),
                           char(0)};

    CHECK(result == correct);
}

TEST_CASE("huffman_tree test-8") {
    std::vector<int> amounts(256, 1);

    huffman_tree tree(amounts);
    tree.build();

    std::string result = tree.form_additional_info();
    std::string correct = {char(1),
                           char(0)};
    for (int i = -128; i < 128; ++i) {
        char x = char(i + 128);

        correct += x;
        correct += char(8);
        correct += x;
    }

    CHECK(result == correct);
}

TEST_CASE("huffman_tree test-9") {
    std::string text = "aaaaa";

    std::unordered_map<char, std::string> correct_codes;
    correct_codes['a'] = "0";

    std::vector<int> amounts(256, 0);
    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    std::string result = tree.form_additional_info();
    std::string correct = {char(0),
                           char(1),
                           char('a' + 128),
                           char(1),
                           char(0)};

    CHECK(result == correct);
}

TEST_CASE("huffman_tree test-10") {
    std::string text = "abaccabba";

    std::unordered_map<char, std::string> correct_codes;
    correct_codes['a'] = "0";
    correct_codes['b'] = "11";
    correct_codes['c'] = "10";

    std::vector<int> amounts(256, 0);
    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    std::string result = tree.form_additional_info();
    std::string correct = {char(0),
                           char(3),
                           char('a' + 128),
                           char(1),
                           char(0),
                           char('b' + 128),
                           char(2),
                           char(3),
                           char('c' + 128),
                           char(2),
                           char(2)};

    CHECK(result == correct);
}

TEST_CASE("huffman_tree test-11") {
    std::string text = "Hello, World! My name is Ivan)";

    std::unordered_map<char, std::string> correct_codes;
    correct_codes[' '] = "111";
    correct_codes['!'] = "10000";
    correct_codes[')'] = "10001";
    correct_codes[','] = "10010";
    correct_codes['H'] = "10011";
    correct_codes['I'] = "10100";
    correct_codes['M'] = "10101";
    correct_codes['W'] = "10110";
    correct_codes['a'] = "0100";
    correct_codes['d'] = "10111";
    correct_codes['e'] = "0101";
    correct_codes['i'] = "11000";
    correct_codes['l'] = "001";
    correct_codes['m'] = "11001";
    correct_codes['n'] = "0110";
    correct_codes['o'] = "0111";
    correct_codes['r'] = "11010";
    correct_codes['s'] = "11011";
    correct_codes['v'] = "0000";
    correct_codes['y'] = "0001";

    std::vector<int> amounts(256, 0);
    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    std::string result = tree.form_additional_info();
    std::string correct = {char(0),
                           char(correct_codes.size())};
    for (int i = -128; i < 128; ++i) {
        if (amounts[int(i) + 128] == 0) {
            continue;
        }

        char x = char(i + 128);

        correct += x;
        correct += char(correct_codes[i].size());

        char code = 0;
        for (size_t bit = 0; bit < correct_codes[i].size(); ++bit) {
            code += ((correct_codes[i][correct_codes[i].size() - bit - 1] - '0') << bit);
        }

        correct += code;
    }

    CHECK(result == correct);
}

TEST_CASE("huffman_tree test-12") {
    huffman_tree tree(256);

    for (int i = -128; i < 128; ++i) {
        std::string correct_code = "";
        std::string result = tree.get_code(char(i));

        CHECK(correct_code == result);
    }
}

TEST_CASE("huffman_tree test-13") {
    std::unordered_map<char, std::string> correct_codes;
    for (int i = -128; i < 128; ++i) {
        std::string correct_code;
        for (int bit = 0; bit < 8; ++bit) {
            correct_code += char('0' + ((i + 128) >> (7 - bit) & 1));
        }
        correct_codes[char(i)] = correct_code;
    }

    huffman_tree tree(256);

    for (int i = -128; i < 128; ++i) {
        tree.add_path(correct_codes[char(i)], i);
    }

    for (int i = -128; i < 128; ++i) {
        std::string correct = correct_codes[char(i)];
        std::string result = tree.get_code(char(i));

        CHECK(correct == result);
    }
}

TEST_CASE("huffman_tree test-14") {
    std::unordered_map<char, std::string> correct_codes;
    correct_codes['a'] = "0";

    huffman_tree tree(256);

    for (int i = -128; i < 128; ++i) {
        if (correct_codes.find(char(i)) != correct_codes.end()) {
            tree.add_path(correct_codes[char(i)], i);
        }
    }

    for (int i = -128; i < 128; ++i) {
        std::string correct = correct_codes[char(i)];
        std::string result = tree.get_code(char(i));

        CHECK(correct == result);
    }
}

TEST_CASE("huffman_tree test-15") {
    std::unordered_map<char, std::string> correct_codes;
    correct_codes['a'] = "0";
    correct_codes['b'] = "11";
    correct_codes['c'] = "10";

    huffman_tree tree(256);

    for (int i = -128; i < 128; ++i) {
        if (correct_codes.find(char(i)) != correct_codes.end()) {
            tree.add_path(correct_codes[char(i)], i);
        }
    }

    for (int i = -128; i < 128; ++i) {
        std::string correct = correct_codes[char(i)];
        std::string result = tree.get_code(char(i));

        CHECK(correct == result);
    }
}

TEST_CASE("huffman_tree test-16") {
    std::unordered_map<char, std::string> correct_codes;
    correct_codes[' '] = "111";
    correct_codes['!'] = "10000";
    correct_codes[')'] = "10001";
    correct_codes[','] = "10010";
    correct_codes['H'] = "10011";
    correct_codes['I'] = "10100";
    correct_codes['M'] = "10101";
    correct_codes['W'] = "10110";
    correct_codes['a'] = "0100";
    correct_codes['d'] = "10111";
    correct_codes['e'] = "0101";
    correct_codes['i'] = "11000";
    correct_codes['l'] = "001";
    correct_codes['m'] = "11001";
    correct_codes['n'] = "0110";
    correct_codes['o'] = "0111";
    correct_codes['r'] = "11010";
    correct_codes['s'] = "11011";
    correct_codes['v'] = "0000";
    correct_codes['y'] = "0001";

    huffman_tree tree(256);

    for (int i = -128; i < 128; ++i) {
        if (correct_codes.find(char(i)) != correct_codes.end()) {
            tree.add_path(correct_codes[char(i)], i);
        }
    }

    for (int i = -128; i < 128; ++i) {
        std::string correct = correct_codes[char(i)];
        std::string result = tree.get_code(char(i));

        CHECK(correct == result);
    }
}


#include "huffman_archiver.hpp"
#include "compressed_data.hpp"
#include "decompressed_data.hpp"

TEST_CASE("huffman_archiver test-1") {
    std::string text;
    std::vector<int> amounts(256, 0);

    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    std::string tree_info = tree.form_additional_info();
    std::string correct_compressed;

    size_t additional_size = 12 + tree_info.size();
    size_t compressed_size = additional_size + correct_compressed.size();

    std::string additional_info = {char(text.size() / (256 * 256 * 256) % 256),
                                   char(text.size() / (256 * 256) % 256),
                                   char(text.size() / 256 % 256),
                                   char(text.size() % 256),
                                   char(compressed_size / (256 * 256 * 256) % 256),
                                   char(compressed_size / (256 * 256) % 256),
                                   char(compressed_size / 256 % 256),
                                   char(compressed_size % 256),
                                   char(additional_size / (256 * 256 * 256) % 256),
                                   char(additional_size / (256 * 256) % 256),
                                   char(additional_size / 256 % 256),
                                   char(additional_size % 256)};
    additional_info += tree_info;
    std::string correct_data = additional_info + correct_compressed;
    compressed_data correct(text.size(), correct_data.size(), additional_info.size(), correct_data);

    compressed_data result = huffman_archiver::compress(text);

    CHECK(correct.source_size == result.source_size);
    CHECK(correct.compressed_size == result.compressed_size + result.additional_size);
    CHECK(correct.additional_size == result.additional_size);
    CHECK(correct.data == result.data);
}

TEST_CASE("huffman_archiver test-2") {
    std::string text;
    for (int i = -128; i < 128; ++i) {
        text += char(i);
    }

    std::vector<int> amounts(256, 0);

    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    std::string tree_info = tree.form_additional_info();

    std::string correct_compressed;
    for (char x : text) {
        correct_compressed += bytes_representation::binary_string_to_byte(tree.get_code(x));
    }

    size_t additional_size = 12 + tree_info.size();
    size_t compressed_size = additional_size + correct_compressed.size();

    std::string additional_info = {char(text.size() / (256 * 256 * 256) % 256),
                                   char(text.size() / (256 * 256) % 256),
                                   char(text.size() / 256 % 256),
                                   char(text.size() % 256),
                                   char(compressed_size / (256 * 256 * 256) % 256),
                                   char(compressed_size / (256 * 256) % 256),
                                   char(compressed_size / 256 % 256),
                                   char(compressed_size % 256),
                                   char(additional_size / (256 * 256 * 256) % 256),
                                   char(additional_size / (256 * 256) % 256),
                                   char(additional_size / 256 % 256),
                                   char(additional_size % 256)};
    additional_info += tree_info;
    std::string correct_data = additional_info + correct_compressed;
    compressed_data correct(text.size(), correct_data.size(), additional_info.size(), correct_data);

    compressed_data result = huffman_archiver::compress(text);

    CHECK(correct.source_size == result.source_size);
    CHECK(correct.compressed_size == result.compressed_size + result.additional_size);
    CHECK(correct.additional_size == result.additional_size);
    CHECK(correct.data == result.data);
}

TEST_CASE("huffman_archiver test-3") {
    std::string text = "aaaaa";

    std::vector<int> amounts(256, 0);

    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    std::string tree_info = tree.form_additional_info();

    std::string correct_compressed = {0};

    size_t additional_size = 12 + tree_info.size();
    size_t compressed_size = additional_size + correct_compressed.size();

    std::string additional_info = {char(text.size() / (256 * 256 * 256) % 256),
                                   char(text.size() / (256 * 256) % 256),
                                   char(text.size() / 256 % 256),
                                   char(text.size() % 256),
                                   char(compressed_size / (256 * 256 * 256) % 256),
                                   char(compressed_size / (256 * 256) % 256),
                                   char(compressed_size / 256 % 256),
                                   char(compressed_size % 256),
                                   char(additional_size / (256 * 256 * 256) % 256),
                                   char(additional_size / (256 * 256) % 256),
                                   char(additional_size / 256 % 256),
                                   char(additional_size % 256)};
    additional_info += tree_info;
    std::string correct_data = additional_info + correct_compressed;
    compressed_data correct(text.size(), correct_data.size(), additional_info.size(), correct_data);

    compressed_data result = huffman_archiver::compress(text);

    CHECK(correct.source_size == result.source_size);
    CHECK(correct.compressed_size == result.compressed_size + result.additional_size);
    CHECK(correct.additional_size == result.additional_size);
    CHECK(correct.data == result.data);
}

TEST_CASE("huffman_archiver test-4") {
    std::string text = "aaaaaaaaa";

    std::vector<int> amounts(256, 0);

    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    std::string tree_info = tree.form_additional_info();

    std::string correct_compressed = {0, 0};

    size_t additional_size = 12 + tree_info.size();
    size_t compressed_size = additional_size + correct_compressed.size();

    std::string additional_info = {char(text.size() / (256 * 256 * 256) % 256),
                                   char(text.size() / (256 * 256) % 256),
                                   char(text.size() / 256 % 256),
                                   char(text.size() % 256),
                                   char(compressed_size / (256 * 256 * 256) % 256),
                                   char(compressed_size / (256 * 256) % 256),
                                   char(compressed_size / 256 % 256),
                                   char(compressed_size % 256),
                                   char(additional_size / (256 * 256 * 256) % 256),
                                   char(additional_size / (256 * 256) % 256),
                                   char(additional_size / 256 % 256),
                                   char(additional_size % 256)};
    additional_info += tree_info;
    std::string correct_data = additional_info + correct_compressed;
    compressed_data correct(text.size(), correct_data.size(), additional_info.size(), correct_data);

    compressed_data result = huffman_archiver::compress(text);

    CHECK(correct.source_size == result.source_size);
    CHECK(correct.compressed_size == result.compressed_size + result.additional_size);
    CHECK(correct.additional_size == result.additional_size);
    CHECK(correct.data == result.data);
}

TEST_CASE("huffman_archiver test-5") {
    std::string text = "abaccabba";

    std::vector<int> amounts(256, 0);

    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    std::string tree_info = tree.form_additional_info();

    //01101010 01111.000
    std::string correct_compressed = {char(2+8+32+64), char(8+16+32+64)};

    size_t additional_size = 12 + tree_info.size();
    size_t compressed_size = additional_size + correct_compressed.size();

    std::string additional_info = {char(text.size() / (256 * 256 * 256) % 256),
                                   char(text.size() / (256 * 256) % 256),
                                   char(text.size() / 256 % 256),
                                   char(text.size() % 256),
                                   char(compressed_size / (256 * 256 * 256) % 256),
                                   char(compressed_size / (256 * 256) % 256),
                                   char(compressed_size / 256 % 256),
                                   char(compressed_size % 256),
                                   char(additional_size / (256 * 256 * 256) % 256),
                                   char(additional_size / (256 * 256) % 256),
                                   char(additional_size / 256 % 256),
                                   char(additional_size % 256)};
    additional_info += tree_info;
    std::string correct_data = additional_info + correct_compressed;
    compressed_data correct(text.size(), correct_data.size(), additional_info.size(), correct_data);

    compressed_data result = huffman_archiver::compress(text);

    CHECK(correct.source_size == result.source_size);
    CHECK(correct.compressed_size == result.compressed_size + result.additional_size);
    CHECK(correct.additional_size == result.additional_size);
    CHECK(correct.data == result.data);
}

TEST_CASE("huffman_archiver test-6") {
    std::string text = "Hello, World! My name is Ivan)";

    std::vector<int> amounts(256, 0);

    for (char x : text) {
        ++amounts[int(x) + 128];
    }

    huffman_tree tree(amounts);
    tree.build();

    std::string tree_info = tree.form_additional_info();

    // 10011010 10010010 11110010 11110110 01111101 00011011 11000011 11010100
    // 01111011 00100110 01010111 11100011 01111110 10000000 10001101 0001.0000
    std::string correct_compressed = {char(2+8+16+128),
                                      char(2+16+128),
                                      char(2+16+32+64+128),
                                      char(2+4+16+32+64+128),
                                      char(1+4+8+16+32+64),
                                      char(1+2+8+16),
                                      char(1+2+64+128),
                                      char(4+16+64+128),
                                      char(1+2+8+16+32+64),
                                      char(2+4+32),
                                      char(1+2+4+16+64),
                                      char(1+2+32+64+128),
                                      char(2+4+8+16+32+64),
                                      char(128),
                                      char(1+4+8+128),
                                      char(16)};

    size_t additional_size = 12 + tree_info.size();
    size_t compressed_size = additional_size + correct_compressed.size();

    std::string additional_info = {char(text.size() / (256 * 256 * 256) % 256),
                                   char(text.size() / (256 * 256) % 256),
                                   char(text.size() / 256 % 256),
                                   char(text.size() % 256),
                                   char(compressed_size / (256 * 256 * 256) % 256),
                                   char(compressed_size / (256 * 256) % 256),
                                   char(compressed_size / 256 % 256),
                                   char(compressed_size % 256),
                                   char(additional_size / (256 * 256 * 256) % 256),
                                   char(additional_size / (256 * 256) % 256),
                                   char(additional_size / 256 % 256),
                                   char(additional_size % 256)};
    additional_info += tree_info;
    std::string correct_data = additional_info + correct_compressed;
    compressed_data correct(text.size(), correct_data.size(), additional_info.size(), correct_data);

    compressed_data result = huffman_archiver::compress(text);

    CHECK(correct.source_size == result.source_size);
    CHECK(correct.compressed_size == result.compressed_size + result.additional_size);
    CHECK(correct.additional_size == result.additional_size);
    CHECK(correct.data == result.data);
}

TEST_CASE("huffman_archiver test-7") {
    std::string text;
    compressed_data compressed = huffman_archiver::compress(text);

    decompressed_data correct(compressed.data.size(),
                              text.size(),
                              compressed.additional_size,
                              text);

    decompressed_data result = huffman_archiver::decompress(compressed.data);

    CHECK(correct.compressed_size == result.compressed_size + result.additional_size);
    CHECK(correct.decompressed_size == result.decompressed_size);
    CHECK(correct.additional_size == result.additional_size);
    CHECK(correct.data == result.data);
}

TEST_CASE("huffman_archiver test-8") {
    std::string text;
    for (int i = -128; i < 128; ++i) {
        text += char(i);
    }

    compressed_data compressed = huffman_archiver::compress(text);

    decompressed_data correct(compressed.data.size(),
                              text.size(),
                              compressed.additional_size,
                              text);

    decompressed_data result = huffman_archiver::decompress(compressed.data);

    CHECK(correct.compressed_size == result.compressed_size + result.additional_size);
    CHECK(correct.decompressed_size == result.decompressed_size);
    CHECK(correct.additional_size == result.additional_size);
    CHECK(correct.data == result.data);
}

TEST_CASE("huffman_archiver test-9") {
    std::string text = "aaaaa";

    compressed_data compressed = huffman_archiver::compress(text);

    decompressed_data correct(compressed.data.size(),
                              text.size(),
                              compressed.additional_size,
                              text);

    decompressed_data result = huffman_archiver::decompress(compressed.data);

    CHECK(correct.compressed_size == result.compressed_size + result.additional_size);
    CHECK(correct.decompressed_size == result.decompressed_size);
    CHECK(correct.additional_size == result.additional_size);
    CHECK(correct.data == result.data);
}

TEST_CASE("huffman_archiver test-10") {
    std::string text = "aaaaaaaaaa";

    compressed_data compressed = huffman_archiver::compress(text);

    decompressed_data correct(compressed.data.size(),
                              text.size(),
                              compressed.additional_size,
                              text);

    decompressed_data result = huffman_archiver::decompress(compressed.data);

    CHECK(correct.compressed_size == result.compressed_size + result.additional_size);
    CHECK(correct.decompressed_size == result.decompressed_size);
    CHECK(correct.additional_size == result.additional_size);
    CHECK(correct.data == result.data);
}

TEST_CASE("huffman_archiver test-11") {
    std::string text = "abajjuuuuuuuybba";

    compressed_data compressed = huffman_archiver::compress(text);

    decompressed_data correct(compressed.data.size(),
                              text.size(),
                              compressed.additional_size,
                              text);

    decompressed_data result = huffman_archiver::decompress(compressed.data);

    CHECK(correct.compressed_size == result.compressed_size + result.additional_size);
    CHECK(correct.decompressed_size == result.decompressed_size);
    CHECK(correct.additional_size == result.additional_size);
    CHECK(correct.data == result.data);
}

TEST_CASE("huffman_archiver test-12") {
    std::string text = "Hello, World! My name is Ivan)";

    compressed_data compressed = huffman_archiver::compress(text);

    decompressed_data correct(compressed.data.size(),
                              text.size(),
                              compressed.additional_size,
                              text);

    decompressed_data result = huffman_archiver::decompress(compressed.data);

    CHECK(correct.compressed_size == result.compressed_size + result.additional_size);
    CHECK(correct.decompressed_size == result.decompressed_size);
    CHECK(correct.additional_size == result.additional_size);
    CHECK(correct.data == result.data);
}