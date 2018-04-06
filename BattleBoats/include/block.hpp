#ifndef __BLOCK__
#define __BLOCK__

#include <SFML/Graphics.hpp>

/*
    Noah Palmer, Zachary Domke, Jeremiah Clothier
    CIS 330
    Group Project
    Player Header
*/

class Block: public sf::RectangleShape{
	private:
		double blockSize;

	public:
		int row, col;

		Block(sf::Vector2f size, double _blockSize);

		Block(sf::Vector2f size, int _row, int _col, double _blockSize);

		~Block(){};

		bool operator==(const Block& block);

		void operator=(const Block& block);
};

#endif //__VEC__
