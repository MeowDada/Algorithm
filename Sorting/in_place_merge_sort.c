#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sort.h"

static inline void *offset(void *ptr, size_t offset, size_t size)
{
    char *tmp = (char *)ptr;
    tmp += offset*size;
    return (void *)tmp;
}

static inline void *copy(void *src, size_t size)
{
    void *tmp = calloc(1, size);
    memcpy(tmp, src, size);
    return tmp;
}

static void merge(void *base, size_t start, size_t mid, size_t end, size_t size,
    int (*cmp)(const void *, const void *))
{
    size_t l = 0;
    size_t r = 0;

    for (int i = start; i <= end; i++) {
        void *elem_l = offset(base, start+l, size);
        void *elem_r = offset(base, mid+1+r, size);
        int cmpval = (*cmp)(elem_l, elem_r);

        if (cmpval == SORT_FORMER_ELEMENT_IS_SMALLER || 
            cmpval == SORT_FORMER_ELEMENT_IS_EQUAL) {
            l++;
        }
        else {
            void *elem_to_put = copy(elem_r, size);
            void *original_pos = offset(base, i, size);
            void *shifted_pos = offset(base, i+1, size);
            size_t bytes_to_shift = (r-l)*size;
            memcpy(shifted_pos, original_pos, bytes_to_shift);
            memcpy(original_pos, elem_to_put, size);
            free(elem_to_put);
            l++;
            r++;
        }
        if (l == r || r > end)
            break;
    }
}

static void merge_sort(void *base, size_t start, size_t end,
    size_t size, int (*cmp)(const void *, const void *))
{
    if (start < end) {
        size_t mid = start + (end-start)/2;
        merge_sort(base, start, mid, size, cmp);
        merge_sort(base, mid+1, end, size, cmp);
        merge(base, start, mid, end, size, cmp);
    }
}

void in_place_merge_sort(void *base, size_t num, size_t size, int (*cmp)(const void *, const void *))
{
    merge_sort(base, 0, num-1, size, cmp);
}