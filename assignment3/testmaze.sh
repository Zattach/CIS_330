#!/bin/bash
make maze.exe
./maze.exe maze_input.txt >> maze_output.txt
diff output.txt maze_output.txt
make clean