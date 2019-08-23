#include <stdio.h>
#include "sort.h"
#include "sort_unit_test.h"

/* descending oreder */
int cmp_int(const void *ptr1, const void *ptr2)
{
    if (*(int *)ptr1 < *(int *)ptr2) return -1;
    if (*(int *)ptr1 == *(int *)ptr2) return 0;
    if (*(int *)ptr1 > *(int *)ptr2) return 1;
    return 0;
}

int main(int argc, char **argv)
{
    int arr[] = {5,2,1,7,8,12,3,5,7,4,2,3,0,-4,2,1};
    int tru[] = {-4,0,1,1,2,2,2,3,3,4,5,5,7,7,8,11};

    sort_method(SORT_METHOD_MERGE_SORT);
    sort(arr, 16, sizeof(int), cmp_int);

    for(int i = 0; i < 16; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    sort_test_int_arr(arr, tru, 16);

    return 0;
}