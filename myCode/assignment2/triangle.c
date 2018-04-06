#include <stdio.h>
#include <stdlib.h>
#include "triangle.h"

/* Allocate a triangle of height "height" (a 2-D array of int) */
void allocateNumberTriangle(const int height, int ***triangle){
	*triangle = (int **) malloc(height * sizeof(int *));
	for(int i=0; i<height; i++){
		(*triangle)[i] = (int *) malloc((1 + (i * 2)) * sizeof(int));
	}
}

/* Initialize the 2-D triangle array */
void initializeNumberTriangle(const int height, int **triangle){
	for(int i=0; i<height; i++){
		for(int j=0; j<(1 + (i * 2)); j++){
			triangle[i][j] = j;
		}
	}
}

/* Print a formatted triangle */
void printNumberTriangle(const int height, int **triangle){
	for(int i=0; i<height; i++){
		for(int j=0; j<(2 * (height - i - 1)); j++){
			printf(" ");
		}
		for(int j=0; j<(1 + (i * 2)); j++){
			printf("%d ", triangle[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/* Free the memory for the 2-D triangle array */
void deallocateNumberTriangle(const int height, int ***triangle){
	for(int i=0; i<height; i++){
		free((*triangle)[i]);
	}
	free((*triangle));
}