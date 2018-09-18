run: main.o node.o user.o
	gcc main.o node.o user.o -o run
main.o: main.c
	gcc -c main.c
node.o: node.c node.h
	gcc -c node.c
user.o: user.c user.h
	gcc -c user.c
clean:
	rm *.o run
