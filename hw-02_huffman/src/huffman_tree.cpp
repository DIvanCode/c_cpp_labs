#include "huffman_tree.hpp"

#include "logger.hpp"
#include "bytes_representation.hpp"
#include <algorithm>
#include <set>

huffman_tree::huffman_tree(const std::vector<int> &amounts) {
    for (int x : amounts) {
        add_node(new huffman_tree_node(nodes_.size(), x),
                  nullptr,nullptr);
    }
    root_ = nullptr;
    tree_built_ = false;
}

huffman_tree::huffman_tree(uint32_t alphabet_size) {
    for (size_t i = 0; i < alphabet_size; ++i) {
        add_node(new huffman_tree_node(i, 0),
                  nullptr, nullptr);
    }
    add_node(new huffman_tree_node(alphabet_size, 0),
              nullptr, nullptr);
    root_ = nodes_.back();
    tree_built_ = true;
}

huffman_tree::~huffman_tree() {
    for (huffman_tree_node *&node: nodes_) {
        delete node;
    }
}

void huffman_tree::build() {
    logger::log("started building huffman tree");

    std::set<huffman_tree_node *, huffman_tree_node_cmp> S;
    for (huffman_tree_node *node: nodes_) {
        if (node->total_amount() > 0) {
            S.insert(node);
        }
    }

    if (S.size() == 1) {
        add_node(new huffman_tree_node((int) nodes_.size(), (*S.begin())->total_amount()),
                  *S.begin(), nullptr);
        S.clear();
    }

    while (S.size() > 1) {
        huffman_tree_node *left_child = *S.begin();
        S.erase(S.begin());
        huffman_tree_node *right_child = *S.begin();
        S.erase(S.begin());

        int total_amount = left_child->total_amount() + right_child->total_amount();
        add_node(new huffman_tree_node((int) nodes_.size(), total_amount),
                  left_child, right_child);

        S.insert(nodes_.back());
    }

    root_ = nodes_.back();
    tree_built_ = true;
    logger::log("huffman tree built");
}

std::string huffman_tree::form_additional_info() const {
    logger::log("started forming huffman tree additional info");

    size_t max_code_length = 0;
    for (int i = -128; i < 128; ++i) {
        if (nodes_[i + 128]->total_amount() > 0) {
            std::string code = get_code(i);
            max_code_length = std::max(max_code_length, code.size());
        }
    }
    size_t code_bytes = (max_code_length + 7) / 8;

    std::string result = bytes_representation::uint32_t_to_bytes(code_bytes).substr(2, 2);
    size_t cnt_nes = 0;

    for (int i = -128; i < 128; ++i) {
        char x = char(i + 128);
        if (nodes_[i + 128]->total_amount() > 0) {
            ++cnt_nes;
            std::string code = get_code(i);

            result += x;
            result += bytes_representation::uint32_t_to_bytes(code.size()).substr(2, 2);

            if (code.size() > 8 * code_bytes) {
                throw huffman_tree_exception("Something wrong :(");
            }

            while (code.size() < 8 * code_bytes) {
                code = "0" + code;
            }

            for (size_t b = 0; b < code_bytes; ++b) {
                result += bytes_representation::binary_string_to_byte(code.substr(8 * b, 8));
            }
        }
    }
    std::string cnt_nes_bytes = bytes_representation::
        uint32_t_to_bytes(cnt_nes).substr(2, 2);
    result = cnt_nes_bytes + result;

    logger::log("huffman tree additional info formed");

    return result;
}

std::string huffman_tree::get_code(char x) const {
    if (!tree_built_) {
        throw huffman_tree_exception("tree is not built");
    }

    std::string code;
    huffman_tree_node *node = nodes_[x + 128];
    while (node->parent() != nullptr) {
        code += char('0' + node->incoming_edge_value());
        node = node->parent();
    }
    reverse(code.begin(), code.end());

    return code;
}

void huffman_tree::add_path(std::string code, char x) {
    huffman_tree_node *node = root_;

    for (size_t i = 0; i < code.size(); ++i) {
        char c = code[i];

        if (i == code.size() - 1) {
            add_edge(node->node_id(), int(x) + 128, c - '0');
            continue;
        }

        if (c == '0') {
            if (!node->left_child()) {
                add_node(new huffman_tree_node(nodes_.size(), 0),
                          nullptr, nullptr);
                add_edge(node->node_id(), nodes_.size() - 1, false);
            }
            node = node->left_child();
        } else {
            if (!node->right_child()) {
                add_node(new huffman_tree_node(nodes_.size(), 0),
                          nullptr, nullptr);
                add_edge(node->node_id(), nodes_.size() - 1, true);
            }
            node = node->right_child();
        }
    }
}

huffman_tree_node *huffman_tree::root() {
    return root_;
}

void huffman_tree::add_node(huffman_tree_node *node,
                            huffman_tree_node *left_child,
                            huffman_tree_node *right_child) {
    if (left_child) {
        left_child->set_parent(node, false);
        node->set_left_child(left_child);
    }
    if (right_child) {
        right_child->set_parent(node, true);
        node->set_right_child(right_child);
    }

    nodes_.push_back(node);
}

void huffman_tree::add_edge(uint32_t p_id, uint32_t id, bool edge_value) {
    nodes_[id]->set_parent(nodes_[p_id], edge_value);
    if (!edge_value) {
        nodes_[p_id]->set_left_child(nodes_[id]);
    } else {
        nodes_[p_id]->set_right_child(nodes_[id]);
    }
}

huffman_tree_exception::huffman_tree_exception(std::string message):
    msg_(std::move(message)) {}

const char* huffman_tree_exception::what() const noexcept {
    return msg_.c_str();
}