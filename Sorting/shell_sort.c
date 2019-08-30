#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sort.h"

static inline void *offset(void *ptr, size_t off, size_t size)
{
    char *tmp = (char *)ptr;
    tmp += off*size;
    return (void *)tmp;
}

static inline void swap(void *ptr1, void *ptr2, size_t size)
{
    char buf[size];
    memcpy(buf, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, buf, size);
}

static inline void *copy(void *ptr, size_t size)
{
    void *tmp = calloc(1, size);
    memcpy(tmp, ptr, size);
    return tmp;
}

void shell_sort(void *base, size_t num, size_t size, int(*cmp)(const void *, const void *))
{
    for (size_t gap = num/2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < num; i++) {
            void *temp = copy(offset(base, i, size), size);
            size_t j = i;
            while (j >= gap && (*cmp)(offset(base, j-gap, size), temp)==SORT_FORMER_ELEMENT_IS_LARGER) {
                memcpy(offset(base, j, size), offset(base, j-gap, size), size);
                j -= gap;
            }
            memcpy(offset(base, j, size), temp, size);
            free(temp);
        }
    }
}