#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"
#include "sort_unit_test.h"

#define RANDOM_CASE_NUM (0)
#define RANDOM_CASE_LEN (1000)
#define RANDOM_NUM_MIN  (0)
#define RANDOM_NUM_MAX  (50)

static int total_test = 0;
int sort_test_print   = 0;

/* descending oreder */
int cmp_int(const void *ptr1, const void *ptr2)
{
    if (*(int *)ptr1 < *(int *)ptr2) return -1;
    if (*(int *)ptr1 == *(int *)ptr2) return 0;
    if (*(int *)ptr1 > *(int *)ptr2) return 1;
    return 0;
}

/* case: length = 1 */
/* case: length = 2 */
static int boundary_case(void)
{
    int passed = 0;

    int arr[] = {1};
    int tru[] = {1};
    total_test++;

    sort(arr, 1, sizeof(int), cmp_int);
    if(sort_test_int_arr(arr, tru, 1)==0)
        passed++;

    int arr_2[] = {1,-1};
    int tru_2[] = {-1,1};
    total_test++;

    sort(arr_2, 2, sizeof(int), cmp_int);
    if(sort_test_int_arr(arr_2, tru_2, 2)==0)
        passed++;

    int arr_3[] = {0,1};
    int tru_3[] = {0,1};
    total_test++;

    sort(arr_3, 2, sizeof(int), cmp_int);
    if (sort_test_int_arr(arr_3, tru_3, 2)==0)
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
    total_test++;

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

static int random_case(int num, int range)
{
    srand(time(NULL));

    int passed = 0;

    total_test += num;
    for (int i = 0; i < num; i++) {
        int len = rand() % (range-1) + 1;
        int *arr = calloc(len, sizeof(int));
        int *tru = calloc(len, sizeof(int));
        for (int j = 0; j < len ; j++) {
            int content = RANDOM_NUM_MIN + rand() % (RANDOM_NUM_MAX-RANDOM_NUM_MIN);
            memcpy(arr+j, &content, sizeof(int));
        }
        memcpy(tru, arr, len*sizeof(int));
        qsort(tru, len, sizeof(int), cmp_int);
        sort(arr, len, sizeof(int), cmp_int);
        if (sort_test_int_arr(arr, tru, len)==0)
            passed++;
        
        free(arr);
        free(tru);
    }

    return passed;
}

int main(int argc, char **argv)
{
    int passed = 0;

    sort_method(SORT_METHOD_SELECTION_SORT);
    passed += boundary_case();
    passed += special_case();
    passed += standard_case();
    passed += random_case(RANDOM_CASE_NUM, RANDOM_CASE_LEN);
    if (passed == total_test) {
        printf("[UNIT TEST]: Selection sort passed\n");
    }
    passed     = 0;
    total_test = 0;

    sort_method(SORT_METHOD_BUBBLE_SORT);
    passed += boundary_case();
    passed += special_case();
    passed += standard_case();
    passed += random_case(RANDOM_CASE_NUM, RANDOM_CASE_LEN);
    if (passed == total_test) {
        printf("[UNIT TEST]: Bubble sort passed\n");
    }
    passed     = 0;
    total_test = 0;

    sort_method(SORT_METHOD_INSERTION_SORT);
    passed += boundary_case();
    passed += special_case();
    passed += standard_case();
    passed += random_case(RANDOM_CASE_NUM, RANDOM_CASE_LEN);
    if (passed == total_test) {
        printf("[UNIT TEST]: Insertion sort passed\n");
    }
    passed     = 0;
    total_test = 0;

    sort_method(SORT_METHOD_MERGE_SORT);
    passed += boundary_case();
    passed += special_case();
    passed += standard_case();
    passed += random_case(RANDOM_CASE_NUM, RANDOM_CASE_LEN);
    if (passed == total_test) {
        printf("[UNIT TEST]: Merge sort passed\n");
    }
    passed     = 0;
    total_test = 0;

    sort_method(SORT_METHOD_IN_PLACE_MERGE_SORT);
    passed += boundary_case();
    passed += special_case();
    passed += standard_case();
    passed += random_case(RANDOM_CASE_NUM, RANDOM_CASE_LEN);
    if (passed == total_test) {
        printf("[UNIT TEST]: In-place merge sort passed\n");
    }
    passed     = 0;
    total_test = 0;

    return 0;
}