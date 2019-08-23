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
    size_t num = end - start + 1;
    if (num == 0 || num == 1)
        return;

    if (num == 2) {
        if ((*cmp)(offset(base, start, size), offset(base, end, size))==SORT_FORMER_ELEMENT_IS_SMALLER)
        {
            swap(offset(base, start, size), offset(base, end, size), size);
            return;
        }
        return;
    }
    
    void *temp = calloc(num, size);
    void *tptr = temp;
    size_t idx = 0;

    size_t l = start;
    size_t r = mid + 1;

    void *lptr = offset(base, l, size);
    void *rptr = offset(base, r, size);

    while (l <= mid+1 && r <= end) {
        lptr = offset(base, l, size);
        rptr = offset(base, r, size);
        int cmp_val = (*cmp)(lptr, rptr);
        if (cmp_val == SORT_FORMER_ELEMENT_IS_SMALLER ||
            cmp_val == SORT_FORMER_ELEMENT_IS_EQUAL) {
            memcpy(tptr, lptr, size);
            idx++;
            l++;
            tptr = offset(temp, idx, size);
        }
        else {
            memcpy(tptr, rptr, size);
            idx++;
            r++;
            tptr = offset(temp, idx, size);
        }
    }

    if (l != mid+1) {
        size_t num_to_copy = (mid+1) - l;
        memcpy(offset(base, start+idx, size), tptr, num_to_copy*size);
    }
    else if (r != end) {
        size_t num_to_copy = end - r + 1;
        memcpy(offset(base, start+idx, size), tptr, num_to_copy*size);
    }

    memcpy(offset(base, start, size), temp, num*size);
    free(temp);
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