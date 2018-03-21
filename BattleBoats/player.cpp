#include "include/player.hpp"

/*
    Noah Palmer, Zachary Domke, Jeremiah Clothier
    CIS 330
    Group Project
    Player Class
*/

using namespace sf;

/**
 * @brief      Constructs the object.
 *
 * @param[in]  _numRows    The number of rows
 * @param[in]  _numCols    The number of cols
 * @param[in]  _blockSize  The block size (pixels)
 */
Player::Player(int _numRows, int _numCols, double _blockSize){
	//sets class variables
	numRows = _numRows;
	numCols = _numCols;
	blockSize = _blockSize;

	//cycles over the number of rows and columns, creating the blocks and storing them in the grid vector
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j++){
			Block block(Vector2f(blockSize, blockSize), i, j, blockSize);
			//block.setPosition(i * blockSize, j * blockSize);
			block.setOutlineColor(Color(0, 0, 0));
			block.setOutlineThickness(.5);
			grid.push_back(block);
		}
	}

	//pushes new boats onto the port stack
	port.push(Boat());
	port.push(Boat(2, blockSize));
	port.push(Boat(3, blockSize));
	port.push(Boat(3, blockSize));
	port.push(Boat(4, blockSize));
	port.push(Boat(5, blockSize));
}

/**
 * @brief      Allows the Player to place their 5 Battleboats.
 *
 * @param      window        The window (GUI)
 * @param[in]  mouse         The mouse
 * @param      boat          The boat being placed
 * @param[in]  mousePressed  Checks if the mouse was pressed
 * @param[in]  spacePressed  Checks if the spacebar was pressed
 *
 * @return     Returns false if all the Player's Boats have been placed, False otherwise.
 */
bool Player::placeBoats(sf::RenderWindow& window, sf::Vector2i mouse, Boat& boat, bool mousePressed, bool spacePressed){
	if(port.empty()){
		return false;
	}

	boat.setPosition(mouse);

	bool goodToGo = isValidBoatPlacement(boat);

	int size = boat.boatSections.size();
	// TODO: The if-else statement below are the same
	// LINES 50-64 Same result for if-else cases
	if(goodToGo){
		//setColor to good boat color
		for(int i = 0; i < size; i++){
			boat.boatSections[i].setFillColor(Color(169, 169, 169));
			window.draw(boat.boatSections[i]);
		}
	}else{
		//setColor to bad boat color
		for(int i = 0; i < size; i++){
			boat.boatSections[i].setFillColor(Color(200, 0, 0));
			window.draw(boat.boatSections[i]);
		}
	}

	//if mouse is pressed and good to go, then pushes the boat onto the boats vector, the next boat
	//is loaded as the boat, and then the port pops that boat
	if(mousePressed){
		if(goodToGo){
			boats.push_back(boat);
			boat = port.top();

			port.pop();
		}
	}

	//if space is pressed, rotate the boat
	if(spacePressed){
		boat.rotate();
	}

	return true;
}

/**
 * @brief      Determines if boat has properly placemed.
 *
 * @param      boat  The boat being placed
 *
 * @return     True if valid boat placement, False otherwise.
 */
bool Player::isValidBoatPlacement(Boat& boat){
	//checks the make sure all boats sections are within the bounds AND do not overlap
	int boatSize = boat.boatSections.size();
	for(int i = 0; i < boatSize; i++){
		int numBoats = boats.size();
		for(int j = 0; j < numBoats; j++){
			int _boatSize = boats[j].boatSections.size();
			for(int k = 0; k < _boatSize; k++){
				if(boat.boatSections[i] == boats[j].boatSections[k]){
					return false;
				}
			}
		}
		//checks for out of bounds here
		if(boat.boatSections[i].row < 0 || boat.boatSections[i].row >= numRows || 
			boat.boatSections[i].col < 0 || boat.boatSections[i].col >= numCols){
			return false;
		}
	}

	return true;
}

/**
 * @brief      Allows the Player to make a guess for a cell
 *
 * @param      window      The window (GUI)
 * @param[in]  mouse       The mouse
 * @param      enemyBoats  The enemy's boats locations
 *
 * @return     True if the cell guessed was correctly selected and will change the color of the guessed cell, False otherwise and no change to the cell will be made.
 */
