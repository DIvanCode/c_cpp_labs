#include "clist.h"

void init_list(intrusive_list_t *list) {
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

void add_node(intrusive_list_t *list, intrusive_node_t *node) {
    node->prev = NULL;
    node->next = NULL;

    if (list->length == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }

    ++list->length;
}

void remove_node(intrusive_list_t *list, intrusive_node_t *node) {
    list->length--;

    if (list->length == 0) {
        list->head = NULL;
        list->tail = NULL;
        return;
    }

    if (node == list->head) {
        list->head = node->next;
        node->next->prev = NULL;
        node->next = NULL;
        return;
    }

    if (node == list->tail) {
        list->tail = node->prev;
        node->prev->next = NULL;
        node->prev = NULL;
        return;
    }

    if (node->next)
        node->next->prev = node->prev;
    if (node->prev)
        node->prev->next = node->next;

    node->next = NULL;
    node->prev = NULL;
}


void apply(intrusive_list_t *list, void (*op)(intrusive_node_t *node, void *data), void *data) {
    intrusive_node_t *curr = list->head;

    while (curr) {
        op(curr, data);
        curr = curr->next;
    }
}