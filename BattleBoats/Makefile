CXX = g++
SFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Compiles all neccessary cpp files into objects
%.o: %.cpp
	$(CXX) -c $< -o $@

# Links object files together making one executable
battleboats.exe: game.o player.o robot.o boat.o block.o  #add your objects to this line
	$(CXX) -o $@ $^ $(SFLAGS)

# Cleans all object files and executables
clean:
	$(RM) battleboats.exe $(wildcard *.o)