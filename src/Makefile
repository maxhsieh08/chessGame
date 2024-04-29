# Compiler and compiler flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra


all: board.o game.o main.o ai.o
	$(CC) $(CFLAGS) board.o game.o main.o ai.o -o main

board.o: board.c board.h Constants.h
	$(CC) $(CFLAGS) -c board.c -o board.o

game.o: game.c game.h Constants.h
	$(CC) $(CFLAGS) -c game.c -o game.o

main.o: main.c Constants.h ai.h
	$(CC) $(CFLAGS) -c main.c -o main.o

ai.o: ai.c ai.h Constants.h
	$(CC) $(CFLAGS) -c ai.c -o ai.o

clean:
	rm -f *.o
	rm main
