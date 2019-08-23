#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
    if (num == 0 || num == 1)
        return;

    int flag = true;
    void *element1 = NULL;
    void *element2 = NULL;

    for (size_t i = 0; i < num - 1 && flag ; i++) {
        flag = false;
        for (size_t j = 0; j < num - i - 1; j++) {
            element1 = at(j);
            element2 = at(j+1);
            if ((*cmp)(element1, element2)==SORT_FORMER_ELEMENT_IS_LARGER) {
                swap(element1, element2, size);
                flag = true;
            }
        }
    }
}