#include <stdio.h>
#include <math.h>

#define A 45				//Test value.

main(){
	binaryConverter(A);		//Calls the function.
}

int binaryConverter(int a){	

    int i=0;
	int x; 						
    int ns[12]={0}; 			//Available number slots to put numbers in.
    
    while(a>0){				//To obtain the corresponding binary numbers (in wrong order). 								         
		ns[i]= a%2;					
		a/=2; 					
		i++; 					
    }
    for(x=11;x>=0;x--){			//Flips the binary string so it can be in the right order.
    	printf("%d",ns[x]);		//Prints the binary string.
    }							
    printf("\n");			//Prints a newline after the string.
}
