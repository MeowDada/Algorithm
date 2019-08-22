#include <stdio.h>
#include "sort.h"

/* return true if ptr1 is larger than ptr2 */
int cmp_int(const void *ptr1, const void *ptr2)
{
    return *(int *)ptr1 > *(int *)ptr2;
}

int main(int argc, char **argv)
{
    int arr[] = {5,2,1,7,8,12,3,5,7,4,2,3,0,-4,2,1};

    sort_method(SORT_METHOD_BUBBLE_SORT);
    sort(arr, 16, sizeof(int), cmp_int);

    for(int i = 0; i < 16; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}