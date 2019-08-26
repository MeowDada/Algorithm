#ifndef PROGRESS_H
#define PROGRESS_H

typedef struct progress_t {
    void   *input;
    void   *total;
    float (*eval)(void *, void *);
} progress_t;

progress_t *progress_create(float (*eval)(void *, void *));
void        progress_destroy(progress_t *);
void        progress_update(progress_t *, void *, void *);
void        progress_show(progress_t *);

#endif /* PROGRESS_H */