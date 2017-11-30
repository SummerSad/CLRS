GCC = g++
MINGW_GCC = i686-w64-mingw32-g++
CLANG = clang++
CFLAGS = -Wall -Wextra -static
SRCS = main.cpp redblack.cpp
TAG = ctags

all:
	$(MINGW_GCC) $(CFLAGS) $(SRCS)

tag:
	$(TAG) .
clean:
	rm -f *.exe *.out *.o
