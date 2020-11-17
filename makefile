main: main.o
	gcc -o main main.o

arpsting.o: main.c
	gcc -c main.c

run:
	./main
