#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int **num;
	int size = 5, i, j;

	// Allocate memory for 2-D int array
	num = (int **) malloc (size * sizeof(int *));
	for (i = 0; i < size; i++){
		num[i] = (int *) malloc (size * sizeof(int *));
		for (j = 0; j < size; j++)
			num[i][j] = i * size + j;
	}

	// Print values
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("%d ", num[i][j]);
		}
		printf("\n");
	}

	// Deallocate memory
	for (i = 0; i < size; i++)
		free(num[i]);
	free(num);
}