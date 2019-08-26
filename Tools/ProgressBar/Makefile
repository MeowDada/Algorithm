.PHONY: all clean

CC                       := gcc
CFLAGS                   := -Wall -g -std=gnu99

PROGRESS_BAR_TEST_PROG   := progress_bar_test
PROGRESS_BAR_TEST_SRCS   := progress_bar_test.c progress.c progress_bar.c
PROGRESS_BAR_TEST_OBJS   := $(patsubst %.c,%.o,$(PROGRESS_BAR_TEST_SRCS))

all:
	$(CC) $(CFLAGS) -c $(PROGRESS_BAR_TEST_SRCS)
	$(CC) $(CFLAGS) -o $(PROGRESS_BAR_TEST_PROG) $(PROGRESS_BAR_TEST_OBJS)

clean:
	rm -rf $(PROGRESS_BAR_TEST_PROG)
	rm -rf *.o