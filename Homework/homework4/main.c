//I took as references the book, rulgamer03 and AbnerIO's repositories.
//To make this program work, you can put all archives in the online gdb and it'll work.

#include <stdio.h>
#include <stdlib.h>		/*for atof()*/
#include <ctype.h>
#include <math.h>		/*for division with remainder*/
#include "calc.h"

#define MAXOP 100		/*max size of operand or operator*/
#define TRUE 1
#define FALSE 0

/*reverse Polish calculator*/
int main(){
	int type,rewritable,forced,number,value,i;
	int l=27;
	double op2;
	double alpha[26]={};
	char s[MAXOP];
	char ans;
	
	printf("This calculator uses Reverse-Polish Notation, so instead of typing something like '3+4', you'll need to type '3 4 +'.\n");
	printf("\t-To create a variable, you should follow this example format: 'a = 2'\n");
	printf("\t-If you want to create a variable with a fixed value, you should use ':=' instead of '='\n");
	printf("\t-To rewrite a variable, just follow this example 'a = new value'.\n\n");
	while((type=getop(s))!=EOF){
		switch(tolower(type)){
			case NUMBER:
				push(atof(s));
				if(rewritable==TRUE){
					number=atof(s);
					value=TRUE;
				}
				break;
			case 'a':
				l=0;
            			push(alpha[l]);
            			break;
        		case 'b':
        			l=1;
            			push(alpha[l]);
				break;
				case 'c':
				l=2;
				push(alpha[l]);
				break;
        		case 'd':
        			l=3;
            			push(alpha[l]);
        	    		break;
      	  		case 'e':
      	  			l=4;
            			push(alpha[l]);
     	       			break;
     	   		case 'f':
     	   			l=5;
				push(alpha[l]);
				break;
    	    		case 'g':
				l=6;
				push(alpha[l]);
				break;
      	  		case 'h':
      	  			l=7;
				push(alpha[l]);
				break;
      	  		case 'i':
      	  			l=8;
            			push(alpha[l]);
          	  		break;
        		case 'j':
        			l=9;
				push(alpha[l]);
				break;
        		case 'k':
        			l=10;
            			push(alpha[l]);
            			break;
        		case 'l':
        			l=11;
            			push(alpha[l]);
            			break;
        		case 'm':
        			l=12;
				push(alpha[l]);
				break;
        		case 'n':
        			l=13;
				push(alpha[l]);
				break;
       			case 'o':
       				l=14;
				push(alpha[l]);
				break;
        		case 'p':
        			l=15;
				push(alpha[l]);
				break;
        		case 'q':
        			l=16;
				push(alpha[l]);
				break;
			case 'r':
				l=17;
				push(alpha[l]);
				break;
			case 's':
				l=18;
				push(alpha[l]);
				break;
			case 't':
				l=19;
				push(alpha[l]);
				break;
			case 'u':
				l=20;
				push(alpha[l]);
				break;
			case 'v':
				l=21;
				push(alpha[l]);
				break;
			case 'w':
				l=22;
				push(alpha[l]);
				break;
			case 'x':
				l=23;
				push(alpha[l]);
				break;
			case 'y':
				l=24;
				push(alpha[l]);
				break;
			case 'z':
				l=25;
				push(alpha[l]);
				break;
			case '+':
				push(pop()+pop());
				break;
			case '*':
				push(pop()*pop());
				break;
			case '-':
				op2=pop();
				push(pop()-op2);
				break;
			case '/':
				op2=pop();
				if(op2!=FALSE)
					push(pop()/op2);
				else
					printf("Error: Zero divisor.\n");
				break;
			case '%':
				op2=pop();
				if(op2!=FALSE)
					push(fmod(pop(),op2));
				else
					printf("Error: Zero divisor.\n");
				break;
			case '\n':
				if (l!=27&&rewritable==TRUE&&value==TRUE){
                			for(i=FALSE;i<26;i++){
                    				if (l==i){
                    					if(forced==TRUE&&rewritable==TRUE)
                    	        				rewritable=FALSE;
                    	    				if(alpha[i]!=FALSE&&forced==TRUE)
								printf("You can't change this value!\n");
							if (alpha[i]!=FALSE&&rewritable==TRUE){
								printf("Do you want to change the value of this variable? Type '1' for YES, and any other key for NO: ");
								if ((ans=getchar())!='1'){
									pop();
									printf("Operation cancelled.\n");
								}else{
									pop();
									printf("New value: %d\n",number);
									alpha[i]=number;
								}
								forced=FALSE;
							}else{
								alpha[i]=number;
								forced=FALSE;
							}
                   				}
                			}
            			}else{
            				if(ans=='1'){
            					ans=NUMBER;
            					continue;
					}
                			printf("\t%.4g\n", pop());
            			}	
				l=27;
				rewritable=FALSE;
				value=FALSE;
				number=FALSE;
				break;
			case '=':
				rewritable=TRUE;		
				break;
			case ':':
				forced=TRUE;
				break;				
			default:
				printf("Error: Unknown command %s\n",s);
				break;
		}
	}
	return FALSE;
}
