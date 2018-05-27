#WYKONAŁ STANISŁAW GRUZ
CC = gcc
DIR = `basename $(PWD)`

run_a: main.o od.o do.o
	mkfifo tmp/fifo
	./main.o tmp/fifo
run_b: main.o od.o do.o
	./main.o 
run_c: od.o do.o
	gnome-terminal -e ./od.o
	./do.o
main.o: main.c
	$(CC) main.c -o main.o
od.o: od.c
	$(CC) od.c -o od.o
do.o: do.c
	$(CC) do.c -o do.o
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf
	rm res/do.txt	
	touch res/do.txt

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
	
cleanfifo:
	rm tmp/fifo
		


