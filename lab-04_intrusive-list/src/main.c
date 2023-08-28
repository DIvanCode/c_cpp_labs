#include "clist.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct point {
    int x;
    int y;
    intrusive_node_t node;
} point_t;

void add_point(intrusive_list_t *list, int x, int y) {
    point_t *pt = malloc(sizeof(point_t));

    pt->x = x;
    pt->y = y;

    add_node(list, &pt->node);
}

void remove_point(intrusive_list_t *list, int x, int y) {
    if (list->length == 0) {
        return;
    }

    intrusive_node_t *curr = list->head;

    while (curr) {
        point_t *item = container_of(curr, point_t, node);

        if (item->x == x && item->y == y) {
            intrusive_node_t *next = curr->next;

            remove_node(list, curr);
            free(item);

            curr = next;
        } else {
            curr = curr->next;
        }
    }
}

void show_all_points(intrusive_list_t *list) {
    intrusive_node_t *curr = list->head;

    int first_point = 1;

    while (curr) {
        point_t *item = container_of(curr, point_t, node);

        if (!first_point) printf(" ");
        printf("(%d %d)", item->x, item->y);

        curr = curr->next;

        first_point = 0;
    }

    printf("\n");
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

int main() {
    intrusive_list_t l;
    init_list(&l);
    char *type = malloc(sizeof(char) * 100);
    while (1) {
        scanf("%s100", type);
        if (strcmp(type, "add") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            add_point(&l, x, y);
        } else if (strcmp(type, "rm") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            remove_point(&l, x, y);
        } else if (strcmp(type, "print") == 0) {
            show_all_points(&l);
            fflush(stdout);
        } else if (strcmp(type, "rma") == 0) {
            remove_all_points(&l);
        } else if (strcmp(type, "len") == 0) {
            printf("%d\n", (int) l.length);
            fflush(stdout);
        } else if (strcmp(type, "exit") == 0) {
            break;
        } else {
            printf("Unknown command\n");
            fflush(stdout);
        }
    }
    free(type);
    remove_all_points(&l);
    return 0;
}
