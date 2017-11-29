CC = g++
CROSS = i686-w64-mingw32-g++
CFLAGS = -Wall -Wextra -static
SRCS = main.c share.c quicksort.c
TAG = ctags

all:
	$(CROSS) $(CFLAGS) $(SRCS)

tag:
	$(TAG) .
