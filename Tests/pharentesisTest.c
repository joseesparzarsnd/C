#include <stdio.h>
#include <ctype.h>

char c;
int i=0, j=0;

main(){
	while((c=getchar())!=EOF){
		if(isdigit(c)&&j==0){
			i++;
			continue;
		}else if(c=='('||c=='{'||c=='['||c=='<'){
			j++;
		}else if(c==')'||c=='}'||c==']'||c=='>'){
			j--;
		}else if(i!=0){
			putchar('X');
			i=0;
		}
		putchar(c);
	}
}
