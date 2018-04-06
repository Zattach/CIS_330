#include <iostream>
#include "game.hpp"

using namespace std;

int main(){
	int row, col, steps;

	// requests size of board 
	cout << "Please enter the size of the grid (int int): ";
	cin >> row >> col;

	// requests number of moves to be made
	cout << "Please enter the number of steps (int): ";
	cin >> steps;

	// initializes the board and prints it
	Game game(row, col);
	game.printBoard();

	// runs through all steps of the game
	for(int i = 1; i <= steps; i++){
		cin.ignore();
		cout << "Step " << i <<":\n";
		game.stepBoard();
		game.printBoard();
	}
	
	return 0;
}