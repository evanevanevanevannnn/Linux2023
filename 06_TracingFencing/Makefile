GENERATES = move libunlink.so *.txt *.log

compile: move unlink.so

unlink.so: new_unlink.c
	cc -shared new_unlink.c -o libunlink.so -ldl

test: compile read_test write_test openat_test_1 openat_test_2 test_protected

read_test: 
	@echo "\t=================== READ TEST ===================\n"
	@echo "random text for my test" > file.txt
	@LD_PRELOAD=./libunlink.so strace -e trace=read -e fault=read:when=4:error=EIO ./move file.txt res0.txt
	@if [ $$? -ne 0 ]; then echo "Not catching error in read fault processing"; fi
	@if [ -f  file.txt ] ; then echo "read_test : OK" ; else echo "read_test : FAILED"; fi
	@rm file.txt
	@echo "\n"

write_test:
	@echo "\t=================== WRITE TEST ===================\n"
	@echo "random text for my test" > file.txt
	@LD_PRELOAD=./libunlink.so strace -e trace=write -e fault=write:when=1:error=EINTR ./move file.txt res0.txt
	@if [ $$? -ne 0 ]; then echo "Not catching error in write fault processing"; fi
	@if [ -f  file.txt ] ; then echo "write_test : OK" ; else echo "write_test : FAILED"; fi
	@rm file.txt
	@echo "\n"

openat_test_1:
	@echo "\t=================== OPENAT TEST 1 ===================\n"
	@echo "random text for my test" > file.txt
	@LD_PRELOAD=./libunlink.so strace -e trace=openat -e fault=openat:when=22:error=ENOENT ./move file.txt res0.txt
	@if [ $$? -ne 0 ]; then echo "Not catching error in openat fault processing"; fi
	@if [ -f  file.txt ] ; then echo "openat_test_1 : OK" ; else echo "openat_test_1 : FAILED"; fi
	@rm file.txt
	@echo "\n"

openat_test_2:
	@echo "\t=================== OPENAT TEST 2 ===================\n"
	@echo "random text for my test" > file.txt
	@LD_PRELOAD=./libunlink.so strace -e trace=openat -e fault=openat:when=23:error=ENOENT ./move file.txt res0.txt
	@if [ $$? -ne 0 ]; then echo "Not catching error in openat fault processing"; fi
	@if [ -f  file.txt ] ; then echo "openat_test_2 : OK" ; else echo "openat_test_2 : FAILED"; fi
	@rm file.txt
	@echo "\n"

test_protected: move libunlink.so
	@echo "\t=================== PROTECTED TEST ===================\n"
	@echo "random text for my test" > filePROTECT.txt
	@LD_PRELOAD=./libunlink.so ./move filePROTECT.txt output.txt
	@if [ -f  filePROTECT.txt ] ; then echo "test_protected : OK" ; else echo "test_protected : FAILED"; fi
	@rm filePROTECT.txt
	@echo "\n"

clean:
	rm -rf $(GENERATES)