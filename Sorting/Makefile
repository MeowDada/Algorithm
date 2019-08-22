.PHONY: all clean

CC                    := gcc
CFLAGS                := -Wall -g -std=gnu99

LIBSORT_PATH          := ../lib
LIBSORT_NAME          := libsort
LIBSORT_SRCS          := sort.c bubble_sort.c
LIBSORT_OBJS          := $(addsuffix .so,$(SHARED_LIBRARIES_NAME))

PLAYGROUND_PROG       := playground
PLAYGROUND_SRCS       := playground.c
PLAYGROUND_OBJS       := $(patsubst %.c,%.o,$(PLAYGROUND_SRCS))
PLAYGROUND_LIBS       := libsort


all:$(LIBSORT_OBJS) $(PLAYGROUND_PROG)

$(LIBSORT_OBJS):$(LIBSORT_SRCS)
	$(CC) -shared -o $(LIBSORT_PATH)/$@ -fPIC $^ 

$(PLAYGROUND_PROG):$(PLAYGROUND_LIBS) $(PLAYGROUND_OBJS)

$(PLAYGROUND_LIBS):$(LIBSORT_OBJS)

$(PLAYGROUND_OBJS):$(PLAYGROUND_SRCS)
	$(CC) $(CFLAGS) -c $^

clean:
