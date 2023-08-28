#include "point_list.h"
#include "clist.h"

#include <malloc.h>
#include <stdio.h>

void add_point(intrusive_list_t *list, int x, int y) {
    point_t *pt = malloc(sizeof(point_t));

    pt->x = x;
    pt->y = y;

    add_node(list, &pt->node);
}

void remove_all_points(intrusive_list_t *list) {
    intrusive_node_t *curr = list->head;

    while (curr) {
        point_t *item = container_of(curr, point_t, node);

        intrusive_node_t *next = curr->next;

        remove_node(list, curr);
        free(item);

        curr = next;
    }
}

void print(intrusive_node_t *node, void *data) {
    char *format = (char *)data;

    point_t *item = container_of(node, point_t, node);

    printf(format, item->x, item->y);
}

void count(intrusive_node_t *node, void *data) {
    int *cnt = (int *)data;
    if (node) (*cnt)++;
}

void savetext(intrusive_node_t *node, void *data) {
    FILE *fout = (FILE *)data;

    point_t *item = container_of(node, point_t, node);

    fprintf(fout, "%d %d\n", item->x, item->y);
}

void savebin(intrusive_node_t *node, void *data) {
    FILE *fout = (FILE *)data;

    point_t *item = container_of(node, point_t, node);

    fwrite(&(item->x), 3, 1, fout);
    fwrite(&(item->y), 3, 1, fout);
}