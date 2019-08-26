#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "progress_bar.h"

int main(int argc, char **argv)
{
    /* create a progress bar */
    progress_bar_t *bar = progress_bar_create();

    /* create a progess */
    progress_t *progess = progress_create(NULL);

    /* load the progress */
    progress_bar_load_progress(bar, progess);

    /* main loop */
    int current = 0;
    int target  = 100;

    for(int i = 0; i < target; i++) {
        current = i;
        progress_update(progess, &current, &target);
        progress_bar_show_progress(bar);
        usleep(5000);
    }

    /* cleanup progress bar */
    progress_bar_destroy(bar);

    return 0;
}