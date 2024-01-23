cmon:main.o src/tree.o src/data.o src/array.o headers/*
	gcc main.o src/tree.o src/data.o src/array.o -o cmon

main.o:main.c headers/tree.h 
	gcc -c main.c -o main.o

src/tree.o:src/tree.c headers/tree.h headers/data.h
	gcc -c src/tree.c -o src/tree.o

src/data.o:src/data.c headers/*
	gcc -c src/data.c -o src/data.o

src/array.o:src/array.c headers/*
	gcc -c src/array.c -o src/array.o

clean:
	rm cmon main.o src/tree.o
