#include <stdio.h>
#include "square.h"

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

	return 0;
}