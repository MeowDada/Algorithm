.PHONY: all clean

CC                    := gcc
CFLAGS                := -Wall -g -std=gnu99

LIBSORT_PATH          := ../lib
LIBSORT_NAME          := libsort
LIBSORT_SRCS          := sort.c bubble_sort.c selection_sort.c merge_sort.c in_place_merge_sort.c insertion_sort.c \
                         shell_sort.c
LIBSORT_OBJS          := $(addsuffix .so,$(LIBSORT_NAME))

PLAYGROUND_PROG       := playground
PLAYGROUND_SRCS       := playground.c sort_unit_test.c
PLAYGROUND_OBJS       := $(patsubst %.c,%.o,$(PLAYGROUND_SRCS))
PLAYGROUND_LIBS       := sort

SORT_UNIT_TEST_PROG   := sort_unit_test_main
SORT_UNIT_TEST_SRCS   := sort_unit_test_main.c sort_unit_test.c
SORT_UNIT_TEST_OBJS   := $(patsubst %.c,%.o,$(SORT_UNIT_TEST_SRCS))
SORT_UNIT_TEST_LIBS   := sort

all:build_libsort build_playground build_sort_unit_test

build_libsort:$(LIBSORT_SRCS)
	$(CC) -shared -o $(LIBSORT_PATH)/$(LIBSORT_OBJS) -fPIC $^

build_playground:
	$(CC) $(CFLAGS) -c $(PLAYGROUND_SRCS)
	$(CC) $(CFLAGS) -o $(PLAYGROUND_PROG) $(PLAYGROUND_OBJS) -L $(LIBSORT_PATH) $(addprefix -l,$(PLAYGROUND_LIBS))

build_sort_unit_test:
	$(CC) $(CFLAGS) -c $(SORT_UNIT_TEST_SRCS)
	$(CC) $(CFLAGS) -o $(SORT_UNIT_TEST_PROG) $(SORT_UNIT_TEST_OBJS) -L $(LIBSORT_PATH) $(addprefix -l,$(SORT_UNIT_TEST_LIBS))

clean:
	rm -rf $(SORT_UNIT_TEST_PROG) $(PLAYGROUND_PROG)
	rm -rf *.o
