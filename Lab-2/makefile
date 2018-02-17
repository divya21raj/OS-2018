CC = gcc
CFLAGS = -I. -Wall
LFLAGS = -lm
PROG = hello

all: hellomain.o helloprint.o
	$(CC) hellomain.o helloprint.o -o $(PROG) $(CFLAGS)

hellomain.o: hellomain.c
	$(CC) $(CFLAGS) -c hellomain.c

helloprint.o: helloprint.c
	$(CC) $(CFLAGS) -c helloprint.c

clean:
	rm *.o 

