#define MIN_MINES 10    //Minimum mines in 10x10 board.
#define MAX_MINES 40    //Maximum mines in 10x10 board.
#define MAXOP 100       //Maximum size of operand/operator.   
#define TRUE 1          
#define FALSE 0             
#define MINE -1         //Value of a mine.
#define SIZE 10         //Size of board.
#define NUMBER '0'
#define BUFSIZE 100

int getop(char[]);
int getch(void);
void ungetch(int);
void realBoard(int** , int );
void userBoard(int** , int , int** );
int countMines(int** , int , int , int );
int revealCells(int** , int** , int , int , int );
