#include <stdio.h>
#include "square.h"
#include "diamond.h"

int main(){

	printf("\nProblem 3:\n");
	int size;
	do{
		printf("Please enter the size of the diamnod [an odd number between 3 and 9 (inclusive)]: ");
		scanf("%d", &size);
	} while (!(size % 2) || size < 3 || size > 9);

	int ** square = NULL;
	allocateNumberSquare(size, &square);
	initializeNumberSquare(size, square);
	printNumberDiamond(size, square);
	deallocateNumberSquare(size, &square);

	return 0;
}
