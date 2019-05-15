#include <stdio.h>
#include "square.h"
#include "triangle.h"
#include "diamond.h"

int main(){

	printf("\nProblem 1:\n");
	int size;
	do{
		printf("Please enter the size of the square [2-10]: ");
		scanf("%d", &size);
	} while(size < 2 || size > 10);

	int **square = NULL;
	allocateNumberSquare(size, &square);
	initializeNumberSquare(size, square);
	printNumberSquare(size, square);
	deallocateNumberSquare(size, &square);

	printf("\nProblem 2:\n");
	int height;
	do{
		printf("Please enter the height of the triangle [1-5]: ");
		scanf("%d", &height);
	} while(height < 1 || height > 5);

	int **triangle = NULL;
	allocateNumberTriangle(height, &triangle);
	initializeNumberTriangle(height, triangle);
	printNumberTriangle(height, triangle);
	deallocateNumberTriangle(height, &triangle);

	printf("\nProblem 3:\n");
	do{
		printf("Please enter the size of the diamnod [an odd number between 3 and 9 (inclusive)]: ");
		scanf("%d", &size);
	} while (!(size % 2) || size < 3 || size > 9);

	square = NULL;
	allocateNumberSquare(size, &square);
	initializeNumberSquare(size, square);
	printNumberDiamond(size, square);
	deallocateNumberSquare(size, &square);

	return 0;
}