#include <stdio.h>
#include "triangle.h"

int main(){

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

	return 0;
}