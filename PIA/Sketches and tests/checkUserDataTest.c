#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

char user[MAX], tmpuser[MAX];
int pin, tmppin; 
int countLines();
void menu();
void checkUserData();

int main(){
    menu();
    return 0;
}

void menu(){
    int op;
    extern char user[MAX], tmpuser[MAX];
    extern int pin, tmppin;
    pin = countLines() + 100;
    printf("Your PIN is: %d\n", pin);
    printf("Insert username: ");
    scanf("%s", user);
    FILE* userinfo = fopen("userinfo.txt", "a");
    fprintf(userinfo, " %s %d\n", user, pin);
    fclose(userinfo);
    printf("Would you like to see your info? 1 for Y, 2 for N: ");
    scanf("%d", &op);
    if(op==1)
        checkUserData();
    else
        exit(1);
}

int countLines(){
    FILE* countusers = fopen("userinfo.txt", "r");
    char c;
    int counter = 0;
    while((c=fgetc(countusers)) != EOF){
    	if(c=='\n')
      		counter++;
    }    
    return counter;
}

void checkUserData(){
    extern char user[MAX], tmpuser[MAX];
    extern int pin, tmppin;
    printf("Type your PIN to continue: ");
    scanf("%d", &pin);
    int line = pin - 100;
    int maxPIN = 99 + countLines();
    if((pin<100&&line<1)||(pin>maxPIN)){
        printf("Error: Invalid PIN. Please check your entry and try again.\n");
        checkUserData();
    }else{
        FILE* userinfo = fopen("userinfo.txt", "r");
        char c;
        int counter = 0;
        while((c=fgetc(userinfo)) != EOF){
        	if(c=='\n')
          		counter++;
          	if(counter==line)
          	    fscanf(userinfo, "%s %d", tmpuser, &tmppin);
        }    
        printf("Username of PIN <%d> is <%s>\n", tmppin, tmpuser);
        fclose(userinfo);
        menu();
    }
}
