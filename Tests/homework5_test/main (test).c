//Test version of minesweeper. It only works when you don't type A1 first. 
#include <stdio.h>
#include <stdlib.h>     
#include <ctype.h>      
#include <time.h>   
#include "test.h"

void menu();
int playMinesweeper();

int main(){
    menu();
    return FALSE;
}

void menu(){
    int option;
    printf("Welcome to Minesweeper. Choose an option: \n  1. Play.\n  2. Rules.\n");
    scanf("%d", &option);
    if(option==1)
        playMinesweeper();
    else{
        printf("\n___________________________________________________________________________________________________________________");
        printf("\nThe goal of the game is to reveal all of the cells without mines in them. ");
        printf("\nSome cells contain numbers in them. It tells you how many of the 8 cells that surround the cell have mines in them.\n");
        printf("\nThe board has a size of 10 x 10 cells, and everytime you play, the number of mines will change. ");
        printf("\nAlso, everytime you play the locations of the mines will change. Good luck!\n");
        printf("___________________________________________________________________________________________________________________\n");
        playMinesweeper();
    }
}

int playMinesweeper(){
    int mines = rand () % (MAX_MINES) + (MIN_MINES);        //Generates pseudo-random amount of mines.
    printf("\nNumber of mines: %d\n", mines);
    
    char s[MAXOP];
    
    int i, j;
    int** board;
    int** revealedCells; 
        
    board=(int**)malloc(sizeof(int*)*SIZE);
    /*Fills the board with zeros*/
    for(i=FALSE;i<SIZE;i++){
        board[i]=(int*)malloc(sizeof(int)*SIZE);
        for(j=FALSE;j<SIZE;j++)
            board[i][j]=FALSE;
        }
    revealedCells=(int**)malloc(sizeof(int*)*SIZE);
    for(i=FALSE;i<SIZE;i++){
        revealedCells[i]=(int*)malloc(sizeof(int)*SIZE);
        for (j=FALSE;j<SIZE;j++)
            revealedCells[i][j]=FALSE;
    }
    /*Puts mines in random positions*/
    srand(time(NULL));
    int z;
    for(z=FALSE;z<mines;z++){
        int randNum1=rand()%(SIZE);
        int randNum2=rand()%(SIZE);
        if (board[randNum1][randNum2]==FALSE)
            board[randNum1][randNum2]=MINE; //Adds mine.
        else
            z--;
    }
    /*Changes the zeros for the number of mines in each cell*/
    for(i=FALSE;i<SIZE;i++){
        for(j=FALSE;j<SIZE;j++){
            if(board[i][j]==FALSE)
                board[i][j]=countMines(board,SIZE,i,j);
        }
    }
    int moves, entry, letterCounter, x, y;
    int play=TRUE;
	char letter;
	
    while(play==TRUE){
        printf("\nType a coordenate (example: A2): \n");
        scanf("%c%d",&letter,&x);
        if(x<=SIZE&&x>=FALSE)
            entry=TRUE;
        switch(toupper(letter)){
            case 'A':
                y=0;
                letterCounter=TRUE;
                break;
            case 'B':
                y=1;
                letterCounter=TRUE;
                break;
            case 'C':
                y=2;
                letterCounter=TRUE;
                break;
            case 'D':
                y=3;
                letterCounter=TRUE;
                break;
            case 'E':
                y=4;
                letterCounter=TRUE;
                break;
            case 'F':
                y=5;
                letterCounter=TRUE;
                break;
            case 'G':
                y=6;
                letterCounter=TRUE;
                break;
            case 'H':
                y=7;
                letterCounter=TRUE;
                break;
            case 'I':
                y=8;
                letterCounter=TRUE;
                break;
            case 'J':
                y=9;
                letterCounter=TRUE;
                break;
        }
        if(entry==TRUE&&letterCounter==TRUE){
            if(((x - 1)<SIZE)&&((x - 1)>=FALSE)&&(y<SIZE)&&(y>=FALSE)){
                int recentMove = revealCells(board, revealedCells, SIZE, x, y);
                if(recentMove==MINE){           //Recent move revealed a mine.
                    realBoard(board, SIZE);     //Shows the real board.
                    printf("\nYou lost!");
                    printf("\nWould you like to play again? 1: Yes, 0: NO. ");
                    scanf("%d",&play);
                    if(play!=TRUE)
                        return FALSE;
                    else
                        return playMinesweeper();
                }if(recentMove==FALSE){         //Recent move tries to reveal an already revealed cell.
                    printf("\nError: Position already revealed!\n");
                    userBoard(board, SIZE, revealedCells);
                }else{
                    moves+=recentMove;          //Adds the recent move to the total of moves.
                    if(moves>=SIZE*SIZE-mines){
                        printf("\nYou won!");
                        printf("\nWould you like to play again? 1: Yes, 0: NO. ");
                        scanf("%d",&play);
                        if(play!=TRUE)
                            return FALSE;
                        else
                            return playMinesweeper();
                    }else
                        userBoard(board, SIZE, revealedCells);
                }
            }
        }
    }
}