
CC = gcc
.SUFFIXES = .c .o
DIR = `basename $(PWD)`

all: powielany.o main.o
	./main.o

main.o: main.c lib.h lib.c
	$(CC) main.c lib.c -o main.o
powielany.o: powielany.c lib.h lib.c
	$(CC) powielany.c lib.c -o powielacz.o
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
