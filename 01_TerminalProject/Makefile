all: show

vector: Vector.h Vector.c
	cc Vector.c -c -o Vector.o

filereader: FileReader.h FileReader.c
	cc FileReader.c -c -o FileReader.o

fileshower: FileShower.h FileShower.c
	cc FileShower.c -c -o FileShower.o

show: Vector.o FileReader.o FileShower.o Show.c
	cc Show.c Vector.o FileReader.o FileShower.o -o Show -lncursesw

clean:
	rm -f *.o Show test
