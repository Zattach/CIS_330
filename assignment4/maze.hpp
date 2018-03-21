/*
 * maze.hpp
 *
 *  Created on: Jan 27, 2014
 *      Author: norris
 */

#ifndef MAZE_HPP_
#define MAZE_HPP_

#include <fstream>

class Maze
{
public:
	Maze(int size);
	~Maze() {}

	enum Direction { DOWN, RIGHT, UP, LEFT };

	// Implement the following functions:

	// read maze from file, find starting location
	void readFromFile(std::ifstream &f);

	// make a single step advancing toward the exit
	void step();

	// return true if the maze exit has been reached, false otherwise
	bool atExit();

	// set row and col to current position of 'x'
	void getCurrentPosition(int &row, int &col);

	// You can add more functions if you like
private:
	// Private methods
	bool atEdge(int x, int y);
	char getValue(int x, int y);
	bool isValidMove(int x, int y);

	// Private data
	int size, xStart, yStart, row, col; // size and position information
	std::string mazeData; // where the maze will be stored
	Direction currentDirection;  // direction information
	int numberOfMoves;  // for counting number of moves in solution 
};


#endif /* MAZE_HPP_ */
