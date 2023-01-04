CFAGS = -Wall -g

proy2: lista.o proy2.o lista.h
	gcc $(CFLAGS) proy2.o lista.o -o proy2

proy2.o: proy2.c
	gcc $(CFLAGS) proy2.c -o proy2.o -c

lista.o: lista.c
	gcc $(CFLAGS) lista.c -o lista.o -c

clear:
	rm -f *.o
