#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "sort_unit_test.h"

static int total_test = 0;

/* descending oreder */
int cmp_int(const void *ptr1, const void *ptr2)
{
    if (*(int *)ptr1 < *(int *)ptr2) return -1;
    if (*(int *)ptr1 == *(int *)ptr2) return 0;
    if (*(int *)ptr1 > *(int *)ptr2) return 1;
    return 0;
}

/* case: length = 1 */
static int boundary_case(void)
{
    int passed = 0;

    int arr[] = {1};
    int tru[] = {1};
    total_test++;

    sort(arr, 1, sizeof(int), cmp_int);
    if(sort_test_int_arr(arr, tru, 1)==0)
        passed++;

    return passed;
}

/**
 * case: sorted already
 * case: odd-length input
 * case: even-length input
 * 
 */
static int special_case(void)
{
    int passed = 0;

    /* sorted already case */
    int arr[] = {1,3,5,7,9};
    int tru[] = {1,3,5,7,9};
    total_test++;
    sort(arr, 5, sizeof(int), cmp_int);
    if(sort_test_int_arr(arr, tru, 5)==0)
        passed++;

    /* odd-length input case */
    int arr_odd[] = {19,7,8,8,10,14,11,7,8};
    int tru_odd[] = {7,7,8,8,8,10,11,14,19};
    total_test++;

    sort(arr_odd, 9, sizeof(int), cmp_int);
    if(sort_test_int_arr(arr_odd, tru_odd, 9)==0)
        passed++;
    
    /* even-length input case */
    int arr_even[] = {-5,-3,7,5,-2,-2,-2,-2,0,4,1,8};
    int tru_even[] = {-5,-3,-2,-2,-2,-2,0,1,4,5,7,8};

    sort(arr_even, 12, sizeof(int), cmp_int);
    if(sort_test_int_arr(arr_even, tru_even, 12)==0)
        passed++;
    
    return passed;
}

static int standard_case(void)
{
    int passed = 0;

    return passed;
}

int main(int argc, char **argv)
{
    int passed = 0;

    sort_method(SORT_METHOD_SELECTION_SORT);
    passed += boundary_case();
    passed += special_case();
    passed += standard_case();

    return passed == total_test ? EXIT_SUCCESS : EXIT_FAILURE;
}