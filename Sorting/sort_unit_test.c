#include <stdio.h>
#include <stdlib.h>
#include "sort_unit_test.h"

#define YELLOW "\033[1;33m"
#define RED    "\033[1;31m"
#define GREEN  "\033[1;32m"
#define RESET  "\033[0m"

extern int sort_test_print;

#define SORT_UNIT_PRINT_RESULT sort_test_print

int sort_test_int_arr(int *test, int *truth, int len)
{
    int succeed = 1;
    int *flag = calloc(len, sizeof(int));

    for (int i = 0; i < len ; i++) {
        if (test[i] != truth[i]) {
            flag[i] = 1;
            succeed = 0;
        }
    }

    if (!succeed)
        goto fail;
    
    free(flag);

    return 0;
fail:
#if SORT_UNIT_PRINT_RESULT
    printf("[input]:");
    for (int i = 0; i < len; i++) {
        if(flag[i]) {
            printf(" %s%d%s", RED, test[i], RESET);
        }
        else {
            printf(" %s%d%s", GREEN, test[i], RESET);
        }
    }
    printf("\n[truth]:");
    for (int i = 0; i < len; i++) {
        if(flag[i]) {
            printf(" %s%d%s", YELLOW, truth[i], RESET);
        }
        else {
            printf(" %s%d%s", GREEN, truth[i], RESET);
        }
    }
    printf("\n");
#endif
    free(flag);

    return -1;
}