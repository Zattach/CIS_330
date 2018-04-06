#ifndef __SQUARE_H_
#define __SQUARE_H_

/* Allocate a square of size "size" (a 2-D array of int) */
void allocateNumberSquare(const int size, int ***square);

/* Initialize the 2-D square array */
void initializeNumberSquare(const int size, int **square);

/* Print a formatted square */
void printNumberSquare(const int size, int **square);

/* Free the memory for the 2-D square array */
void deallocateNumberSquare(const int size, int ***square);

#endif
