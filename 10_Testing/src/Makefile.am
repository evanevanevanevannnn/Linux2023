CFLAGS = -std=c99 -Wall -Wextra -pedantic
if COND_GCOV
CFLAGS += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS += -O3 -g3
endif

lib_LTLIBRARIES = libbuf.la

libbuf.c: buf.h

gcov:
	gcov -o .libs libbuf 