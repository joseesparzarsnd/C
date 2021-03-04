//1.5.3 Line counting.

#include <stdio.h>

int c;
int nl=0;

main(){
    while((c=getchar())!=EOF)
        if(c=='\n')
        ++nl;
    printf("%d\n",nl);
}
