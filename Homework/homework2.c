//I used the teacher's and rulgamer03's repositories as references.

#include <stdio.h>
#include <math.h>

#define K 18 					//Constant.

int primeNumbers(int k);		//Function to get the first 'k' prime numbers.
int binaryConverter(int a);		//Function to convert them to binary strings.

main(){
	primeNumbers(K);			//Uses the value of 'K' to call the function. 
	return 0;
}

int primeNumbers(int k){		
	
	int i, prime;
  	int num=2;					//Starts with 2 because it's the first prime number..
 	int counter=1;				//Counts the number of prime numbers found. 

  	while(counter<=k){					
	  	
    	prime=1;					//Default value if a number is prime..
 
    	for(i=2;i<=sqrt(num);i++){	//i=2 since it's the first prime number.
    		if(num%i==0){			
        		prime=0; 			//States that the number is not a prime number.
    			break;			 
      		}
   		}
    	if(prime==1){ 				//States that a prime number was found.
    		binaryConverter(num);	//Uses the value of 'num' to call the function.
    		counter++;				//Adds 1 to the counter.
   		}
    	num++;					//Continues with the next number.
  	}
}

int binaryConverter(int a){	

    int i=0;
	int x; 						
    int ns[10]={0}; 			//Total number of spaces of the binary strings.
    
    while(a>0){					//This will obtain the corresponding binary numbers... 								         
		ns[i]= a%2;				//...through residual division, but this numbers...	
		a/=2; 					//...aren't the final binary string, since they're...
		i++; 					//...in the wrong order.
    }
    for(x=9;x>=0;x--){			//This will "flip" the numbers obtained by the previous loop....
    	printf("%d",ns[x]);		//...so we obtain the right binary string, and then...
    }							//...it'll print it.
    printf("\n");				//Prints a newline after printing the binary string of a number.
}


