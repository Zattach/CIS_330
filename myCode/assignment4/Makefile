CXX = g++
CFLAGS = -std=c++14 -g -Wall

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $< 

# Add any additional targets you may have here 

test-maze.exe: test-maze.o maze.o
	$(CXX) -o $@ $^

# Link with external main (on ix-dev only)
test-main.exe: main.o  maze.o utils.o #add your objects to this line
	$(CXX) -o $@ $^

clean:
	$(RM) test-main.exe $(OBJECTS)
