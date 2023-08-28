#include "clist.h"

void init_list(intrusive_list_t *list) {
    list->length = 0;
    list->head = 0;
}

void add_node(intrusive_list_t *list, intrusive_node_t *node) {
    node->prev = 0;
    node->next = 0;

    if (list->length == 0) {
        list->head = node;
    } else {
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
    }

    ++list->length;
}

void remove_node(intrusive_list_t *list, intrusive_node_t *node) {
    list->length--;

    if (list->length == 0) {
        list->head = 0;
        return;
    }

    if (node == list->head) {
        list->head = node->next;
        node->next->prev = 0;
        return;
    }

    if (node->next)
        node->next->prev = node->prev;
    if (node->prev)
        node->prev->next = node->next;
}
