#WYKONANE PRZEZ STANISLAWA GRUZ
.SUFFIXES: .c .o .h

CC = gcc
CFLAGS = -c -Wall
LFLAGS = -lm
DIR = `basename $(PWD)`
run =  ./output.o

all: program.o
	$(CC) program.o $(LFLAGS) -o output.o
	$(run)
	
program.o: main.c procesy.h
	$(CC) $(CFLAGS) main.c $(LFLAGS) -o program.o
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


