SOURCES = $(wildcard *.c)

CC = gcc
CFLAGS = -std=c11 -g -Wall

# Pattern used in target and prerequisites
%.o: %.c %.h
	$(CC) -c $(CFLAGS) $<

tests: test-square.exe test-triangle.exe test-diamond.exe test-all.exe

test-square.exe: test-square.o square.o
	$(CC) -o $@ $^ -lm

test-triangle.exe: test-triangle.o triangle.o
	$(CC) -o $@ $^ -lm

test-diamond.exe: test-diamond.o diamond.o
	$(CC) -o $@ $^ -lm

test-all.exe: square.o triangle.o diamond.o test.o
	$(CC) -o $@ $^ -lm

test-main.exe: square.o triangle.o diamond.o main.o
	$(CC) -o $@ $^ -lm

memcheck: test-all.exe
	valgrind --leak-check=yes --track-origins=yes test-all.exe

# To get rid of all compiler-generated binary files, run "make clean"
clean: 
	$(RM) $(wildcard *.exe) $(wildcard *.o)
