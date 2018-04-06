#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "include/player.hpp"
#include "include/robot.hpp"
#include "include/boat.hpp"
#include "include/block.hpp"

/*
    Noah Palmer, Zachary Domke, Jeremiah Clothier
    CIS 330
    Group Project
    Game Class
*/

using namespace sf;

//global variables
int windowHeight, windowWidth;
double blockSize;
bool mousePressed, spacePressed, spaceAllowed;

/**
 * @brief      Event Listener
 *
 * @param      window  The window
 */
void checkEvent(RenderWindow& window){
	//checks for an event
	Event event;
    if(window.pollEvent(event)){
        if(event.type == Event::Closed){
        	//if event type is closed, then closes window
            window.close();
        }else if(event.type == Event::MouseButtonPressed){
        	//if event is mouse button press
            if(event.mouseButton.button == Mouse::Left){
            	//if button pressed is the left mouse button, mousePressed is true
                mousePressed = true;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        	//if key space is pressed
        	if(spaceAllowed){
        		//if space is allowed, spacePressed is true, spaceAllowed is false
	        	spacePressed = true;
	        	spaceAllowed = false;
	        }
        }
        else if(event.type == Event::KeyReleased){
        	//if key (space) is released, spaceAllowed is true
        	spaceAllowed = true;
        }
    }
}

/**
 * @brief      Draws a message
 *
 * @param      window  The window
 * @param[in]  winner  The text displayed in the message
 */
void drawMessage(RenderWindow& window, Text winner){
	window.draw(winner);
}

/**
 * @brief      Draws instructions.
 *
 * @param      window        The window
 * @param[in]  header        The header text
 * @param[in]  instructions  The instructions
 */
void drawInstructions(RenderWindow& window, Text header, Text instructions){
	window.draw(header);
	window.draw(instructions);
}

/**
 * @brief      Clears the window
 *
 * @param      window  The window
 */
void clearWindow(RenderWindow& window){
	window.clear(Color(0, 150, 0));
}

/**
 * @brief      Keeps the Player's Grid visually updated for gameplay
 *
 * @param      window  The window
 * @param      player  The player
 * @param      bot     The bottom
 * @param[in]  mouse   The mouse
 */
void drawObjectsLeftGrid(RenderWindow& window, Player& player, Robot& bot, Vector2i mouse){
	player.drawGrid(window, mouse);
	player.drawBoats(window);
	bot.drawChosenSpots(window);
}

/**
 * @brief      Keeps the Robot's Grid visually updated for gameplay
 *
 * @param      window  The window
 * @param      player  The player
 * @param      bot     The bottom
 * @param[in]  mouse   The mouse
 */
void drawObjectsRightGrid(RenderWindow& window, Player& player, Robot& bot, Vector2i mouse){
	bot.drawGrid(window, mouse);
	//bot.drawBoats(window); // NOTE, USE ONLY FOR DEBUGGING
	player.drawChosenSpots(window);
}

/**
 * @brief      Updates the GUI for a full Battleboats game
 *
 * @param      window  The window
 * @param      player  The player
 * @param      bot     The Robot (computer AI)
 */
void draw(RenderWindow& window, Player& player, Robot& bot){
	//declares mouse and block for mouse and block positions
	Vector2i mouse;
	Vector2f block;

	//loads font file
	Font font;
	if(!font.loadFromFile("fonts/Fipps-Regular.otf")){
		std::cout << "ERROR LOADING FONT FILE" << std::endl;
	}

	//instruction header
	Text header;
	header.setFont(font);
	header.setString("Battle Boats");
	header.setCharacterSize(36);
	header.setFillColor(Color::Black);
	header.setStyle(Text::Underlined);
	header.setPosition(Vector2f(blockSize * 12.5, blockSize));

	//instruction body
	Text instructions;
	instructions.setFont(font);
	std::string body = "\n\tPlace your five boats\n\t(5, 4, 3, 3, 2)\n\tPress Space to Rotate\n\n\tSearch for and destroy\n\tyour opponents boats\n\n\tBlue . . . . Ocean\n\tYellow . . Miss\n\tRed. . . . . Hit";
	instructions.setString(body);
	instructions.setCharacterSize(18);
	instructions.setFillColor(Color::Black);
	instructions.setPosition(Vector2f(blockSize * 12, blockSize * 1.25));

	//winner body
	Text winner;
	winner.setFont(font);
	winner.setCharacterSize(48);
	winner.setFillColor(Color::Black);
	winner.setStyle(Text::Underlined);
	winner.setPosition(Vector2f(blockSize * 7, blockSize));

	//lets bot place boats on the grid
	bot.placeBoats(window);

	//gets the first boat off the port
	Boat boat(player.port.top());
	player.port.pop();

	bool isPlacingBoats = true, endGame = false, playerTurn = true, gameOver = false, playerWon = true;

	//keeps going while the window is still open
	while(window.isOpen() && !endGame){
		//gets mouse position
		mouse = Mouse::getPosition(window);

		//clears window and draws the players grid
		clearWindow(window);
		drawObjectsLeftGrid(window, player, bot, mouse);

		//checks for any events 
		checkEvent(window);

		//when done placing boats, the boolean switches to false in which case the game officially starts
		if(isPlacingBoats){
			isPlacingBoats = player.placeBoats(window, mouse, boat, mousePressed, spacePressed);
			drawInstructions(window, header, instructions);
		}else{
			//draws bots grid
			drawObjectsRightGrid(window, player, bot, mouse);

			//if its not a game over
			if(!gameOver){
				//if its the players turn
				if(playerTurn){
					//if the mouse is pressed
					if(mousePressed){
						//if the player makes a valid guess
						if(player.makeGuess(window, mouse, bot.boats)){
							//switches players turn to false
							playerTurn = false;
						}
					}
				}else{
					//bot makes its guess and then its players turn again
					bot.makeGuess(window, player.boats);
					playerTurn = true;
				}

				//if bot or player won, game is over
				if(player.won(bot.boats)){
					gameOver = true;
					playerWon = true;
				}else if(bot.won(player.boats)){
					gameOver = true;
					playerWon = false;
				}
			}else{
				//if game is over, display winner
				std::string message = "";
				if(playerWon){
					message = "Player Won!";
				}else{
					message = "Robot Won!";
				}
				winner.setString(message);
				Block background(Vector2f(blockSize * 11, blockSize * 3), blockSize);
				background.setFillColor(Color(151, 133, 143));
				background.setPosition(Vector2f(blockSize * 5, 0));

				window.draw(background);
				drawMessage(window, winner);
			}
		}

		//continually sets mousePressed and spacePressed to false
		mousePressed = false;
		spacePressed = false;

		//display the current objects on the window
		window.display();
	}
}

/**
 * @brief      Controls operation of the program.
 */
int main(){
	//declares and initializes variables
	int numRows, numCols;
	numRows = numCols = 10;

	windowHeight = 600;
	blockSize = windowHeight / numRows;
	windowWidth = windowHeight * 2 + blockSize;
    mousePressed = false;
    spaceAllowed = true;

	//creates window
    RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BATTLE BOATS!!");

    Player player(numRows, numCols, blockSize);
    Robot bot(numRows, numCols, blockSize);

    //begins drawing the game
    draw(window, player, bot);

    return 0;
}
