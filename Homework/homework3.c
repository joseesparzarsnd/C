#include <stdio.h>
#include <ctype.h>

char c;
int p=0, n=0, q=0;		//p=pharentesis, n=numbers, q=quotes.
					
main(){
	while((c=getchar())!=EOF){
		if(ispunct(c)){										
			if(c=='('||c=='['||c=='{'||c=='<'){				
				p++;										
			}else if(c==')'||c==']'||c=='}'||c=='>'){		
				p--;
			}else if(c=='\''||c=='\"'){
				q++;
			}else{
				continue;
			}
		}
		if(q==2){											
			q=0;											
		}
		if(isdigit(c)&&p==0&&q==0){							
			n++;											
			continue;										
		}else if(n!=0){										
			putchar('X');									
			n=0;
		}
		putchar(c);
		if(c=='\n'){
			n=0;
			q=0;
			p=0;
		}
	}
}
