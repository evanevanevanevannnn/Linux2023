all : lab

lab : lab1 lab2 lab3 lab4

lab1 : lab0.c
	gcc -o lab0 lab0.c

lab2 : lab0.c lab1.patch
	patch -o lab1.c < lab1.patch
	gcc -o lab1 lab1.c

lab3 : lab0.c lab2.patch
	patch -o lab2.c < lab2.patch
	gcc -o lab2 lab2.c

lab4 : lab0.c lab3.patch
	patch -o lab3.c < lab3.patch
	gcc -o lab3 lab3.c

run : lab
	./lab0
	./lab1 7
	./lab2 '_#' 4
	./lab3 100 '_#' 4

clean:
	rm lab0 lab1 lab2 lab3 lab1.c lab2.c lab3.c