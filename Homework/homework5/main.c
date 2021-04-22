//I took as references the book, rulgamer03, AbnerIO and the teacher's repositories.
//I also looked at this site for ideas on how to implement some stuff: https://www.geeksforgeeks.org/cpp-implementation-minesweeper-game/
//To make this program work, you can put all archives in the online gdb and it'll work. Just make sure the header has the exact same name it has here.
#include <stdio.h>
#include <stdlib.h>     
#include <ctype.h>      
#include <time.h>   
#include "main.h"

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
        menu();
    }
}

int playMinesweeper(){
    int play=TRUE; 
    int type;
    int entry;	//Checks if input is correct (TRUE) or wrong (FALSE);
    
    char s[MAXOP];
    
    while(play==TRUE){
        int mines = rand () % (MAX_MINES) + (MIN_MINES);    //Generates a random number of mines.
        printf("\n\nNumber of mines: %d\n", mines);         
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
        /*Puts the mines in random positions*/
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
        printf("\nType a coordenate (example: A2): \n");
        int letter=FALSE;	//Position in y-axis.
        int letterCounter=FALSE;
        int moves=FALSE;  
        int position;		//Position in x-axis.
        userBoard(board,SIZE,revealedCells); 
        while((type=getop(s))!=EOF){
            switch(toupper(type)){
                case NUMBER:
                    position=atof(s);
                    entry=TRUE;
                    break;
                case '\n':
                    if(entry==TRUE&&letterCounter==TRUE){
                        if(position - 1<SIZE&&position - 1 >=FALSE&&letter<SIZE&&letter>=FALSE){
                            int recentMove=revealCells(board, revealedCells, SIZE, position, letter);
                            /*If your recent move ended with you revealing a mine, you lose*/
                            if(recentMove==MINE){
                                realBoard(board, SIZE);
                                printf("\nThe mines (*) exploded. You lost!");
                                printf("\nWould you like to play again? Type 1 for YES, and 0 for NO: ");
                                scanf("%d",&play);
                                if(play!=TRUE)
                                    return FALSE;
                                else
                                    return playMinesweeper();
                                /*Set values to default (0)*/
                                letterCounter=FALSE;
                                letter=FALSE;
                                position=FALSE;
                                entry=FALSE;
                            }
                            /*If no recent move was registered (you already revealed this cell)*/
                            else if(recentMove==FALSE){
                                printf("\nError: That position has been already revealed!\n");
                                userBoard(board, SIZE, revealedCells);
                            }
                            /*If your recent move was valid*/
                            else{
                                moves+=recentMove;
                                /*If you reached the maximum amount of possible moves*/
                                if(moves>=SIZE*SIZE-mines){
                                    realBoard(board, SIZE);
                                    printf("\nYou won, congrats!");
                                    printf("\nWould you like to play again? Type 1 for YES, and 0 for NO: ");
                                    scanf("%d",&play);
                                    if(play!=TRUE)
                                        return FALSE;
                                    else
                                        return playMinesweeper();
                                    letterCounter=FALSE;
                                    letter=FALSE;
                                    position=FALSE;
                                    entry=FALSE;
                                }
                                else	/*Prints updated board*/
                                    userBoard(board, SIZE, revealedCells);
                            }
                        }else   /*The move wasn't valid, because it wasn't within range*/
                            printf("\nError: The coordenate isn't within range of the board!\n");
                    }else   /*Your entry wasn't valid*/
                        printf("\nError: Please check your entry! (If your game just started, please ignore this message)\n");
                    letterCounter=FALSE;
                    letter=FALSE;
                    position=FALSE;
                    entry=FALSE;
                    break;
                default:
                    if(type>=97&&type<=122){
                        letter=type-97;
                        letterCounter=TRUE;
                    }
                    else{
                        printf("\nError: Please check your entry and try again.\n");
                        entry=FALSE;
                    }
                    break;
            }
        }
    }
}
