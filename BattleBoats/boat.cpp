#include "include/boat.hpp"

/*
    Noah Palmer, Zachary Domke, Jeremiah Clothier
    CIS 330
    Group Project
    Player Header
*/

using namespace sf;

/**
 * @brief      Default Constructor for the object.
 */
Boat::Boat(){
	//on default, sets the variables to invalid numbers
	size = -999;
	blockSize = -999;
	rotationNumber = -999;
}

/**
 * @brief      Constructs the object.
 *
 * @param[in]  _size       The length of a boat
 * @param[in]  _blockSize  The block size (pixel)
 */
Boat::Boat(int _size, double _blockSize){
	//sets size and blockSize
	size = _size;
	blockSize = _blockSize;

	//adds the size number of blocks to the boatSections vector
	for(int i = 0; i < size; i++){
		Block block(Vector2f(blockSize, blockSize), 0, i, blockSize);
		boatSections.push_back(block);
	}

	//initializes rotation number to 0
	rotationNumber = 0;
}

/**
 * @brief      Copy Constructor for object.
 *
 * @param[in]  boat  The boat
 */
Boat::Boat(const Boat& boat){
	//copies information from another boat to this boat
	size = boat.size;
	blockSize = boat.blockSize;
	boatSections.clear();
	for(int i = 0; i < size; i++){
		boatSections.push_back(boat.boatSections[i]);
	}

	rotationNumber = boat.rotationNumber;
}

/**
 * @param[in]  boat  The boat
 * {@inheritDoc}
 */
void Boat::operator=(const Boat& boat){
	//copies information from another boat to this boat
	size = boat.size;
	blockSize = boat.blockSize;
	boatSections.clear();
	for(int i = 0; i < size; i++){
		boatSections.push_back(boat.boatSections[i]);
	}

	rotationNumber = boat.rotationNumber;
}

/**
 * @brief      Rotates the boat
 */
void Boat::rotate(){
	int numCols = 10;

	//calculates the new position of each block after a rotation
	for(int i = 0; i < size; i++){
		if(rotationNumber == 0){
			boatSections[i].move(-1 * i * blockSize, i * blockSize);
		}else if(rotationNumber == 1){
			boatSections[i].move(-1 * i * blockSize, -1 * i * blockSize);
		}else if(rotationNumber == 2){
			boatSections[i].move(i * blockSize, -1 * i * blockSize);
		}else if(rotationNumber == 3){
			boatSections[i].move(i * blockSize, i * blockSize);
		}

		//sets the new row and column for each block after the rotation
		Vector2f pos = boatSections[i].getPosition();
		boatSections[i].row = int(pos.y) / int(blockSize);
		boatSections[i].col = int(pos.x) / int(blockSize) - numCols - 1;
	}

	//adjusts the rotation number
	rotationNumber = (rotationNumber + 1) % 4;
}

/**
 * @brief      Sets the position of the Boat
 *
 * @param[in]  mouse  The mouse, the "pivot" location of boat
 */
void Boat::setPosition(const Vector2i& mouse){
	//gets the position of the head of the boat
	Vector2f head = boatSections[0].getPosition();

	//creates the shift based upon the position of the mouse, then uses fmod to lock the
	//shifting blocks into a grid format
	double xShift = mouse.x - head.x;
	if(fmod(xShift, blockSize) <= 0){
		xShift -= fmod(xShift, blockSize) + blockSize;
	} else {
		xShift -= fmod(xShift, blockSize);
	}

	double yShift = mouse.y - head.y;
	if(fmod(yShift, blockSize) <= 0){
		yShift -= fmod(yShift, blockSize) + blockSize;
	} else {
		yShift -= fmod(yShift, blockSize);
	}

	//resets the blocks of the boatSections vector to a new row/col based upon its position
	for(int i = 0; i < size; i++){
		boatSections[i].move(xShift, yShift);

		Vector2f pos = boatSections[i].getPosition();
		boatSections[i].row = int(pos.y) / int(blockSize);
		boatSections[i].col = int(pos.x) / int(blockSize);
	}
}
