#include <stdio.h>

#define BLANK ' '

int c;
int d=BLANK;

main(){
    while((c=getchar())!=EOF){
        if(c==' '){
            if(d!=' '){
                putchar(c);
            }
        }else{
            putchar(c);
        }
        d=c;
    }
}
