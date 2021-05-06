#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 20              //Max. characters for username.
#define MAXCMD 10           //Max. characters for commands.

int pin = 0, tmppin = 0;            //Global variables.
    
int menu();                     //Prints menu.
int countRegisteredUsers();     //Counts the amount of registered users in "users.txt" file.
void generatePin();             //Creates a PIN based on previous function.
void clockIn();                 //Clocks you in for work.
void clockOut();                //Clocks you out of work.
void work();                    //Now you have to work!
int printWhReport();            //Prints the report of total hours worked by clocked-in users.
int printAReport();             //Prints the attendance report of each clocked-in user.
int printLogs();                //Prints when a user clocked in and out based on system time.
int printUserInfo();            //Prints user data (username and PIN).
