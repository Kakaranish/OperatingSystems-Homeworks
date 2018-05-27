#WYKONAŁ STANISŁAW GRUZ

.SUFFIXES: .c .o .h
CC = gcc
DIR = `basename $(PWD)`

all: obsluga.o wyslij.o grupa.o 
	
obsluga.o: obsluga.c
	$(CC) obsluga.c -o obsluga.o
wyslij.o: wyslij.c
	$(CC) wyslij.c -o wyslij.o
grupa.o: grupa.c
	$(CC) grupa.c -o grupa.o
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
