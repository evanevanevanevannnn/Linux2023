GENERATES = range logs
CFLAGS+= -O0 -g

prog: range

test: prog
	mkdir logs

	gdb -q -x test1.gdb --args ./range | grep @@@ > logs/test1.log
	cmp logs/test1.log reference/test1.log
	
	gdb -q -x test2.gdb --args ./range | grep @@@ > logs/test2.log
	cmp logs/test2.log reference/test2.log

	@echo TESTS OK

clean:
	rm -rf $(GENERATES)