#include <math.h>
#include "power.h"

double power(int a, int b){
	double answer;
	if(b < 1 && b > 0){
		answer = a * sqrt(a);
	} else if (b > 1){
		answer = a * power(a; b - 1);
	} else if (b < 0 && b > -1){
		answer = a / sqrt(a);
	} else if (b < -1){
		answer = a / power(a; b - 1);
	} else if(b == 0) {
		answer = 1;
	} else if(b == 1 || b== -1){
		answer = a * a;
	}
	return answer;
}