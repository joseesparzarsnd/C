#include "test.h"
#include <stdio.h>

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
                printf("   X");
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

int revealCells(int** board, int** revealedCells, int size, int x, int y){
    if(board[x - 1][y]==MINE)
        return MINE;
    else if(revealedCells[x - 1][y]==TRUE)
        return FALSE;
    else{
        /*Found a mine-less cell*/
        if(board[x - 1][y]==FALSE){
            revealedCells[x - 1][y]=TRUE;
            int cellValue=1;
            int row, col;
            /*Searches the neighboring cells*/
            {   /*North*/
                row=x - 1;
                col=y;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*South*/
                row=x + 1;
                col=y;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*East*/
                row=x;
                col=y + 1;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*West*/
                row=x;
                col=y - 1;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*North-East*/
                row=x - 1;
                col=y + 1;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*North-West*/
                row=x - 1;
                col=y - 1;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*South-East*/
                row=x + 1;
                col=y + 1;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }{  /*South-West*/
                row=x + 1;
                col=y - 1;
                if((row - 1)>=FALSE&&(row - 1)<size&&col>=FALSE&&col<size)
                    cellValue+=revealCells(board, revealedCells, size, row, col);
            }
            return cellValue;
        }else{
            revealedCells[x - 1][y]=TRUE;
            return TRUE;
        }
    }
}