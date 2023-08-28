#include "mergesort.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// int less than comparator
int int_ls_comparator(const void *a, const void *b) {
    return *(int*)a - *(int*)b;  // Сортировка массива по возрастанию.
}

// char less than comparator
int char_ls_comparator(const void *a, const void *b) {
    return *(char*)a - *(char*)b;  // Сортировка массива по возрастанию.
}

// string less than comparator
int string_ls_comparator(const void *a, const void *b) {
    return strcmp(*(char**)a, *(char**)b);  // Сортировка массива по возрастанию.
}

void sort_ints(int *data, int length) {
    mergesort(data,
              length,
              sizeof data[0],
              int_ls_comparator);
    for (int i = 0; i < length; ++i) {
        printf("%d", data[i]);
        if (i + 1 < length) printf(" ");
    }
    printf("\n");
}

void sort_chars(char *data, int length) {
    mergesort(data,
              length,
              sizeof data[0],
              char_ls_comparator);
    for (int i = 0; i < length; ++i) {
        printf("%c", data[i]);
        if (i + 1 < length) printf(" ");
    }
    printf("\n");
}

void sort_strings(char **data, int length) {
    mergesort(data,
              length,
              sizeof data[0],
              string_ls_comparator);
    for (int i = 0; i < length; ++i) {
        printf("%s", data[i]);
        if (i + 1 < length) printf(" ");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Incorrect arguments\n");
        return 0;
    }

    char *type = argv[1];
    int length = argc - 2;

    if (length == 0) {
        printf("\n");
        return 0;
    }

    if (strcmp(type, "int") == 0) {
        int *data = malloc(length * sizeof(int));
        for (int i = 0; i < length; ++i) {
            data[i] = atoi(argv[2 + i]);
        }
        sort_ints(data, length);
        free(data);
    } else if (strcmp(type, "char") == 0) {
        char *data = malloc(length * sizeof(char));
        for (int i = 0; i < length; ++i) {
            data[i] = argv[2 + i][0];
        }
        sort_chars(data, length);
        free(data);
    } else if (strcmp(type, "str") == 0) {
        char **data = malloc(length * sizeof(char*));
        for (int i = 0; i < length; ++i) {
            data[i] = argv[2 + i];
        }
        sort_strings(data, length);
        free(data);
    } else {
        printf("Unknown type\n");
    }

    return 0;
}