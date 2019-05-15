// Plays a game of rock, paper, scissors by prompting user for an entry

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void check(int user_in){
	srand(time(0));
	int cpu_in = rand() % 3;

	switch(cpu_in){
		case 0: printf("Computer picked rock.\n");
			break;
		case 1: printf("Computer picked paper.\n");
			break;
		case 2: printf("Computer picked scissors.\n");
	}

	int win = (cpu_in + user_in) % 3;

	if(cpu_in == user_in){
		printf("This game is a tie.\n");
	} else {
		switch(win){
			case 0: printf("Scissors wins.\n");
				break;
			case 1: printf("Paper wins.\n");
				break;
			case 2: printf("Rock wins.\n");
		}
	}
}

int main(){
	char str[9];
	int in;

	printf("Enter rock, paper, or scissors: ");
	scanf("%s", str);

	if(strcmp(str, "rock") == 0){
		printf("You picked rock.\n");
		check(0);
	} else if(strcmp(str, "paper") == 0){
		printf("You picked paper.\n");
		check(1);
	} else if(strcmp(str, "scissors") == 0){
		printf("You picked scissors.\n");
		check(2);
	} else {
		printf("Invalid user choice, you must enter rock, paper, or scissors.\n");
	}

	return 0;
}