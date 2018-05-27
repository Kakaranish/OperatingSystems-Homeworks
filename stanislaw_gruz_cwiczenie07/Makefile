
CC = gcc
.SUFFIXES = .c .o
DIR = `basename $(PWD)`

all: main.o
	./main.o

main.o: main.c sem_lib.c shm_lib.c sem_lib.h shm_lib.h
	$(CC) main.c sem_lib.c shm_lib.c -o main.o

clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
