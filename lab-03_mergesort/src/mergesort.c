#include "mergesort.h"
#include <stdlib.h>
#include <assert.h>

void copy(char* from, char* to, size_t element_size) {
    for (size_t i = 0; i < element_size; ++i, from++, to++) {
        *to = *from;
    }
}

void mergesort(
        void *array,
        size_t elements, size_t element_size,
        int (*comparator)(const void *, const void *)
) {
    if (elements <= 1) {
        return;
    }

    size_t half = elements / 2;
    size_t elements_lef = half;
    size_t elements_rig = elements - half;

    mergesort(array, elements_lef, element_size, comparator);
    mergesort(array + half * element_size, elements_rig, element_size, comparator);

    char *sorted_part = malloc(elements * element_size);
    assert(sorted_part);

    char *ptr = sorted_part;
    char *ptr_lef = array;
    char *ptr_rig = array + half * element_size;

    size_t sorted_lef = 0;
    size_t sorted_rig = 0;

    while (sorted_lef < elements_lef && sorted_rig < elements_rig) {
        if (comparator(ptr_lef, ptr_rig) < 0) {
            copy(ptr_lef, ptr, element_size);
            ptr_lef += element_size;
            ++sorted_lef;
        } else {
            copy(ptr_rig, ptr, element_size);
            ptr_rig += element_size;
            ++sorted_rig;
        }
        ptr += element_size;
    }

    while (sorted_lef < elements_lef) {
        copy(ptr_lef, ptr, element_size);
        ptr_lef += element_size;
        ++sorted_lef;
        ptr += element_size;
    }

    while (sorted_rig < elements_rig) {
        copy(ptr_rig, ptr, element_size);
        ptr_rig += element_size;
        ++sorted_rig;
        ptr += element_size;
    }

    char *sorted_ptr = sorted_part;

    while (elements--) {
        copy(sorted_ptr, array, element_size);
        sorted_ptr += element_size;
        array += element_size;
    }

    free(sorted_part);
}