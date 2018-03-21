#include "include/robot.hpp"

/*
    Noah Palmer, Zachary Domke, Jeremiah Clothier
    CIS 330
    Group Project
    Robot Class
*/

using namespace sf;

/**
 * Constructor for Robot object
 *
 * Description: Builds a Matrix of Blocks "grid" for a Robot
 *
 * @param _numRow: number of rows for the Matrix
 * @param _numCols: number of columns for the Matrix
 * @param _blockSize: the number of pixels for each block in the grid
 *
 */
Robot::Robot(int _numRows, int _numCols, double _blockSize) : Player(_numRows, _numCols, _blockSize) {
	//seed the random number
	std::srand(std::time(0));

	//move the grid over to the right
	int gSize = grid.size();
	for(int i = 0; i < gSize; i++){
		//move over by one grid, plus on blockSize space
		grid[i].move(numCols * blockSize + blockSize, 0);
	}

	hitLastGuess = false;
}

/**
 * Description: Places the Robot's Boats randomly in the grid and moves them for the GUI to display
 *
 *@param window: SFML window
 *@return void
 *
 *Result: Updates robot.boats (a vector of Boats). robot.boats will now include 5 boats
 *which have been placed in the grid
 */
void Robot::placeBoats(sf::RenderWindow& window){
	Boat boat;
	int boatSize;

	//keep placing boats as long as the port isn't empty
	while(!port.empty()){
		//get the top boat on the port
		boat = port.top();
		boatSize = boat.boatSections.size();

		//get a random row and column for the boat
		int rowVal = rand() % numRows;
		int colVal = rand() % numCols;
		int xCoord = colVal * blockSize;
		int yCoord = rowVal * blockSize;

		//initialize the random boat with the given information
		for(int i = 0; i < boatSize; i++){
			boat.boatSections[i].row = rowVal;
			boat.boatSections[i].col = colVal + i;
			boat.boatSections[i].move(xCoord, yCoord);
			boat.boatSections[i].move(numCols * blockSize + blockSize, 0);
		}

		//give the boat a random rotation
		int rotate = rand() % 4;
		for(int i = 0; i < rotate; i++){
			boat.rotate();
		}

		//if the boat is in a valid location, push the boat on the boats vector
		//and then pop off the boat so that the top of the loop can access the next boat
		if(isValidBoatPlacement(boat)){
			boats.push_back(boat);
			port.pop();
		}
	}
}

/**
 * @brief      Makes a guess for the computer AI. Make guess will make educated guesses if the previous guess was a 'hit'
 *
 * @param      window      The window
 * @param      enemyBoats  The enemy boats
 * @see        https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderWindow.php
 */
void Robot::makeGuess(sf::RenderWindow& window, std::vector<Boat>& enemyBoats){
	if(hitLastGuess){
		int row = chosenSpots[chosenSpots.size() - 1].row;
		int col = chosenSpots[chosenSpots.size() - 1].col;

		Block left(Vector2f(blockSize, blockSize), row, col - 1, blockSize);
		Block right(Vector2f(blockSize, blockSize), row, col + 1, blockSize);
		Block up(Vector2f(blockSize, blockSize), row - 1, col, blockSize);
		Block down(Vector2f(blockSize, blockSize), row + 1, col, blockSize);

		//once the robot hits, it will continue to find blocks that are around it
		//if no more valid ship guesses are around the current cell, then randomly chooses a new guess
		if(isValidGuess(left) && enemyBoatsContainsBlock(enemyBoats, left)){
			left.setFillColor(Color(150, 10, 15));
			chosenSpots.push_back(left);
		}else if(isValidGuess(right) && enemyBoatsContainsBlock(enemyBoats, right)){
			right.setFillColor(Color(150, 10, 15));
			chosenSpots.push_back(right);
		}else if(isValidGuess(up) && enemyBoatsContainsBlock(enemyBoats, up)){
			up.setFillColor(Color(150, 10, 15));
			chosenSpots.push_back(up);
		}else if(isValidGuess(down) && enemyBoatsContainsBlock(enemyBoats, down)){
			down.setFillColor(Color(150, 10, 15));
			chosenSpots.push_back(down);
		}else{
			randomGuess(window, enemyBoats);
			hitLastGuess = false;
		}
	}else{
		randomGuess(window, enemyBoats);
	}
}

/**
 * @brief      Makes a random guess for the Robot's turn.
 *
 * @param      window      The window
 * @param      enemyBoats  The enemy boats
 * @see        https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderWindow.php
 */
void Robot::randomGuess(sf::RenderWindow& window, std::vector<Boat>& enemyBoats){
	int row;
	int col;

	Block b(Vector2f(blockSize, blockSize), blockSize);

	//keep generating a new random block until it is a valid guess
	do{
		row = rand() % numRows;
		col = rand() % numCols;

		Block temp(Vector2f(blockSize, blockSize), row, col, blockSize);
		b = temp;
	}while(!isValidGuess(b));

	//if b is found over the enemy boats, then change color to dark red, else yellow
	if(enemyBoatsContainsBlock(enemyBoats, b)){
		hitLastGuess = true;
		b.setFillColor(Color(150, 10, 15));
	}else{
		b.setFillColor(Color(225, 211, 25));
	}

	//push back the block onto the chosenSpots
	chosenSpots.push_back(b);
}
