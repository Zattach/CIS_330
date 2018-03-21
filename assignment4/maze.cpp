#include <fstream>
#include <iostream>
#include <string.h>
#include "maze.hpp"

Maze::Maze(int size): size(0), xStart(0), yStart(0), row(0), col(0), mazeData(""), currentDirection(DOWN), numberOfMoves(0) {
	this->size = size;
}

void Maze::readFromFile(std::ifstream &f){
	int i = 0;
	std::string temp;
	while(i < size){
		f >> temp;
		this->mazeData += temp;
		i++;
	}

	getCurrentPosition((this->yStart), (this->xStart));
	this->row = (this->yStart);
	this->col = (this->xStart);

	if(this->yStart == 0 && this->xStart != 0){
		this->currentDirection = DOWN;
	} else if(this->xStart == 0 && this->yStart != 0){
		this->currentDirection = RIGHT;
	} else if(this->yStart == this->size - 1){
		this->currentDirection = UP;
	} else if(this->xStart == this->size - 1){
		this->currentDirection = LEFT;
	}

	//std::cout << this->yStart << "\n" << this->xStart << "\n" <<this->mazeData;
}

void Maze::step(){
	bool down = isValidMove(this->col, (this->row + 1));
	bool right = isValidMove((this->col + 1), this->row);
	bool up = isValidMove(this->col, (this->row - 1));
	bool left = isValidMove((this->col - 1), this->row);

	switch(this->currentDirection){
		case DOWN:
			if(left){
				this->currentDirection = LEFT;
				this->col--;
			} else if(down){
				this->currentDirection = DOWN;
				this->row++;
			} else if(right){
				this->currentDirection = RIGHT;
				this->col++;
			} else if(up){
				this->currentDirection = UP;
				this->row--;
			}
			break;
		case RIGHT:
			if(down){
				this->currentDirection = DOWN;
				this->row++;
			} else if(right){
				this->currentDirection = RIGHT;
				this->col++;
			} else if(up){
				this->currentDirection = UP;
				this->row--;
			} else if(left){
				this->currentDirection = LEFT;
				this->col--;
			}
			break;
		case UP:
			if(right){
				this->currentDirection = RIGHT;
				this->col++;
			} else if(up){
				this->currentDirection = UP;
				this->row--;
			} else if(left){
				this->currentDirection = LEFT;
				this->col--;
			} else if(down){
				this->currentDirection = DOWN;
				this->row++;
			}
			break;
		case LEFT:
			if(up){
				this->currentDirection = UP;
				this->row--;
			} else if(left){
				this->currentDirection = LEFT;
				this->col--;
			} else if(down){
				this->currentDirection = DOWN;
				this->row++;
			} else if(right){
				this->currentDirection = RIGHT;
				this->row++;
			}
			break;
	}
	this->numberOfMoves += 1;

	std::string dir[] = {"DOWN", "RIGHT", "UP", "LEFT"};

	std::cout << dir[this->currentDirection] << "\n";
}

bool Maze::atExit(){
	if(atEdge(this->col, this->row) && getValue(this->col, this->row) == '.'){
		return true;
	} else {
		return false;
	}
}

void Maze::getCurrentPosition(int &row, int &col){
	std::size_t pos = this->mazeData.find('x');

	row = pos / this->size;
	col = pos % this->size;

	//std::cout << pos << "\n" << row << "\n" << col;
}

bool Maze::atEdge(int x, int y){
	if(x == 0 || y == 0 || x == (this->size - 1) || y == (this->size-1)){
		return true;
	} else {
		return false;
	}
}

char Maze::getValue(int x, int y){
	int pos = (this->size * y) + x;
	//std::cout << this->mazeData[pos];
	return this->mazeData[pos];
}

bool Maze::isValidMove(int x, int y){
	if(getValue(x, y) == '.'){
		return true;
	} else {
		return false;
	}
}