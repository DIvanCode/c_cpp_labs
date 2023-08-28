#pragma once

#include <cstdint>

class huffman_tree_node {
public:
    huffman_tree_node(uint32_t node_id, int total_amount);

    uint32_t node_id() const;
    int total_amount() const;
    huffman_tree_node *parent() const;
    huffman_tree_node *left_child() const;
    huffman_tree_node *right_child() const;
    bool incoming_edge_value() const;

    void set_parent(huffman_tree_node *parent, bool incoming_edge_value);
    void set_left_child(huffman_tree_node *left_child);
    void set_right_child(huffman_tree_node *right_child);

private:
    uint32_t node_id_;
    int total_amount_;
    huffman_tree_node *parent_;
    huffman_tree_node *left_child_;
    huffman_tree_node *right_child_;
    bool incoming_edge_value_;
};

struct huffman_tree_node_cmp {
    bool operator ()(huffman_tree_node *node1, huffman_tree_node *node2) const;
};