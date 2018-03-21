#ifndef __BOAT__
#define __BOAT__

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "block.hpp"

/*
    Noah Palmer, Zachary Domke, Jeremiah Clothier
    CIS 330
    Group Project
    Boat Header
*/

class Boat{
	private:
		int size;
		int rotationNumber;
		double blockSize;

	public:
		std::vector<Block> boatSections;

		Boat();

		Boat(int _size, double _blockSize);

		Boat(const Boat& boat);

		~Boat(){};

		void operator=(const Boat& boat);

		void rotate();

		void setPosition(const sf::Vector2i& mouse);
};

#endif //__BOAT__
