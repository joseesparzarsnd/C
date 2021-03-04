#include <stdio.h>
#include <math.h>

#define A 45					//Test value.

main(){
	binaryConverter(A);			//Calls the function.
}

int binaryConverter(int a){	

    int i=0;
	int x; 						
    int ns[12]={0}; 			//Available number slots to put numbers in.
    
    while(a>0){					//This will obtain the corresponding binary numbers... 								         
		ns[i]= a%2;				//...through residual division, but this numbers...	
		a/=2; 					//...aren't the final binary string, since they're...
		i++; 					//...in the wrong order.
    }
    for(x=11;x>=0;x--){			//This will "flip" the numbers obtained by the previous loop...
    	printf("%d",ns[x]);		//...so we obtain the right binary string, and then...
    }							//...it'll print it.
    printf("\n");
}
