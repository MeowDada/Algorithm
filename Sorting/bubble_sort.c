#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

#define at(i)  (void *)((char *)base + (i)*size);
#define next(ptr) (ptr = (char *)ptr + size;)

static inline void swap(void *ptr1, void *ptr2, size_t size)
{
    char buf[size];
    memcpy(buf, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, buf, size);
}

void bubble_sort(void *base, size_t num, size_t size, int(*cmp)(const void *, const void *))
{
    void *element1 = NULL;
    void *element2 = NULL;

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            element1 = at(i);
            element2 = at(j);
            if ((*cmp)(element1, element2))
                swap(element1, element2, size);
        }
    }
}