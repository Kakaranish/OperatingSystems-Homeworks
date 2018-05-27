
CC = gcc
.SUFFIXES = .c .o
DIR = `basename $(PWD)`

all: main.o klient.o serwer.o
	./main.o

serwer.o: serwer.c msg_lib.c msg_lib.h
	$(CC) serwer.c msg_lib.c -o serwer.o

main.o: main.c msg_lib.c msg_lib.h
	$(CC) main.c msg_lib.c -o main.o

klient.o: klient.c msg_lib.c msg_lib.h
	$(CC) klient.c msg_lib.c -o klient.o

clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
