# Makefile for Dots and Boxes (CMPS 241 project)
#   make         builds the game: ./dotsandboxes
#   make test    builds and runs the unit tests
#   make clean   deletes the .o files and the programs

CC = gcc
CFLAGS = -Wall -Werror -g -std=c11 -c

SOURCES = main.c board.c display.c input.c bot.c
OBJECTS = $(SOURCES:.c=.o)
OUTPUT = dotsandboxes
TEST_OUTPUT = test_board

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^

main.o: main.c board.h display.h input.h bot.h
	$(CC) $(CFLAGS) -o $@ $<

board.o: board.c board.h
	$(CC) $(CFLAGS) -o $@ $<

display.o: display.c display.h board.h
	$(CC) $(CFLAGS) -o $@ $<

input.o: input.c input.h
	$(CC) $(CFLAGS) -o $@ $<

bot.o: bot.c bot.h board.h
	$(CC) $(CFLAGS) -o $@ $<

test: $(TEST_OUTPUT)
	./$(TEST_OUTPUT)

$(TEST_OUTPUT): test_board.o board.o
	$(CC) -o $@ $^

test_board.o: test_board.c board.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean test
clean:
	rm -f *.o $(OUTPUT) $(TEST_OUTPUT)
