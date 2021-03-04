//1.4 Symbolic constants.

#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int fahr;

main(){
	printf(" Fahrenheit to Celsis table.\n\n");
	for(fahr=LOWER;fahr<=UPPER;fahr=fahr+STEP){
		printf("\t%3d %6.1f\n",fahr,(5.0/9.0)*(fahr-32));
	}
}
