#ifndef SORT_H
#define SORT_H

#include <unistd.h>

enum {
    SORT_FORMER_ELEMENT_IS_SMALLER = -1,
    SORT_FORMER_ELEMENT_IS_EQUAL   = 0,
    SORT_FORMER_ELEMENT_IS_LARGER  = 1,
};

enum {
    SORT_METHOD_BUBBLE_SORT,
    SORT_METHOD_SELECTION_SORT,
    SORT_METHOD_INSERTION_SORT,
    SORT_METHOD_MERGE_SORT,
    SORT_METHOD_IN_PLACE_MERGE_SORT,
};

void sort_method(int method);
void sort(void *base, size_t num, size_t size, int (*cmp)(const void *,const void *));

extern void bubble_sort(void *, size_t, size_t, int(*)(const void *, const void *));
extern void selection_sort(void *, size_t, size_t, int(*)(const void *, const void *));
extern void insertion_sort(void *, size_t, size_t, int(*)(const void *, const void *));
extern void merge_sort(void *, size_t, size_t, int(*)(const void *, const void *));
extern void in_place_merge_sort(void *, size_t, size_t, int(*)(const void *, const void *));

#endif /* SORT_H */