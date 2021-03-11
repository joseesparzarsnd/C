#include <stdio.h>
#include <ctype.h>

char c;
int counter=0;

main(){	
	while((c=getchar())!=EOF){
		if(isdigit(c)){
			counter=1;
			continue;		
		}else if(counter!=0){
			putchar('X');
			counter=0;
		}
		putchar(c);
	}
}
