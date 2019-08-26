#include <stdio.h>
#include <stdlib.h>
#include "progress.h"

static float eval_int(void *input, void *goal)
{
    if (!input || !goal)
        return;
    
    int   current  = *(int *)input;
    int   total    = *(int *)goal;
    float progress = (float)current / (float)total;

    return progress;
}

progress_t *progress_create(float (*eval)(void *, void *))
{
    progress_t *progress = calloc(1, sizeof(progress_t));
    if (!progress) {
        fprintf(stderr, "[progress_create]: failed to create progress instance\n");
        return NULL;
    }

    if (!eval)
        progress->eval = eval_int;

    return progress;
}

void progress_destroy(progress_t *progress)
{
    if (!progress)
        return;
    
    progress->eval = NULL;
    free(progress);
}

void progress_update(progress_t *progress, void *input, void *goal)
{
    if (!progress || !input || !goal)
        return;
    
    progress->input = input;
    progress->total = goal;
}

void  progress_show(progress_t *progress)
{
    return;
}