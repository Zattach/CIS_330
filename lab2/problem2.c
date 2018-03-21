#include <stdio.h>
#define MAX 10


void printArray(int a[MAX][MAX], int m, int n){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int arrayEqual(int a[MAX][MAX], int b[MAX][MAX], int m, int n){
	int test = 1;

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(a[i][j] != b[i][j]){
				test = 0;
				return test;
			}
		}
	}

	return test;
}

int main(){
	printf("Please enter how many columns the arrays should have (< 10): ");
	int col;
	scanf("%d", &col);


	printf("Please enter how many rows the arrays should have (<10): ");
	int row;
	scanf("%d", &row);

	int arrA[MAX][MAX];
	int arrB[MAX][MAX];

	for(int i = 0; i < col; i++){
		for(int j = 0; j < row; j++){
			arrA[i][j] = j;
		}
	}

	for(int i = 0; i < col; i++){
		for(int j = 0; j < row; j++){
			arrB[i][j] = i;
		}
	}

	printf("\nHere is array A:\n");
	printArray(arrA, col, row);
	printf("Here is array B:\n");
	printArray(arrB, col, row);

	int equal = arrayEqual(arrA, arrB, col, row);
	if(equal){
		printf("The 2 arrays are equal!!\n\n");
	} else {
		printf("The 2 arrays are not equal.\n\n");
	}

	return 0;
}