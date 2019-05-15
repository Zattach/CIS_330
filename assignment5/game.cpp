#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "game.hpp"

using namespace std;

// implementation borrowed from gooli on stackoverflow:
// https://stackoverflow.com/questions/2035522/get-adjacent-elements-in-a-two-dimensional-array
struct {
	int dx;
	int dy;
} directions[] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

// game constructos
Game::Game(int row, int col){
	this->rowB = row;
	this->colB = col;
	vector<vector<char>> vec(rowB);
	for(int i = 0; i < rowB; i++){
		vec[i] = vector<char>(colB);
	}

	this->board = vec;

	initBoard();
}

// board initializer randomizes pieces on the board: F 5%, W 5%, S 40%, . 50%
void Game::initBoard(){
	srand(time(NULL));

	int randNum;

	for(int i = 0; i < this->rowB; i++){
		for(int j = 0; j < (this->colB); j++){
			randNum = rand() % 100 + 1;
			if(randNum < 6){
				this->board[i][j] = 'F';
			} else if(randNum < 11){
				this->board[i][j] = 'W';
			} else if(randNum < 51){
				this->board[i][j] = 'S';
			} else {
				this->board[i][j] = '.';
			}
		}
	}
}

// prints out a graphical display of the board
void Game::printBoard(){
	for(int i = 0; i < this->rowB; i++){
		for(int j = 0; j < this->colB; j++){
			cout << this->board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

// makes one step in the game (has some issues with farmers)
void Game::stepBoard(){
	vector<vector<char>> newBoard = this->board;
	char val;

	for(int i = 0; i < this->rowB; i++){
		for(int j = 0; j < this->colB; j++){
			val = stepIndividual(newBoard, i, j);
			if(val == 'X'){
				newBoard[i][j] = '.';
				int x = replaceFarmer(i, j);
				newBoard[i + directions[x].dy][j + directions[x].dx] = 'F';
			} else {
				newBoard[i][j] = val;
			}
		}
	}
	this->board = newBoard;
}

// makes an indivudal step by reading the pieces and surroundings
char Game::stepIndividual(vector<vector<char>> newBoard, int row, int col){
	char val = this->board[row][col];
	char newVal = newBoard[row][col];
	char newChar = val;
	int empty = getEmpty(row, col);
	int sheep = getSheep(row, col);
	int wolves = getWolves(row, col);
	int farmers = getFarmers(row, col);

	if(val == 'S' && newVal != 'F'){
		if(sheep > 3 || wolves > 0){
			newChar = '.';
		}
	} else if(val == 'W' && newVal != 'F'){
		if((wolves > 3) || (farmers > 0) || ((sheep + farmers) == 0)){
			newChar = '.';
		}
	} else if(val == 'F' && newVal == 'F'){
		if(empty > 0){
			newChar = 'X';
		}
	} else {
		if(sheep == 2){
			newChar = 'S';
		} else if(wolves == 2){
			newChar = 'W';
		} else if(farmers == 2){
			newChar = 'F';
		}
	}
	return newChar;
}

// attempts to choose which direction the farmer should move
int Game::replaceFarmer(int row, int col){
	srand(time(NULL));
	int empty = getEmpty(row, col);
	int randNum = rand() % empty;
	int num = 0;
	int nRow, nCol;

	for(int i = 0; i < 8; i++){
		nRow = row + directions[i].dy;
		nCol = col + directions[i].dx;
		if(nRow >= 0 && nCol >= 0 && nRow < this->rowB && nCol < this->colB){
			if(this->board[nRow][nCol] == '.'){
				if(num == randNum){
					return i;
				}
				num++;
			}
		}
	}
	return 0;
}

// returns how many empty cells surround the piece
int Game::getEmpty(int row, int col){
	int num = 0;
	int nRow, nCol;
	for(int i = 0; i < 8; i++){
		nRow = row + directions[i].dy;
		nCol = col + directions[i].dx;
		if(nRow >= 0 && nCol >= 0 && nRow < this->rowB && nCol < this->colB){
			if(this->board[nRow][nCol] == '.'){
				num++;
			}
		}
	}
	return num;
}

// returns how many sheep cells surround the piece
int Game::getSheep(int row, int col){
	int num = 0;
	int nRow, nCol;
	for(int i = 0; i < 8; i++){
		nRow = row + directions[i].dy;
		nCol = col + directions[i].dx;
		if(nRow >= 0 && nCol >= 0 && nRow < this->rowB && nCol < this->colB){
			if(this->board[nRow][nCol] == 'S'){
				num++;
			}
		}
	}
	return num;
}

// returns how many wolf cells surround the piece
int Game::getWolves(int row, int col){
	int num = 0;
	int nRow, nCol;
	for(int i = 0; i < 8; i++){
		nRow = row + directions[i].dy;
		nCol = col + directions[i].dx;
		if(nRow >= 0 && nCol >= 0 && nRow < this->rowB && nCol < this->colB){
			if(this->board[nRow][nCol] == 'W'){
				num++;
			}
		}
	}
	return num;
}

// returns how many farmer cells surround the piece
int Game::getFarmers(int row, int col){
	int num = 0;
	int nRow, nCol;
	for(int i = 0; i < 8; i++){
		nRow = row + directions[i].dy;
		nCol = col + directions[i].dx;
		if(nRow >= 0 && nCol >= 0 && nRow < this->rowB && nCol < this->colB){
			if(this->board[nRow][nCol] == 'F'){
				num++;
			}
		}
	}
	return num;
}
