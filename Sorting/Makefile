.PHONY: all clean

CC                    := gcc
CFLAGS                := -Wall -g -std=gnu99

LIBSORT_PATH          := ../lib
LIBSORT_NAME          := libsort
LIBSORT_SRCS          := sort.c bubble_sort.c selection_sort.c
LIBSORT_OBJS          := $(addsuffix .so,$(LIBSORT_NAME))

PLAYGROUND_PROG       := playground
PLAYGROUND_SRCS       := playground.c
PLAYGROUND_OBJS       := $(patsubst %.c,%.o,$(PLAYGROUND_SRCS))
PLAYGROUND_LIBS       := sort


all:build_libsort build_playground

build_libsort:$(LIBSORT_SRCS)
	$(CC) -shared -o $(LIBSORT_PATH)/$(LIBSORT_OBJS) -fPIC $^

build_playground:
	$(CC) $(CFLAGS) -c $(PLAYGROUND_SRCS)
	$(CC) $(CFLAGS) -o $(PLAYGROUND_PROG) $(PLAYGROUND_OBJS) -L $(LIBSORT_PATH) $(addprefix -l,$(PLAYGROUND_LIBS))

clean:
