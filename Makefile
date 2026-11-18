# Makefile for Dots and Boxes (CMPS 241 project)
#   make         builds the game: ./dotsandboxes
#   make clean   deletes the .o files and the program

CC = gcc
CFLAGS = -Wall -Werror -g -std=c11 -c

SOURCES = main.c board.c display.c
OBJECTS = $(SOURCES:.c=.o)
OUTPUT = dotsandboxes

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^

main.o: main.c board.h display.h
	$(CC) $(CFLAGS) -o $@ $<

board.o: board.c board.h
	$(CC) $(CFLAGS) -o $@ $<

display.o: display.c display.h board.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f *.o $(OUTPUT)
