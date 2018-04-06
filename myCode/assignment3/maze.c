/*
 * Zach Domke
 * CIS 330
 * 2/1/18
 */

// header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// defines global variables and typedef
#define MAX_MAZE_SIZE 30

typedef enum { DOWN, RIGHT, UP, LEFT } Direction;

// defines global functions
void printDir(Direction dir);
void printMaze(char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE], int mazeSize);
void mazeSolve( char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE], int mazeSize, const int startX, const int startY, int currX, int currY, Direction dir);


// main function takes in a list of mazes and solves them
int main( int argc, const char* argv[] ){
    if( argc != 2 ) { 
        //checks for the input file name
        printf( "error; no input file name\n" );
        return 1;
    }

    // saves the input file and creates an array titled maze
    FILE *filePointer;
    filePointer = fopen( argv[1], "r" );
    char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE];


    int numberOfTestCases = 0;
    fscanf( filePointer, "%d\n", &numberOfTestCases );

    for( int testCaseNumber = 0; testCaseNumber < numberOfTestCases; testCaseNumber++ ) {
        
        // initializes variable mazeSize, which is used throughout
        int mazeSize = 0;
        fscanf( filePointer, "%d\n", &mazeSize );

        // prints ENTER signifying  the start of the maze
        printf( "ENTER\n" );

        // initializes variables used later
        int startX, startY;
        Direction dir = UP;

        // saves the maze into a 2D array as well as finds the starting location
        for(int i = 0; i < mazeSize; i++){
            for(int j = 0; j < (mazeSize - 1); j++){
                fscanf(filePointer, "%c ", &maze[i][j]);
        		if(maze[i][j] == 'x'){
        			startX = j;
        			startY = i;
        		}
            }
            fscanf(filePointer, "%c\n", &maze[i][mazeSize - 1]);
        }

        // determines if the size given is viable. moves to the next maze if it is not
        // comes after the section above so that it will not mess up the scanning proccess
        if(mazeSize < 10 || mazeSize > 30){
            printf("\n\nWrong size of maze. Maze must be between 10 and 30.\n\n");
            continue;
        }

        // determines the starting direction
        if(maze[startY + 1][startX] == '.'){
        	dir = DOWN;
        } else if(maze[startY][startX + 1] == '.'){
        	dir = RIGHT;
        } else if(maze[startY - 1][startX] == '.'){
        	dir = UP;
        } else if(maze[startY][startX - 1] == '.'){
        	dir = LEFT;
        }

        // runs mazeSolve
        mazeSolve(maze, mazeSize, startX, startY, startX, startY, dir);

        // prints EXIT signifying leaving the maze
        printf( "EXIT\n***\n" );        
    }

    // closes the connection to the input file and the main method
    fclose( filePointer );
    return 0;
}

// printDir is a method that simply prints our the direction we will move in
void printDir(Direction dir){
	switch(dir){
		case DOWN: printf("DOWN\n");
			break;
		case RIGHT: printf("RIGHT\n");
			break;
		case UP: printf("UP\n");
			break;
		case LEFT: printf("LEFT\n");
			break;
	}
}

// printMaze was a test function to make sure I was saving the maze correctly
void printMaze(char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE], int mazeSize){
        for(int i = 0; i < mazeSize; i++){
            for(int j = 0; j < mazeSize; j++){
                printf("%c ", maze[i][j]);
            }
            printf("\n");
        }
}

// mazeSolve is the heart of the program and solves the maze itself by looking at the surrounding positions
void mazeSolve( char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE], int mazeSize, const int startX, const int startY, int currX, int currY, Direction dir){
    int done = 0;
    Direction newDir;
    char down, right, up, left;

    while(!done){

    	// reads the character at each space surrounding our current position
        down = maze[currY + 1][currX];
        right = maze[currY][currX + 1];
        up = maze[currY - 1][currX];
        left = maze[currY][currX - 1];

        // which direction are we moving in?
        switch(dir){

        	// if the direction we are moving in is down, then we look at the walls surrounding us after the move
            case DOWN:
            	if(left != '@' && left != 'x'){
            		newDir = LEFT;
            		currX--;
            	} else if(down != '@' && down != 'x'){
            		newDir = DOWN;
            		currY++;
            	} else if(right != '@' && right + 1 != 'x'){
            		newDir = RIGHT;
            		currX++;
            	} else if(up != '@' && up != 'x'){
            		newDir = UP;
            		currY--;
            	}
                break;

			// if the direction we are moving in is right, then we look at the walls surrounding us after the move
        	case RIGHT:
            	if(down != '@' && down != 'x'){
            		newDir = DOWN;
            		currY++;
            	} else if(right != '@' && right != 'x'){
            		newDir = RIGHT;
            		currX++;
            	} else if(up != '@' && up != 'x'){
            		newDir = UP;
            		currY--;
            	} else if(left != '@' && left != 'x'){
            		newDir = LEFT;
            		currX--;
            	}
        	    break;

        	// if the direction we are moving in is up, then we look at the walls surrounding us after the move
        	case UP:
            	if(right != '@' && right != 'x'){
            		newDir = RIGHT;
            		currX++;
            	} else if(up != '@' && up != 'x'){
            		newDir = UP;
            		currY--;
            	} else if(left != '@' && left != 'x'){
            		newDir = LEFT;
            		currX--;
            	} else if(down != '@' && down != 'x'){
            		newDir = DOWN;
            		currY++;
            	}
        	    break;

        	// if the direction we are moving in is left, then we look at the walls surrounding us after the move
        	case LEFT:
            	if(up != '@' && up != 'x'){
            		newDir = UP;
            		currY--;
            	} else if(left != '@' && left != 'x'){
            		newDir = LEFT;
            		currX--;
            	} else if(down != '@' && down != 'x'){
            		newDir = DOWN;
            		currY++;
            	} else if(right != '@' && right != 'x'){
            		newDir = RIGHT;
            		currX++;
            	}
        	    break;
    	}

    	// a long if statement that checks if we have finished the maze
    	if((maze[currY][currX] != 'x') && ((currX == 0 || currX == (mazeSize - 1)) || currY == 0 || currY == (mazeSize - 1))){
        	done = 1;
    	} 

    	// determines the new direction and prints it out 
    	dir = newDir;
    	printDir(dir);
	}
}