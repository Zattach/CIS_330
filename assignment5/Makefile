CXX = g++
CFLAGS = -std=c++14 -g -Wall

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $<  

test-game.exe: test-game.o game.o
	$(CXX) -o $@ $^

clean:
	$(RM) test-game.exe $(wildcard *.o)
