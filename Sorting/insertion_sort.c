#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sort.h"

static inline void *offset(void *ptr, size_t off, size_t size)
{
    char *tmp = (char *)ptr;
    tmp += size*off;
    return tmp;
}

static inline void swap(void *ptr1, void *ptr2, size_t size)
{
    char buf[size];
    memcpy(buf, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, buf, size);
}

static inline void *copy(void *ptr, size_t size)
{
    void *tmp = calloc(1, size);
    memcpy(tmp, ptr, size);
    return tmp;
}

static inline void shift_index(void *ptr, size_t dest, size_t src, size_t size)
{
    size_t bytes_to_shift = (dest > src)? dest-src : src-dest;
    bytes_to_shift *= size;
    void *ptr_dest = offset(ptr, dest, size);
    void *ptr_src  = offset(ptr, src,  size);
    memmove(ptr_dest, ptr_src, bytes_to_shift);
}

static inline void insert_new_card_to_hands(void *base, size_t card_idx, size_t insert_pos, size_t size)
{
    void *new_card = offset(base, card_idx, size);
    void *new_card_dup = copy(new_card, size);
    void *ptr_insert_pos = offset(base, insert_pos, size);
    shift_index(base, insert_pos+1, insert_pos, size);
    memcpy(ptr_insert_pos, new_card_dup, size);
    free(new_card_dup);
}

void insertion_sort(void *base, size_t num, size_t size, int(*cmp)(const void *, const void *))
{
    if (num == 0 || num == 1)
        return;
    
    /* pick the unsorted new card */
    for (size_t i = 1; i < num; i++) {
        void *new_card = offset(base, i, size);
        void *smallest_card = offset(base, 0, size);
        size_t insert_pos = 0;
        /* check current hands */
        for(size_t j = 0; j < i; j++) {
            void *compared_card = offset(base, j, size);
            int cmpval = (*cmp)(new_card, compared_card);
            if (cmpval == SORT_FORMER_ELEMENT_IS_SMALLER ||
                cmpval == SORT_FORMER_ELEMENT_IS_EQUAL) {
                insert_pos = j;
                insert_new_card_to_hands(base, i, insert_pos, size);
                break;
            }
        }
    }
}