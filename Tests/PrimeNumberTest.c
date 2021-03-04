#include <stdio.h>
#include <math.h>

#define K 21					//Test value.

int primeNumbers(int k);

main(){
	primeNumbers(K);			//Calls the function.
	return 0;
	
}

int primeNumbers (int k){		
	
	int i, prime;
  	int num=2;				//Starts with 2 because it's the first prime number.
 	int counter=1;				//Counts the number of prime numbers found. 

  	while(counter<=k){					
	  	
    	prime=1;				//Default value if a number is prime.
 
    	for(i=2;i<=sqrt(num);i++){	
    		if(num%i==0){			
        		prime=0; 		//States that the number is not a prime number.
    			break;			 
      		}
   		}
    	if(prime==1){ 				//States that a prime number was found.
    		counter++;			//Adds 1 to the counter.
    		printf("%d\n",num);		//Prints the value of the number.
   		}
    	num++;					//Continues with the next number.
  	}
}
