#include <vector>

#ifndef GAME_HPP_
#define GAME_HPP_

// delares all public and private elements of game.cpp
class Game{

public:
	Game(int row, int col);

	void printBoard();
	void stepBoard();

private:
	std::vector<std::vector<char>> board;

	int rowB, colB;

	void initBoard();
	char stepIndividual(std::vector<std::vector<char>> newBoard, int row, int col);
	int replaceFarmer(int row, int col);
	int getEmpty(int row, int col);
	int getSheep(int row, int col);
	int getWolves(int row, int col);
	int getFarmers(int row, int col);
	
};

#endif 
