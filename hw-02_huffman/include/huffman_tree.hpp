#pragma once

#include "huffman_tree_node.hpp"
#include <vector>
#include <string>

class huffman_tree {
public:
    explicit huffman_tree(const std::vector<int> &amounts);
    explicit huffman_tree(uint32_t alphabet_size);
    ~huffman_tree();

    void build();
    std::string form_additional_info() const;
    std::string get_code(char x) const;

    void add_path(std::string code, char x);
    huffman_tree_node *root();

private:
    std::vector<huffman_tree_node *> nodes_;
    huffman_tree_node *root_;
    bool tree_built_;

    void add_node(huffman_tree_node *node,
                  huffman_tree_node *left_child,
                  huffman_tree_node *right_child);
    void add_edge(uint32_t p_id, uint32_t id, bool edge_value);
};


class huffman_tree_exception: public std::exception {
public:
    explicit huffman_tree_exception(std::string message);
    const char* what() const noexcept override;
private:
    std::string msg_;
};