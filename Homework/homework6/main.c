//To use the program, just compile all the files in onlineGDB. Just make sure the header file has the right name.
//I looked at the teacher's and rulgamer03's repositories to make my program.
//This site also helped me: https://personales.unican.es/corcuerp/progcomp/slides/arbol.pdf
#include <stdio.h>
#include <stdlib.h>     //Memory allocation stuff.
#include <string.h>     //String comparing command.
#include "tree.h"

char line[MAX], username[MAX], password[MAX];

/*Main function*/
int main(){
  	extern char line[];
  	node* n = NULL;
  	node* tree = NULL; 
  	int i, j, l = 0;
  	char* u;
  	char* p;
  	int check = 0;		    //Checks if a user has been deleted.
  	int spaceCounter = 0;	//Counts blank spaces.
  	
  	printf("Welcome. Available commands: \n");
  	printf("\tadd (user password) - adds user to database.\n");
  	printf("\tdel (user password) - deletes user from database.\n");
  	printf("\tview - prints registered users in alphabetical order.\n");
  	printf("\tseeall - prints registered users and their passwords.\n");
  	printf("\texit - exits the program.\n");
  	printf("\nMake sure your input follows the correct format before pressing 'enter'.\n\n");
  	while((l=getLine())==0){
      	spaceCounter = 0;
	    for(j=0; j<MAX; j++){
	        if(line[j]==' '||line[j]=='\t')
	            spaceCounter++;
	    }
	    /*If line contains the 'del' command*/
	    //The line should have at least 7 characters, two being blank spaces, and it should look a bit like 'del a b'.
	    if(strstr(line, "del")!=NULL && strlen(line)>=7 && spaceCounter==2){
	      	getUserInfo(line, password, username);
	      	u = (char*)malloc(sizeof(int*) * strlen(username));
	      	p = (char*)malloc(sizeof(int*) * strlen(password));
	      	/*Copies user and password into another array for temporary use*/
	      	for (i=0; i<strlen(username); i++)
	          	u[i]=username[i];
	      	for (i=0; i<strlen(password); i++)
	         	p[i]=password[i];
	        /**/
	      	erase(tree, u, p, &check);
	      	if(check==0){   //It'll return with a value of 1 if it deleted the user.
	        	printf("Error: User wasn't deleted. Please check your entry and try again.\n\n");
	      	}
	      	check = spaceCounter = 0;	//Resets values to default.
	    }/*If line contains the 'add' command*/
	    //The line should look like 'add a b'.
		else if(strstr(line, "add")!=NULL && strlen(line)>=7 && spaceCounter==2){ 
	      	getUserInfo(line, password, username);
	      	u = (char*)malloc(sizeof(int*) * strlen(username));
	      	p = (char*)malloc(sizeof(int*) * strlen(password));
	      	for(i=0; i<strlen(username); i++)
	          	u[i]=username[i];
	      	for(i=0; i<strlen(password);i++)
	          	p[i]=password[i];
	      	if(strlen(password)>0 && strlen(username)>0){
	      		n = insert(u, p, tree, 0);	//Inserts info into the tree.
		  		if(tree==NULL)
		    		tree = n; 				//If tree is empty, this will be the root.
		   	spaceCounter = 0;
	    	}else if(strlen(password)<=0||strlen(username)<=0)
	        	printf("Error: Please check your entry and try again.\n\n");
	    }/*If line = view, it should only have 4 characters*/	      
	    else if(strstr(line, "view")!=NULL && strlen(line)==4){
	      	alpha(tree);
	      	printf("\n\n");
	      	spaceCounter = 0;
	    }else if(strstr(line, "exit")!=NULL && strlen(line)==4)
	    	return 0;
	    else if(strstr(line, "seeall")!=NULL && strlen(line)==6){
	    	seeAll(tree);
	    	printf("\n");
	    	spaceCounter = 0;
	    }else
	        printf("Error: Please check your entry and try again.\n\n");
	    spaceCounter = 0;      
  	}
  	return 0;
}

/*Deletes user info*/
void erase(node* pos, char* u, char* p, int* n){
    if(pos!=NULL){        
        erase(pos->leftChild, u, p, n);
        erase(pos->rightChild, u, p, n);
        if(strcmp(pos->username, u)==0 && strcmp(pos->password, p)==0){	//Checks that inputted user and password match the ones in the database.
            pos->password=NULL;
            printf("User %s deleted\n\n", u);
            *n=1;	//Means that user has been deleted.
        }  
    }
}

/*Inserts a node*/
node* insert(char* u, char* p, node* pos, int d){
  	node* temp;
  	if(pos==NULL){
	    pos = (node*)malloc(sizeof(node));
	    pos->username = u;
	    pos->password = p;
	    pos->depth = d;
	    printf("Succesfully registered user %s, with password %s\n\n", u, p);
	}else{
		if(strcmp(pos->username, u)==0){
      		if(pos->password!=NULL)
      			printf("Error: User already registered!\n\n");
     	 	else{
          		pos->password = p;
          		printf("Succesfully registered user %s, with password %s\n\n", u, p);
      		}
    	}else if(strcmp(pos->username, u)>0){
      		temp = insert(u, p, pos->leftChild, d + 1);
      		if(pos->leftChild==NULL)
				pos->leftChild = temp;
    	}else{
      		temp = insert(u, p, pos->rightChild, d + 1); 
      		if(pos->rightChild==NULL) 
				pos->rightChild = temp;
    	}
  	}
  	return pos;
}

/*Orders tree alphabetically*/
void alpha(node* pos){
  	if(pos!=NULL){
    	alpha(pos->leftChild);
    	if(pos->password!=NULL)
    		printf("%s ", pos->username);
    	alpha(pos->rightChild);
 	}
}

/*Orders tree alphabetically, and prints all user info*/
void seeAll(node* pos){
  	if(pos!=NULL){
    	seeAll(pos->leftChild);
    	if(pos->password!=NULL)
    		printf("%s %s\n", pos->username, pos->password);
    	seeAll(pos->rightChild);
 	}
}

/*Stores the input line*/
int getLine(){
	extern char line[];
  	int c, i = 0;

  	for (; i<MAX-1 && (c = getchar())!=EOF && c!='\n';)
        line[i++]=c;
	line[i]='\0';
  	return c == EOF;
}

/*Gets username and password based on getLine function*/
void getUserInfo(char l[MAX],char p[MAX],char u[MAX]){
    int a = 4, b = 0, c=0;
    while(l[a]!=' '&&l[a]!='\t'){	//While there's no blankspaces it'll store the username.
        u[b]=l[a];
        b++;
        a++;
    }
    u[b]='\0';
    int lengthUsername = strlen(u);
    a++;
    while(l[a]!=' '&&l[a]!='\t'&&l[a]!='\0'){	//While there's no blankspace or end of string it'll store the password.
       p[c]=l[a];
       c++;
       a++;
    }
    p[c]='\0';
    int lengthPassword = strlen(p);
}