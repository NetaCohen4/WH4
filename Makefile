NAME = main
CC = gcc
CFLAGS = -Wall -Werror -g
OBJ = Algo.o Graph.o main.o Graph.h
.PHONY = all clean

all : Graph

Graph: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o Graph 

Graph.o: Graph.c Graph.h
	$(CC) $(CFLAGS) -c Graph.c

Algo.o: Algo.c Graph.h
	$(CC) $(CFLAGS) -c Algo.c

main.o: main.c Graph.h
	$(CC) $(CFLAGS) -c main.c


clean:
	rm -f *.o *.a Graph