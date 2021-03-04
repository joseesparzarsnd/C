#include <stdio.h>

int c;
int nl=0;  //Newlines.
int b=0;   //Blanks.
int t=0;   //Tabs.

main(){
    while((c=getchar())!=EOF){
        if(c==' '){
            ++b;
        }else if(c=='\n'){
            ++nl;
        }else if(c=='\t'){
            ++t;
        }
    }
    printf("Newlines: %d\nBlanks: %d\nTabs: %d\n",nl,b,t);
}
