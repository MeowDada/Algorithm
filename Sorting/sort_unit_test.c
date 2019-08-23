#include <stdio.h>
#include "sort_unit_test.h"

#define YELLOW "\033[0;33m]"
#define RED    "\033[0;31m]"
#define GREEN  "\033[0;32m]"
#define RESET  "\033[0m]"

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
    printf("[input]:");
    for (int i = 0; i < len; i++) {
        if(flag[i]) {
            printf("%s", RED);
            printf(" %d", test[i]);
            printf("%s", RESET);
        }
        else {
            printf("%s", GREEN);
            printf(" %d", test[i]);
            printf("%s", RESET);
        }
    }
    printf("\n[truth]:");
    for (int i = 0; i < len; i++) {
        if(flag[i]) {
            printf("%s", YELLOW);
            printf(" %d", truth[i]);
            printf("%s", RESET);
        }
        else {
            printf("%s", GREEN);
            printf(" %d", truth[i]);
            printf("%s", RESET);
        }
    }
    printf("\n");

    free(flag);

    return -1;
}