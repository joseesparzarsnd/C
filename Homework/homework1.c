#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Note: It can't get rid of the things inside the scripts.

#define A '<'
#define B '>'
#define O 'o'
#define H 'h'

char ch;
int a=0;
int o=0;   //For the <strong> stuff.
int h=0;   //For the <h1> stuff.

main(){
    while((ch=getchar())!=EOF){
        if(ch==A){               //To ignore the '<'
            a=1;
            h=0;
            o=0;
            continue;
        }else if(ch==O&&a!=0){   //For the <strong> stuff.
            o=1;
            continue;
        }else if(ch==H&&a!=0){   //For the <h1> stuff.
            h=1;
            continue;
        }else if(ch==B&&a!=0){   //To ignore the '>' and put characters afterwards.
            a=0;
            continue;
        }else if(ch==' '&&o==1&&a==0){   //Will replace the blank spaces for '_'
            printf("_");
            ch=getchar();
        }else if(ch==' '&&h==1&&a==0){
            printf("_");
            ch=getchar();
        }else if(isalnum(ch)&&a!=0){     //To ignore numbers and letters if they're inside the '<>'.
            continue;
        }else if(ispunct(ch)&&a!=0){     //To ignore any punctuation characters inside the '<>'.
            continue;
        }
        putchar(ch);
    }
}
