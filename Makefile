# Compiler and compiler flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
# Include path for SDL2 header files
SDL_INC = -I/opt/homebrew/Cellar/sdl2/2.30.2/include

# Library path for SDL2 libraries
SDL_LIB = -L/opt/homebrew/Cellar/sdl2/2.30.2/lib -lSDL2


all: src/board.o src/game.o src/main.o
	$(CC) $(CFLAGS) src/board.o src/game.o src/main.o -o main

src/board.o: src/board.c src/board.h
	$(CC) $(CFLAGS) -c src/board.c -o src/board.o

src/game.o: src/game.c src/game.h
	$(CC) $(CFLAGS) -c src/game.c -o src/game.o

src/main.o: src/main.c src/game.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