bool Player::makeGuess(sf::RenderWindow& window, sf::Vector2i mouse, std::vector<Boat>& enemyBoats){
	//gets the the row and column the mouse is over
	int row = int(mouse.y / blockSize);
	int col = int(mouse.x / blockSize) - numRows - 1;

	//creates a new block with those row and col information
	Block b(Vector2f(blockSize, blockSize), row, col, blockSize);
	b.move(blockSize + numCols * blockSize, 0);

	if(isValidGuess(b)){
		//if b is found over the enemy boats, then change color to dark red, else yellow
		if(enemyBoatsContainsBlock(enemyBoats, b)){
			b.setFillColor(Color(150, 10, 15));
		}else{
			b.setFillColor(Color(225, 211, 25));
		}

		chosenSpots.push_back(b);

		return true;
	}else{
		return false;
	}
}

/**
 * @brief      Determines if valid guess.
 *
 * @param      block  The block (indivual cell in the grid)
 *
 * @return     True if a valid cell is guessed, False otherwise.
 */
bool Player::isValidGuess(Block& block){
	int size = chosenSpots.size();

	//returns false if the block has already been chosen
	for(int i = 0; i < size; i++){
		if(block == chosenSpots[i]){
			return false;
		}
	}

	//returns false if its not within bounds
	if(block.row < 0 || block.row >= numRows || block.col < 0 || block.col >= numCols){
		return false;
	}

	//otherwise returns true
	return true;
}

/**
 * @brief      Checks to see if a block has the same coordinates as an enemy's boat
 *
 * @param      enemyBoats  The enemy boats
 * @param      block       The block
 *
 * @return     True if the block is a hit, False otherwise.
 */
bool Player::enemyBoatsContainsBlock(std::vector<Boat>& enemyBoats, Block& block){
	//cycles through the enemy boats, if at any point, the enemy boat contains the block,
	//returns true, otherwise false
	int numEnemyBoats = enemyBoats.size();
	for(int i = 0; i < numEnemyBoats; i++){
		int enemyBoatsSize = enemyBoats[i].boatSections.size();
		for(int j = 0; j < enemyBoatsSize; j++){
			if(enemyBoats[i].boatSections[j] == block){
				return true;
			}
		}
	}
	return false;
}

/**
 * @brief      Draws a grid.
 *
 * @param      window  The window
 * @param[in]  mouse   The mouse
 */
void Player::drawGrid(RenderWindow& window, Vector2i mouse){
	int size = numRows * numCols;
	Vector2f block;

	for(int i = 0; i < size; i++){
		block = grid[i].getPosition();

		//if the mouse is over this specific block, then make it a darker colored block, otherwise, normal ocean color
		if(mouse.x > block.x && mouse.y > block.y && mouse.x < block.x + blockSize && mouse.y < block.y + blockSize){
			grid[i].setFillColor(Color(30, 50, 150));
		}else{
			grid[i].setFillColor(Color(30, 50, 200));
		}
		window.draw(grid[i]);
	}
}

/**
 * @brief      Draws the boats.
 *
 * @param      window  The window
 */
void Player::drawBoats(sf::RenderWindow& window){
	int boatsSize = boats.size();
	for(int i = 0; i < boatsSize; i++){
		int boatSize = boats[i].boatSections.size();
		for(int j = 0; j < boatSize; j++){
			boats[i].boatSections[j].setFillColor(Color(105, 105, 105));
			window.draw(boats[i].boatSections[j]);
		}
	}
}

/**
 * @brief      Draws the Player's chosen spots.
 *
 * @param      window  The window
 */
void Player::drawChosenSpots(sf::RenderWindow& window){
	int size = chosenSpots.size();
	for(int i = 0; i < size; i++){
		window.draw(chosenSpots[i]);
	}
}

/**
 * @brief      Checks if the Player has won the Game.
 *
 * @param[in]  enemyBoats  The enemy boats
 *
 * @return     True if the player has sunken all the Robot's Boats, False otherwise.
 */
bool Player::won(std::vector<Boat> enemyBoats){
	bool found;

	//cycles through the enemyBoats, at each boat, goes through the boatSections, if 
	//all blocks of an enemy boat are equal at some point to a chosen spot, it is found
	//if it is not found, returns false. If it gets through, finding all enemy boat blocks
	//in the chosenSpots, then returns true
	int numEnemyBoats = enemyBoats.size();
	int cSize = chosenSpots.size();
	for(int i = 0; i < numEnemyBoats; i++){
		int enemyBoatSize = enemyBoats[i].boatSections.size();
		for(int j = 0; j < enemyBoatSize; j++){
			found = false;
			for(int k = 0; k < cSize; k++){
				if(chosenSpots[k] == enemyBoats[i].boatSections[j]){
					found = true;
				}
			}
			if(!found){
				return false;
			}
		}
	}
	return true;
}
