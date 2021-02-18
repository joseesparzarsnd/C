/*1.2 Variables and arithmetic expressions.*/

#include <stdio.h>
/* print Fahrenheit-Celsius table for fahr=0, 20, ..., 300*/

main(){
	float fahr, celsius;
	int lower, upper, step;
	
	lower=0;       /*lower limit of temperature table*/
	upper=300;     /*upper limit*/
	step=20;       /*step size*/
	
	fahr=lower;
	printf("Fahrenheit to Celsius table.\n\n");
	while(fahr<=upper){
		celsius=(5.0/9.0)*(fahr-32.0);
		printf("\t%3.0f\t%6.2f\n",fahr,celsius);
		fahr=fahr+step;
	}	
}
