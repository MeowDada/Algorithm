#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sort.h"

#define at(i)  (void *)((char *)base + (i)*size)
#define next(ptr) (ptr = (char *)ptr + size;)

static inline void swap(void *ptr1, void *ptr2, size_t size)
{
    char buf[size];
    memcpy(buf, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, buf, size);
}

void selection_sort(void *base, size_t num, size_t size, int(*cmp)(const void *, const void *))
{
    if (num == 0)
        return;
    
    void *element_small  = NULL;
    void *element_to_cmp = NULL;
    void *element_head   = NULL;

    for (size_t i = 0; i < num - 1; i++) {
        element_small = at(i);
        element_head = at(i);
        for (size_t j = i+1 ; j < num ; j++) {
            element_to_cmp = at(j);
            if (!((*cmp)(element_small, element_to_cmp))) {
                element_small = at(j);
            }
        }
        swap(element_head, element_small, size);
    }
}