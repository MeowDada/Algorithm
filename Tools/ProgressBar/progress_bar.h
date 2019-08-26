#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H
#include "progress.h"

typedef struct progress_bar_config_t {
    int   bar_length;
    int   show_percentage;
    int   show_progess;
    int   show_time_predict;
    int   show_time_elapsed;
    char *processed_color;
    char  processed_char;
    char *unprocessed_color;
    char  unprocessed_char;
    char  bar_start_char;
    char  bar_end_char;
    char *bar_format;
    char *bar_title;
} progress_bar_config_t;

typedef struct progress_bar_t {
    progress_t *progress;
    progress_bar_config_t *config;
    char *buffer;
} progress_bar_t;

progress_bar_t *progress_bar_create(void);
void            progress_bar_setup(progress_bar_t *, progress_bar_config_t *);
void            progress_bar_load_progress(progress_bar_t *, progress_t *);
void            progress_bar_destroy(progress_bar_t *);
void            progress_bar_show_progress(progress_bar_t *);

#endif /* PROGRESS_BAR_H */