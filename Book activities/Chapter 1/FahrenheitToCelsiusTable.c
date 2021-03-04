//1.2 Variables and arithmetic expressions.

#include <stdio.h>

float fahr, celsius;

int lower=0;
int upper=300;
int step=20;

main(){
	fahr=lower;
	printf(" Fahrenheit to Celsius table.\n------------------------------\n");
	while(fahr<=upper){
		celsius=5*(fahr-32)/9;
		printf("\t%3.0f %6.1f\n",fahr,celsius);
		fahr=fahr+step;
	}
}
