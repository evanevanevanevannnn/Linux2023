GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so README
TRASH = *.o *~ o.* *.tmp
CFLAGS = -Wall -fPIC

TEST_PARAM_ARGS = param
TEST_PARAMS_ARGS = even more params

all: prog prog-a prog-so README

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc -L. prog.o -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. prog.o -loutput -o $@

fun.o: outlib.h

liboutput_static.a:	const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	cc  -shared -o $@ $^

README: prog
	./$< 2> $@

test: test_no_params test_param test_params

test_no_params: prog prog-a prog-so
	./prog    > 0.prog.tmp 2>&1
	./prog-a  > 1.prog.tmp 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > 2.prog.tmp 2>&1
	cmp 0.prog.tmp 1.prog.tmp
	cmp 1.prog.tmp 2.prog.tmp
	@ echo TEST 1 IS OK

test_param: prog prog-a prog-so
	./prog    $(TEST_PARAM_ARGS) > 0.prog.tmp 2>&1
	./prog-a  $(TEST_PARAM_ARGS) > 1.prog.tmp 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so $(TEST_PARAM_ARGS) > 2.prog.tmp 2>&1
	cmp 0.prog.tmp 1.prog.tmp
	cmp 1.prog.tmp 2.prog.tmp
	@ echo TEST 2 IS OK

test_params: prog prog-a prog-so
	./prog   $(TEST_PARAMS_ARGS) > 0.prog.tmp 2>&1
	./prog-a $(TEST_PARAMS_ARGS) > 1.prog.tmp 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so $(TEST_PARAMS_ARGS) > 2.prog.tmp 2>&1
	cmp 0.prog.tmp 1.prog.tmp
	cmp 1.prog.tmp 2.prog.tmp
	@ echo TEST 3 IS OK

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)