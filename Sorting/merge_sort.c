#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sort.h"

#define at(i)  (void *)((char *)base + (i)*size)
#define next(ptr) (void *)((char *)ptr + size;)

static inline void *offset(void *ptr, size_t offset, size_t size)
{
    char *tmp = (char *)ptr;
    tmp += offset*size;
    return (void *)tmp;
}

static inline void swap(void *ptr1, void *ptr2, size_t size)
{
    char buf[size];
    memcpy(buf, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, buf, size);
}

static inline void assign(void *dest, void *src, size_t size)
{
    memcpy(dest, src, size);
}

static void _merge(void *base, size_t start, size_t mid, size_t end, size_t size,
    int (*cmp)(const void *, const void *))
{
    size_t len_l = mid-start+1;
    size_t len_r = end-mid;

    void *left_arr  = calloc(len_l, size);
    void *right_arr = calloc(len_r, size);
    memcpy(left_arr, offset(base, start, size), len_l*size);
    memcpy(right_arr, offset(base, mid+1, size), len_r*size);

    for (int i = start ; i <= end ; i++) {
        if (i == start) {
            printf("[%d", *(int *)offset(base, i, size));
        }
        else if (i <= mid) {
            printf(" %d", *(int *)offset(base, i, size));
        }
        else if (i == mid+1) {
            printf("][%d", *(int *)offset(base, i, size));
            if (i == end) {
                printf("]\n");
            }
        }
        else if (i < end) {
            printf(" %d", *(int *)offset(base, i, size));
        }
        else if (i == end) {
            printf(" %d]\n", *(int *)offset(base, i, size));
        }
    }

    size_t l = 0;
    size_t r = 0;
    size_t idx = 0;

    for (size_t i = start ; i <= end; i++) {
        void *elem_l = offset(left_arr, l, size);
        void *elem_r = offset(right_arr, r, size);
        int cmpval = (*cmp)(elem_l, elem_r);
        if (cmpval == SORT_FORMER_ELEMENT_IS_SMALLER) {
            memcpy(offset(base, i, size), elem_l, size);
            l++;
        }
        else {
            memcpy(offset(base, i, size), elem_r, size);
            r++;
        }
        idx++;
        if (l == len_l || r == len_r)
            break;
    }

    if (l != len_l) {
        memcpy(offset(base, idx, size), offset(left_arr, l, size), (len_l-l)*size);
    }
    else if (r != len_r) {
        memcpy(offset(base, idx, size), offset(right_arr, r, size), (len_r-r)*size);
    }

    printf("[MERGE:] =");
    for (int i = start ; i <= end ; i++) {
        printf(" %d", *(int *)offset(base, i, size));
    }
    printf("\n");

    free(left_arr);
    free(right_arr);
}

static void _merge_sort(void *base, size_t start, size_t end, size_t size,
    int (*cmp)(const void *, const void *))
{
    if ( start < end ) {
        size_t mid = start + (end-start) / 2;
        _merge_sort(base, start, mid, size, cmp);
        _merge_sort(base, mid+1, end, size, cmp);
        _merge(base, start, mid, end, size, cmp);
    }
}

void merge_sort(void *base, size_t num, size_t size, int (*cmp)(const void *, const void *))
{
    _merge_sort(base, 0, num-1, size, cmp);
}

void in_place_merge_sort(void *base, size_t num, size_t size, int (*cmp)(const void *, const void *))
{

}