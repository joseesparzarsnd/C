//1.3 The "for" statement.

#include <stdio.h>

int fahr;

main(){
	printf(" Fahrenheit to Celsius table.\n\n");
	for(fahr=300;fahr>=0;fahr=fahr-20){
		printf("\t%3d %6.1f\n",fahr,(5.0/9.0)*(fahr-32));
	}
}
