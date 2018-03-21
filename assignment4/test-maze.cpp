#include <fstream>
#include <iostream>
#include <string>
#include "maze.hpp"

using namespace std;

int main(int argc, char *argv[]){
	if(argc != 2){
		cout << "usage: " << argv[0] << " <filename>\n";
		return 1;
	} 

	ifstream file (argv[1]);
	int numberOfTestCases = 0;
	int mazeSize = 0;

	if(!file.is_open()){
		cout << "Could not open file\n";
	}
	file >> numberOfTestCases;

	for(int testCaseNumber = 0; testCaseNumber < numberOfTestCases; testCaseNumber++){
		cout << "ENTER\n";

		file >> mazeSize;
		Maze::Maze maze(mazeSize);
		maze.readFromFile(file);

        if(mazeSize < 10 || mazeSize > 30){
        	cout << "\n\nWrong size of maze. Maze must be between 10 and 30.\n\n";
            continue;
        }
        
		while(!maze.atExit()){
			maze.step();
		}
		
		cout << "EXIT\n***\n";
	}
}