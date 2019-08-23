#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

const static void (*_sort_method_table[])(void *, size_t, size_t, int(*)(const void *, const void *)) = {
    bubble_sort,
    selection_sort,
    merge_sort,
    in_place_merge_sort,
};
static void (*_sort_method)(void *, size_t, size_t, int(*)(const void *, const void *)) = NULL;

void sort_method(int method)
{
    _sort_method = _sort_method_table[method];
}

void sort(void *base, size_t num, size_t size, int (*cmp)(const void *,const void *))
{
    (*_sort_method)(base, num, size, cmp);
}