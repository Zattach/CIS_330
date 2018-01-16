#include <stdio.h>

int g_int = 21;
int g_un;

int func(){
	int local_func;
	int *ptr = malloc(sizeof(int));
	//...
	free(ptr);
}

int main(int argc, char *argv[]){
	int local_main;
	func();
	return 0;
}

/*

Memory:

|Other|             argv, argc              Higher Level Memory |
																|
|Stack| main()      local_main                                  V
		func()      local_func, ptr(mem)
----------------|---------------    ^   
				V                   |
				^                   |   
________________|_______________    V
|Heap|                          |int|

|Uninitialized|     g_un
|Initialized|       g_int(21)
|Text sequence|     a.out                   Lower Level Memory


Multi-dimensional Array: Rows vs. Cols

int array[3][5];

|0,0|0,1|0,2|0,3|0,4|
|1,0|1,1|1,2|1,3|1,4|
|2,0|2,1|2,2|2,3|2,4|

Multi-dimensional Array: Memory Allocation

int **array;
void init(int ***v, int rows, int cols)
	*v = (int **) malloc(rows * sizeof(int *));
	for(i = 0; i < rows; i++){
		(*v)[i] = (int *) malloc(cols * sizeof(int));
	}
	...
array = (int **) malloc(3 * sizeof(int *))
for(i = 0; i < 3; i++){
	array[i] = (int *) malloc(5 * sizeof(int))
}
init(&array,3,5)