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

static inline void assign(void *dest, void *src, size_t size)
{
    memcpy(dest, src, size);
}

/**
 * array: <----------array--------->
 *        <-----l-----><-----r----->
 * indexL .l............r...........
 */
static void _merge(void *base, size_t start, size_t mid, size_t end, size_t size,
    int (*cmp)(const void *, const void *))
{
    size_t l = start;
    size_t m = mid;
    size_t r = m+1;

    void *element1 = at(m);
    void *element2 = at(r);

    /* if already sorted */
    if ((*cmp)(element1, element2))
        return;

    while (l <= m && r <= end) {
        element1 = at(l);
        element2 = at(r);
        if ((*cmp)(element1, element2)) {
            l++;
        }
        else {
            void *val = at(r);
            size_t idx = r;
            while (idx != l) {
                element1 = at(idx);
                element2 = at(idx-1);
                assign(element1, element2, size);
                idx--;
            }
            element1 = at(l);
            assign(element1, val, size);
            l++;
            m++;
            r++;
        }
    }
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