#ifndef __PLAYER__
#define __PLAYER__

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include "boat.hpp"
#include "block.hpp"

/*
    Noah Palmer, Zachary Domke, Jeremiah Clothier
    CIS 330
    Group Project
    Player Header
*/

class Player{
	protected:
		int numRows;
		int numCols;
		int blockSize;

	public:
		std::vector<Block> grid;

		std::vector<Boat> boats;

		std::vector<Block> chosenSpots;

		std::stack<Boat> port;

		Player(int _numRows, int _numCols, double _blockSize);

		~Player(){};

		void rotateBoat();

		bool placeBoats(sf::RenderWindow& window, sf::Vector2i mouse, Boat& boat, bool mousePressed, bool spacePressed);

		bool isValidBoatPlacement(Boat& boat);

		bool makeGuess(sf::RenderWindow& window, sf::Vector2i mouse, std::vector<Boat>& enemyBoats);

		bool isValidGuess(Block& block);

		bool enemyBoatsContainsBlock(std::vector<Boat>& enemyBoats, Block& block);

		void drawGrid(sf::RenderWindow& window, sf::Vector2i mouse);

		void drawBoats(sf::RenderWindow& window);

		void drawChosenSpots(sf::RenderWindow& window);

		bool won(std::vector<Boat> enemyBoats);
};

#endif //__PLAYER__
