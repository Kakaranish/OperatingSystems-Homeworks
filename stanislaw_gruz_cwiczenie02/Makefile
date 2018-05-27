#WYKONAŁ STANISŁAW GRUZ

.SUFFIXES: .c .o .h
CC = gcc
DIR = `basename $(PWD)`

all: main.o file.o
	./main.o
	make clean
	

main.o: main.c procesy.h
	$(CC) main.c -o main.o

file.o: executable_file.c
	$(CC) executable_file.c -o file.o

clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
