cmon:main.o src/tree.o headers/*
	gcc main.o src/tree.o src/data.o -o cmon

main.o:main.c headers/tree.h 
	gcc -c main.c -o main.o

src/tree.o:src/tree.c headers/tree.h headers/data.h
	gcc -c src/tree.c -o src/tree.o

src/data.o:src/data.c headers/data.h headers/types.h
	gcc -c src/data.c -o src/data.o

clean:
	rm cmon main.o src/tree.o
