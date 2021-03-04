#include <stdio.h>

double nc;

main(){
    for(nc=0;getchar()!=EOF;++nc)
        ;
    printf("%.0f\n",nc);
}
