
CC = gcc
.SUFFIXES = .c .o
DIR = `basename $(PWD)`

all: main.o
	./main.o

main.o: main.c
	$(CC) main.c -pthread -o main.o
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
