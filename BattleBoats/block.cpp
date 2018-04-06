#include "include/block.hpp"

/*
    Noah Palmer, Zachary Domke, Jeremiah Clothier
    CIS 330
    Group Project
    Player Header
*/

using namespace sf;

/**
 * Default Constructor
 * @see https://www.sfml-dev.org/documentation/2.0/classsf_1_1RectangleShape.php
 */

Block::Block(sf::Vector2f size, double _blockSize) : RectangleShape(size) {
	blockSize = _blockSize;
}

/**
 * Constructor for Block object
 *
 * Description: Block represent an individual "cell" of the battleboats board's grid
 *
 * @param position: SFML X,Y coordinate vector (see more at https://www.sfml-dev.org/documentation/2.0/classsf_1_1Vector2.php)
 * @param _row: the row index of a Block
 * @param _col: the column index of a Block
 * @param blockSize: pixel size of the blockSize
 */
Block::Block(Vector2f size, int _row, int _col, double _blockSize) : RectangleShape(size) {
	row = _row;
	col = _col;
	blockSize = _blockSize;
	setPosition(col * blockSize, row * blockSize);
}

/**
 * {@inheritDoc}
 * @return True if the the row and column for two different blocks are the same, False otherwise.
 */
bool Block::operator==(const Block& block){
	return row == block.row && col == block.col;
}

/**
 * {@inheritDoc}
 */
void Block::operator=(const Block& block){
	row = block.row;
	col = block.col;
	setPosition(col * blockSize, row * blockSize);
}
