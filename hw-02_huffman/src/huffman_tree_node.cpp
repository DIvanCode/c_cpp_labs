#include "huffman_tree_node.hpp"

#include <utility>

huffman_tree_node::huffman_tree_node(uint32_t node_id, int total_amount) {
    node_id_ = node_id;
    total_amount_ = total_amount;
    parent_ = nullptr;
    left_child_ = nullptr;
    right_child_ = nullptr;
    incoming_edge_value_ = false;
}

uint32_t huffman_tree_node::node_id() const {
    return node_id_;
}

int huffman_tree_node::total_amount() const {
    return total_amount_;
}

huffman_tree_node * huffman_tree_node::parent() const {
    return parent_;
}

huffman_tree_node * huffman_tree_node::left_child() const {
    return left_child_;
}

huffman_tree_node * huffman_tree_node::right_child() const {
    return right_child_;
}

bool huffman_tree_node::incoming_edge_value() const {
    return incoming_edge_value_;
}

void huffman_tree_node::set_parent(huffman_tree_node *parent, bool incoming_edge_value) {
    parent_ = parent;
    incoming_edge_value_ = incoming_edge_value;
}

void huffman_tree_node::set_left_child(huffman_tree_node *left_child) {
    left_child_ = left_child;
}

void huffman_tree_node::set_right_child(huffman_tree_node *right_child) {
    right_child_ = right_child;
}


bool huffman_tree_node_cmp::operator()(huffman_tree_node *node1, huffman_tree_node *node2) const {
    return std::make_pair(node1->total_amount(), node1->node_id()) <
            std::make_pair(node2->total_amount(), node2->node_id());
}
