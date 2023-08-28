#pragma once

#include "clist.h"

typedef struct point {
    int x;
    int y;
    intrusive_node_t node;
} point_t;

void add_point(intrusive_list_t *list, int x, int y);
void remove_all_points(intrusive_list_t *list);

void print(intrusive_node_t *node, void *data);
void count(intrusive_node_t *node, void *data);
void savetext(intrusive_node_t *node, void *data);
void savebin(intrusive_node_t *node, void *data);