SOURCES = $(wildcard *.c)

CC = gcc
CFLAGS = -std=c11 -g -Wall

# Pattern used in target and prerequisites
%.o: %.c %.h
	$(CC) -c $(CFLAGS) $<

maze.exe: maze.o
	$(CC) -o $@ $^ -lm

# To get rid of all compiler-generated binary files, run "make clean"
clean: 
	$(RM) $(wildcard *.exe) $(wildcard *.o)
