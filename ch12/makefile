GCC = g++
MINGW_GCC = i686-w64-mingw32-g++
CLANG = clang++
MINGW_CLANG = i686-w64-mingw32-clang++
CFLAGS = -Wall -Wextra -static
SRCS = main.cpp bst.cpp
TAG = ctags

all:
	$(MINGW_GCC) $(CFLAGS) $(SRCS)

tag:
	$(TAG) .

clean:
	rm -f *.exe *.o *.out
