SUBDIRS = src tests
GENERATES = Makefile *.in *.log config.* compile depcomp install-sh ltmain.sh missing test-driver configure libtool stamp-h1 *m4*

clean:
	git clean -df

gcov:	check
	$(MAKE) $(MAKEFLAGS) -C src gcov