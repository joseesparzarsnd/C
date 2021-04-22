#include <stdio.h>
#include <ctype.h>
#include "main.h"

char buf[BUFSIZE];
int bufp = 0;

int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int getop(char s[]){
    int i,c;
    char a;
    
    while((s[0]=c=getch())==' '||c=='\t')
        ;
    s[1]='\0';
    i=FALSE;
    if(!isdigit(c)&&c!='.'&&c!='-'){
        if (!isalpha(c))
            return c;
        if (isalpha(c))
            return tolower(c);
    }
    if(c=='-'){
        if(isdigit(c=getch()) || c == '.')
            s[++i]=c;
        else{
            if(c!=EOF)
                ungetch(c);
            return '-';
        }
    }
    if(isdigit(c)){
        while(isdigit(s[++i] =c =getch()))
            ;
    }

    if(c=='.'){
        while(isdigit(s[++i] = c=getch()))
            ;
    }
    s[i]='\0';
    if(c!=EOF)
        ungetch(c);
    return NUMBER;
}

/*This is the board that the user sees and interacts with*/
void userBoard(int** board, int size, int** openCells){ 
    int i, j;
    char c;
    int z=TRUE;
    printf("   ");
    for(i=FALSE;i<size;i++){
        c=i+65;
        printf ("   %c", c);
    }
    printf("\n");
    printf(" 1 ");
    for(i=FALSE;i<size;i++){
        for(j=FALSE;j<size;j++){
        if(board[i][j]!=MINE&&openCells[i][j]==TRUE){
            if (board[i][j]!=FALSE)
                printf(" %3d", board[i][j]);
            else
                printf("    ");  
        }else
          printf("   #");
    }
    printf("\n");
    z++;
    if(z<=size)
        printf("%2d ", z);
    }
    for(i=FALSE;i<(size*4+4);i++)
        printf("-"); 
    printf("\n");
}

/*This is the board where all the values are stored*/
void realBoard(int** board, int size) {
    int i, j;
    int z=TRUE;
    char c;
    printf("   ");
    for(i=FALSE;i<size;i++){
        c=i+65;
        printf ("   %c", c);
    }
    printf("\n");
    printf(" 1 ");
    for(i=FALSE;i<size;i++) {
        for(j=FALSE;j<size;j++) {
            if(board[i][j]!=MINE){
                if(board[i][j]!=FALSE)
                    printf(" %3d", board[i][j]);
                else
                    printf("    ");  
            }else
                printf("   *");
        }
        printf("\n");
        z++;
        if (z<=size)
        printf("%2d ", z);
    }
    for (i=FALSE;i<(size*4+4);i++)
        printf("-"); 
    printf("\n");
}

/*Searches the adyacent cells for mines and counts them*/
int countMines(int** board, int size, int a, int b){
    int i, j;
    int copyBoard[size][size];
    for(i=FALSE;i<size;i++){
        for(j=FALSE;j<size;j++)
            copyBoard[i][j]=board[i][j];
    }
    int x, y, z=FALSE;
    for(x=a- 1;x<3+a- 1;x++){
        for(y=b- 1;y<3+b- 1;y++){
            if(x>=FALSE&&x<size&&y>=FALSE&&y<size&&copyBoard[x][y]==MINE)
                z++;
        }
    }
    return z;
}

/*Recursively reveals cells*/
int revealCells(int** board, int** revealedCells, int size, int position, int letter){
    /*Finds an already-revealed cell*/
    if(revealedCells[position - 1][letter]==TRUE)  
        return FALSE;
    /*Finds a mine*/
    else if(board[position - 1][letter]==MINE)   
        return MINE;
    else{
        /*Finds a empty, unrevealed cell*/
        if(board[position - 1][letter]==FALSE){
            revealedCells[position - 1][letter]=TRUE;
            int cellValue=1;
            int row, col;
            /*Searches the neighboring cells, to either reveal other empty cells, or return the value of non-empty and mineless cells*/
            {   /*North*/
                row=position - 1;
                col=letter;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*South*/
                row=position + 1;
                col=letter;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*East*/
                row=position;
                col=letter + 1;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*West*/
                row=position;
                col=letter - 1;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*North-East*/
                row=position - 1;
                col=letter + 1;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*North-West*/
                row=position - 1;
                col=letter - 1;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*South-East*/
                row=position + 1;
                col=letter + 1;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*South-West*/
                row=position + 1;
                col=letter - 1;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }
            return cellValue;
        }else{
            /*Updates the board*/
            revealedCells[position - 1][letter]=TRUE;
            return TRUE;
        }
    }
}
