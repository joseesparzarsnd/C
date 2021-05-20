#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX 20              //Max. characters for username.
#define MAXCMD 10           //Max. characters for commands.

int pin = 0, tmppin = 0, dep = 0, tmpdep = 0, lastfired = 0;       	//Global variables.
char user[MAX], tmpuser[MAX];                                       //Global variables.
    
void mainMenu();  
void userMenu();
void adminMenu();
void generatePin(); 
void clockIn();                 
void clockOut();                
void work();                    
void logIn();
void logOut();
int countRegisteredUsers();  
int isUserFired(int p);
int isUserRegistered(int pwd);
int calculateUserPerformance(float wh);
int updateUser(int p, int per);				
int printReport(char filename[MAX]);
int printUserReport(char filename[MAX]);
