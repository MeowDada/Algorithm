#ifndef SORT_H
#define SORT_H
#include <unistd.h>

enum {
    SORT_METHOD_BUBBLE_SORT,
    SORT_METHOD_SELECTION_SORT
};

void sort_method(int method);
void sort(void *base, size_t num, size_t size, int (*cmp)(const void *,const void *));

extern void bubble_sort(void *, size_t, size_t, int(*)(const void *, const void *));
extern void selection_sort(void *, size_t, size_t, int(*)(const void *, const void *));

#endif /* SORT_H */