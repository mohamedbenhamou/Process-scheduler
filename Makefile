all: Ordonnanceur
Ordonnanceur: main.o processus.o
	gcc main.o processus.o -o Ordonnanceur

main.o: main.c
	gcc -c main.c
	
processus.o: processus.c processus.h
	gcc -c processus.c

clean:
	rm *.o Ordonnanceur