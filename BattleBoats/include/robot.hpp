#ifndef __ROBOT__
#define __ROBOT__

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "player.hpp"

/*
    Noah Palmer, Zachary Domke, Jeremiah Clothier
    CIS 330
    Group Project
    Robot Header
*/

class Robot : public Player {
	private:
		bool hitLastGuess;

		void randomGuess(sf::RenderWindow& window, std::vector<Boat>& enemyBoats);

	public:
		Robot(int _numRows, int _numCols, double _blockSize);

		~Robot(){};

		void placeBoats(sf::RenderWindow& window);

		void makeGuess(sf::RenderWindow& window, std::vector<Boat>& enemyBoats);
};

#endif //__ROBOT__
