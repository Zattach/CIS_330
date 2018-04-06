#include <stdio.h>
#include <stdlib.h>
#include "diamond.h"

/* Print a formatted square */
void printNumberDiamond(const int size, int **square){
	int i;
	for(i=0; i<=(size / 2); i++){
		for(int j=0; j<((size / 2) - i); j++){
			printf("  ");
		}

		for(int j=0; j<(1 + (i * 2)); j++){
			printf("%d ", square[i][j]);
		}
		printf("\n");
	}

	for(i=((size / 2) - 1); i>=0; i--){
		for(int j=0; j<((size / 2) - i); j++){
			printf("  ");
		}

		for(int j=0; j<(1 + (i * 2)); j++){
			printf("%d ", square[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}