#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "progress_bar.h"

static progress_bar_config_t default_config = {
    .bar_length            = 20,
    .show_percentage       = true,
    .show_progess          = true,
    .show_time_predict     = false,
    .show_time_elapsed     = false,
    .processed_color       = NULL,
    .processed_char        = '=',
    .unprocessed_color     = NULL,
    .unprocessed_char      = ' ',
    .bar_start_char        = '[',
    .bar_end_char          = ']',
    .bar_format            = NULL,
    .bar_title             = NULL,
};

static int convert_process_to_bar_length(progress_bar_t *bar, float process)
{
    if (!bar)
        return 0;
    
    int bar_length = bar->config->bar_length;

    if (fabsf(process - 1) <= 10e-6)
        return bar_length;
    
    return (int)((float)bar_length*process);
}

progress_bar_t *progress_bar_create(void)
{
    progress_bar_t *bar = calloc(1, sizeof(progress_bar_t));
    if (!bar) {
        fprintf(stderr, "[progress_bar_create]: failed to allocate memory for progress bar instance\n");
        return NULL;
    }
    bar->config = &default_config;
    
    bar->buffer = calloc(bar->config->bar_length, sizeof(char));
    if (!bar->buffer) {
        bar->config = NULL;
        free(bar);
        fprintf(stderr, "[progress_bar_create]: failed to allocate memory for progress bar buffer\n");
        return NULL;
    }

    return bar;
}

void progress_bar_setup(progress_bar_t *bar, progress_bar_config_t *config)
{
    if (!bar || !config)
        return;
    
    bar->config = config;

    char *new_buffer = calloc(bar->config->bar_length, sizeof(char));
    if (!new_buffer) {
        fprintf(stderr, "[progress_bar_setup]: failed to allocate memory for new progress bar buffer\n");
        return;
    }

    if (bar->buffer)
        free(bar->buffer);
    
    bar->buffer = new_buffer;
}

/* Note: will delete progress loaded in this progess bar, too. */
void progress_bar_destroy(progress_bar_t *bar)
{
    if (!bar)
        return;
    
    if (bar->progress) {
        progress_destroy(bar->progress);
        bar->progress = NULL;
    }

    if (bar->buffer) {
        free(bar->buffer);
        bar->buffer = NULL;
    }

    free(bar);
}

void progress_bar_load_progress(progress_bar_t *bar, progress_t *progress)
{
    if (!bar || !progress)
        return;
    
    bar->progress = progress;
}

void progress_bar_show_progress(progress_bar_t *bar)
{
    if (!bar) {
        fprintf(stderr, "[progress_bar_show_progress]: progress bar is NULL pointer\n");
        return;
    }
    
    progress_t *progress = bar->progress;
    if (!progress) {
        fprintf(stderr, "[progress_bar_show_progress]: progress is NULL pointer\n");
        return;
    }
    
    float process = progress->eval(progress->input, progress->total);
    int process_len = convert_process_to_bar_length(bar, process);
    // int unprocess_len = bar->config->bar_length-process_len;

    /* setup progress bar */
    for(int i = 0; i < bar->config->bar_length; i++) {
        if (i <= process_len) {
            bar->buffer[i] = bar->config->processed_char;
        }
        else {
            bar->buffer[i] = bar->config->unprocessed_char;
        }
    }

    fprintf(stdout, "\b%c[2k\r%c%s%c\n", 27,
                                    bar->config->bar_start_char, 
                                    bar->buffer,
                                    bar->config->bar_end_char);
    fflush(stdout);
}