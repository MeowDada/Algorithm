#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sort.h"

#define DEBUG_IN_PLACE_MERGE_SORT 1

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

static void _merge(void *base, size_t _start, size_t _mid, size_t _end, size_t size,
    int (*cmp)(const void *, const void *))
{
#if DEBUG_IN_PLACE_MERGE_SORT
    printf("\033[1;35m[BEFORE]: \033[0m[");
    for(int i = _start ; i <= _mid; i++) {
        printf(" %d", *(int *)offset(base, i, size));
    }
    printf(" ] [");
    for(int i = _mid+1; i <= _end; i++) {
        printf(" %d", *(int *)offset(base, i, size));
    }   
    printf(" ]\n");
#endif
    size_t start = _start;
    size_t mid   = _mid;
    size_t end   = _end;
    size_t l = start;
    size_t r = mid+1;

    int cmpval = (*cmp)(offset(base, mid, size), offset(base, r, size));
    if (cmpval == SORT_FORMER_ELEMENT_IS_SMALLER ||
        cmpval == SORT_FORMER_ELEMENT_IS_EQUAL)
        return;
    
    while (l <= mid && r <= end) {
        void *elem_l = offset(base, l, size);
        void *elem_r = offset(base, r, size);
        cmpval = (*cmp)(elem_l, elem_r);
        if (cmpval == SORT_FORMER_ELEMENT_IS_SMALLER ||
            cmpval == SORT_FORMER_ELEMENT_IS_EQUAL) {
            l++;
        }
        else {
            void *copied = offset(base, r, size);
            size_t idx = r;

            while (idx != l) {
                void *dest = offset(base, idx, size);
                void *src  = offset(base, idx-1, size);
                memcpy(dest, src, size);
                idx--;
            }
            memcpy(elem_l, copied, size);
            free(copied);
            l++;
            mid++;
            r++;
        }
    }
#if DEBUG_IN_PLACE_MERGE_SORT
    printf("\033[1;36m[MERGED]: \033[0m[");
    for(int i = _start ; i <= _end; i++) {
        printf(" %d", *(int *)offset(base, i, size));
    }
    printf(" ]\n");
#endif
}

static void _merge_sort(void *base, size_t start, size_t end,
    size_t size, int (*cmp)(const void *, const void *))
{
    if (start < end) {
        size_t mid = start + (end-start)/2;
        _merge_sort(base, start, mid, size, cmp);
        _merge_sort(base, mid+1, end, size, cmp);
        _merge(base, start, mid, end, size, cmp);
    }
}

void in_place_merge_sort(void *base, size_t num, size_t size, int (*cmp)(const void *, const void *))
{
#if DEBUG_IN_PLACE_MERGE_SORT
    printf("\033[01;33m[TARGET]: [");
    for (int i = 0; i < num ; i++) {
        printf(" %d", *(int *)offset(base, i, size));
    }
    printf(" ]\033[0m\n");
#endif
    _merge_sort(base, 0, num-1, size, cmp);
}