#include "header.h"

int main(){
    mainMenu();
    return 0;
}

/*Sends user into main menu*/
void mainMenu(){
    char cmd[MAXCMD];
    printf("\nAvailable commands:\n\treg - registers user into system.\n\tcin - clocks you in for work.");
    printf("\n\tlogin - to log into the system.\n\texit - exits the program.");
    printf("\nType your command: ");
    scanf("%s", cmd);
    if(strstr(cmd, "reg"))          generatePin();
    else if(strstr(cmd, "cin"))     clockIn();
    else if(strstr(cmd, "login"))   logIn();
    else if(strstr(cmd, "exit"))    exit(0);
    else{
        printf("Error: Please check your entry and try again.\n");
        mainMenu();
    }
}

/*Menu for employees that work in departements 1-4, or for fired users that worked in departement 5*/
void userMenu(){
	char file[MAX], cmd[MAX];
	extern char tmpuser[];
	printf("Welcome %s. This are the available commands: ", tmpuser);
	printf("\n\t1. bal - prints a report of total worked hours per week by each user.");
	printf("\n\t2. twh - prints a report of the days attended per week by each employee.");
	printf("\n\t6. logout - to log out of the system.");
	printf("\n\t7. exit - exits program.\nOption: ");
	scanf("%s", cmd);
    if(strstr(cmd, "twh")) 			printUserReport(strcpy(file, "workedhours.txt"));
    else if(strstr(cmd, "bal")) 	printUserReport(strcpy(file, "balance.txt"));
    else if(strstr(cmd, "logout")) 	logOut();
    else if(strstr(cmd, "exit"))    exit(0);
    else{
        printf("Error: Please check your entry and try again.\n");
        userMenu();
    }
}

/*This menu will show for people that work in the administration departement*/
void adminMenu(){
	char file[MAX], cmd[MAX];
	extern int tmppin, lastfired;
	extern char tmpuser[];
	if(tmppin!=lastfired){
		printf("Welcome %s. This are the available commands: ", tmpuser);
		printf("\n\twr - prints a report of total worked hours per week by each user.");
		printf("\n\tar - prints a report of the days attended per week by each employee.");
		printf("\n\tlogs - prints logs.");
		printf("\n\tsee - to see every single user that has been registered.");
		printf("\n\tperf - prints a report about how well an individual performed in a month.");
		printf("\n\tlogout - to log out of the system.");
		printf("\n\texit - exits program.\nOption: ");
		scanf("%s", cmd);
	    if(strstr(cmd, "wr")) 			printReport(strcpy(file, "workedhours.txt"));
	    else if(strstr(cmd, "ar")) 		printReport(strcpy(file, "attendance.txt"));
	    else if(strstr(cmd, "logs"))	printReport(strcpy(file, "logs.txt"));
	    else if(strstr(cmd, "see"))		printReport(strcpy(file, "users.txt"));
	    else if(strstr(cmd, "perf"))	printReport(strcpy(file, "userperformance.txt"));
	    else if(strstr(cmd, "logout")) 	logOut();
	    else if(strstr(cmd, "exit"))    exit(0);
	    else{
	        printf("Error: Please check your entry and try again.\n");
	        adminMenu();
	    }
	}else{
		printf("Since you were fired, you can't access the admin menu!\n");
		userMenu();
	}
}

/*Counts the amount of users in the system*/
int countRegisteredUsers(){
    FILE* countusers = fopen("users.txt", "r");
    char c;
    int counter = 0;
    while((c=fgetc(countusers)) != EOF){
    	if(c=='\n')
      		counter++;
    }    
    return counter;
}

/*Generates an unique PIN based on how many users are registered in the system*/
void generatePin(){
    extern char user[];
    extern int pin, dep;
    pin = 100 + countRegisteredUsers();
    printf("\nYour PIN is: %d\n", pin);
    printf("Insert your username: ");
    scanf("%s", user);
    printf("Choose one of the following departements to work at: ");
    printf("\n\t1. Sales.\n\t2. System maintenance.\n\t3. Human resources.\n\t4. Contability.\n\t5. Administration.\nDepartement: ");
    scanf("%d", &dep);
    switch(dep){
    	case 1:
    		printf("Succesfully registered user <%s> with PIN <%d> in <Sales> departement.\n", user, pin);
    		break;
    	case 2:
    		printf("Succesfully registered user <%s> with PIN <%d> in <System maintenance> departement.\n", user, pin);
    		break;
    	case 3:
    		printf("Succesfully registered user <%s> with PIN <%d> in <Human resources> departement.\n", user, pin);
    		break;
    	case 4:
    		printf("Succesfully registered user <%s> with PIN <%d> in <Contability> departement.\n", user, pin);
    		break;
    	case 5:
    		printf("Succesfully registered user <%s> with PIN <%d> in <Administration> departement.\n", user, pin);
    		break;
    	default:
			printf("\nError: Departement not found. Please check your entry and try again.");
			mainMenu();
			break;
	}
    FILE *userinfo = fopen("users.txt", "a");
    fprintf(userinfo, " %s %d 1 %d\n", user, pin, dep);
    fclose(userinfo);
    mainMenu();
}

/*To clock in for work*/
void clockIn(){
    extern int pin;
    printf("\nType your PIN to clock in for work: ");
    scanf("%d", &pin);
    if(isUserFired(pin)==1){
    	printf("You're now working!\n\n");
        time_t mytime = time(NULL);
        char * time_str = ctime(&mytime);
        time_str[strlen(time_str)-1] = '\0';
        printf("Clocked in at: %s\n", time_str);
        FILE* logs = fopen("logs.txt", "a");
        fprintf(logs, "%d: Clocked in at %s\n", pin, time_str);
        fclose(logs);
        work();
	}else if(isUserFired(pin)==0){
        printf("Error: That user was fired!\n");
        mainMenu();
    }else{
    	printf("Error: Please check your entry and try again.\n");
    	mainMenu();
	}
}

/*To clock out of work*/
void clockOut(){
	extern char tmpuser[];
    extern int pin, tmppin;
    printf("\nType your PIN to clock out of work: ");
    scanf("%d", &pin);
    if(pin==tmppin){
        printf("You're not working anymore\n\n");
        FILE* logs = fopen("logs.txt", "a");
        time_t mytime = time(NULL);
        char * time_str = ctime(&mytime);
        time_str[strlen(time_str)-1] = '\0';
        printf("Clocked out at: %s\n", time_str);
        fprintf(logs, "%d: Clocked out at %s\n", pin, time_str);
        fclose(logs);
    }else{
        printf("Error: Please check your entry and type again.\n");
        pin = tmppin;
        clockOut();
    }
    mainMenu();
}

/*Special function to simulate an employee working*/
void work(){
	extern char tmpuser[];
    extern int tmppin, tmpdep;
    int week = 1, days = 0, totaldays = 0, i;
    float hrs[6], totalhrs, totalmonthhrs, totalextrahrs = 0, pay = 0.0;
    printf("Starting your month of work...\n");
    while(week<=4){
    	totalhrs = 0, days = 0;
    	printf("\nYou can work up to 6 days per week (from monday to saturday). ");
    	printf("Type the hours you will work per day (1-16 hrs max). \nNote: Every number outside of that range will be taken as a zero.\n");
    	//To scan and store hours worked per day
		for(i=1; i<=6; i++){
			printf("Day %d: ", i);
    		scanf("%f", &hrs[i]);
    		if(hrs[i]<0.0 || hrs[i]>16.0) 	hrs[i] = 0.0;
    		if(hrs[i]>0.0 && hrs[i] <=16.0)	days++;
    		totalhrs += hrs[i];
		}
		totalmonthhrs += totalhrs;
		totaldays += days;
		if(totalmonthhrs>192)	totalextrahrs = totalmonthhrs - 192;
		printf("Perfect! Now wait until your shifts end (total seconds to wait: %.2f).\n", totalhrs/8);
		//Delays the program to simulate that an user is "working".
		time_t start, end;
	    time(&start);
	    do time(&end); while(difftime(end, start) <= (totalhrs/8));
		week++;
	}
	//These ifs will calculate the amount of money an employee makes on a week based on the hours they worked.
	if(tmpdep==1){ 		
		if(totalextrahrs>0) pay = (192 * 100.9) + (1.2 * totalextrahrs * 100.9);
		else 				pay = totalmonthhrs * 100.9;
	}else if(tmpdep==2){	
		if(totalextrahrs>0)	pay = (192 * 129.8) + (1.2 * totalextrahrs * 129.8);
		else				pay = totalmonthhrs * 129.8;
	}else if(tmpdep==3){
		if(totalextrahrs>0)	pay = (192 * 148.7) + (1.2 * totalextrahrs * 148.7);
		else 				pay = totalmonthhrs * 148.7;
	}else if(tmpdep==4){
		if(totalextrahrs>0)	pay = (192 * 156.2) + (1.2 * totalextrahrs * 156.2);
		else				pay = totalmonthhrs * 156.2;
	}else if(tmpdep==5){
		if(totalextrahrs>0)	pay = (192 * 193.4) + (1.2 * totalextrahrs * 193.4);
		else 				pay = totalmonthhrs * 193.4;
	}
	//Writes in attendance report file.
    FILE* ar = fopen("attendance.txt", "a");	
    fprintf(ar, "%s %d - Attended %d out of 24 days this month.\n", tmpuser, tmppin, totaldays);
    fclose(ar);       
    //Writes on worked hours report.
    FILE* wh = fopen("workedhours.txt", "a");	
    fprintf(wh, " %s %d: Worked %.2f hours this month.\n", tmpuser, tmppin, totalmonthhrs);
    fclose(wh);
    //Writes on balance report.
    FILE* bal = fopen("balance.txt", "a");
    fprintf(bal, " %s %d: Made $%.2f this month.\n", tmpuser, tmppin, pay);
    fclose(bal);
    int performance = calculateUserPerformance(totalmonthhrs);
    totalmonthhrs = totalextrahrs = totaldays = pay = 0;
    updateUser(pin, performance);
}

/*To log into the system*/
void logIn(){
    extern int pin, tmpdep;
    int op;
    printf("\nType your PIN to log in: ");
    scanf("%d", &pin);
    if(isUserRegistered(pin)==1){
    	printf("Succesfully logged in.\n");
    	if(tmpdep<5)
    		userMenu();
    	else{
    		printf("Since you work at the administration departement, you can choose to go to the admin menu by pressing 1. ");
    		printf("\nOtherwise, you'll be redirected to the normal menu. \nOption: ");
    		scanf("%d", &op);
    		if(op!=1)	userMenu();
    		else 		adminMenu();
		}
	}else{
        printf("Error: Please check your entry and type again.\n");
        mainMenu();	
	}
}

/*To log out of the system*/
void logOut(){
	extern char tmpuser[];
    extern int pin, tmppin;
    printf("\nType your PIN to log out: ");
    scanf("%d", &pin);
    if(pin==tmppin)
        printf("Succesfully logged out.\n\n");
    else{
        printf("Error: Please check your entry and type again.\n");
        pin = tmppin;
        logOut();
    }
    mainMenu();
}

/*Checks if user is currently employed*/
int isUserFired(int p){
	extern char tmpuser[];
	extern int tmppin, tmpdep, lastfired;
	char c;
    int line = p - 100, maxPIN = 99 + countRegisteredUsers(), counter = 0, state;
    if(p<100 || p>maxPIN)
		return -1;
	else{
        FILE* userinfo = fopen("users.txt", "r");
        while((c=fgetc(userinfo)) != EOF){
        	if(c=='\n')
          		counter++;
          	if(counter==line)
          	    fscanf(userinfo, "%s" "%d" "%d" "%d", tmpuser, &tmppin, &state, &tmpdep);
        }
        fclose(userinfo);
		if(tmppin==lastfired)  	return 0;
        else 					return 1;
    }
}

/*Checks if user has been registered or not*/
int isUserRegistered(int pwd){
	extern char tmpuser[];
	extern int tmppin, tmpdep;
	char c;
    int line = pwd - 100, maxPIN = 99 + countRegisteredUsers(), counter = 0, state;
    if(pwd<100 || pwd>maxPIN)
		return -1;
	else{
        FILE* userinfo = fopen("users.txt", "r");
        while((c=fgetc(userinfo)) != EOF){
        	if(c=='\n')
          		counter++;
          	if(counter==line)
          	    fscanf(userinfo, "%s" "%d" "%d" "%d", tmpuser, &tmppin, &state, &tmpdep);
        }
		if(tmpdep<=5)
          	return 1;
        fclose(userinfo);
    }
}	

/*Prints data of a specific user*/
int printUserReport(char filename[MAX]){
	extern int tmppin;
	int a = 0, b = 0, spaces = 0, location, counter = 0, newline = 0, data;
	char c, d[MAX], e, string[100];
    printf("\n");
    FILE* report = fopen(filename, "r");
    if(report==NULL){
        printf("Cannot open file. Make sure you created the corresponding file.\n");
        return 0;
    }
    c = fgetc(report);
    while(c!=EOF){
    	if(c==' ')	spaces++;
    	while(isdigit(c) && spaces<=2){
    		d[a]=c;
    		a++;
    		c=fgetc(report);
		}
		d[a]='\0';
		if(c=='\n'){
			spaces = 0;
			newline++;
		}	
		if(tmppin==atoi(d)){
			location = newline;
	        while((e=fgetc(report)) != EOF){
	        	if(e=='\n')
	          		counter++;
	          	if(counter==location){
	          	    fscanf(report, "%[^\n]s", string);
	          	    printf("%s\n", string);
	          	    e=fgetc(report);
	          	}
	        }	
	        break;
		}else 		
			c=fgetc(report);
    }
    fclose(report);	
    printf("\n");	
	userMenu();
}

/*Prints a complete report*/
int printReport(char filename[MAX]){
    char c;
    printf("\n");
    FILE* report = fopen(filename, "r");
    if(report==NULL){
        printf("Cannot open file. Make sure you created the corresponding file.\n");
        return 0;
    }
    c = fgetc(report);
    while(c!=EOF){
        printf("%c", c);
        c = fgetc(report);
    }
    fclose(report);
    printf("\n");
    adminMenu();	
}

/*Calculates user performance based on worked hours in a week*/
int calculateUserPerformance(float wh){
	int points;
	if(wh>0.0 && wh<20.0) 			points = 1;
	else if(wh>=20.0 && wh<40.0)	points = 2;
	else if(wh>=40.0 && wh<60.0)	points = 3;
	else if(wh>=60.0 && wh<80.0)	points = 4;
	else if(wh>=80.0 && wh<120.0)	points = 5;
	else if(wh>=120.0 && wh<160.0)	points = 6;
	else if(wh>=160.0 && wh<192.0)	points = 7;
	else if(wh>=192.0 && wh<240.0)	points = 8;
	else if(wh>=240.0 && wh<312.0)	points = 9;
	else if(wh>=312.0 && wh<384.0)	points = 10;
	else  if(wh==0) 				points = 0;
	return points;		
}

/*Updates user data based on performance*/
int updateUser(int p, int performance){
	//Almost all files here are opened in write+ mode to delete or change information in a specific line.
    int line = p - 100, maxPIN = 99 + countRegisteredUsers(), counter = 0, state;
	extern char tmpuser[];
	extern int tmppin, tmpdep, lastfired;
	char c;
	FILE* userper = fopen("userperformance.txt", "a");
	if(performance>=0 && performance<5)			fprintf(userper, "%s %d: Performed terribly this month.\n", tmpuser, tmppin);	
	else if(performance>=5 && performance<10)	fprintf(userper, "%s %d: Performed well enough this month.\n", tmpuser, tmppin);
	fclose(userper);
    if(p<100 || p>maxPIN)
		return -1;
	else{
        FILE* userfired = fopen("fired.txt", "a");
        if(performance>=0 && performance<5){
			fprintf(userfired, "%s %d: 0\n", tmpuser, tmppin);
			printf("You were fired.\n");
			lastfired = tmppin;
			clockOut();
		}else{
			fprintf(userfired, "%s %d: 1\n", tmpuser, tmppin);
			printf("You worked well enough this month.");
			clockOut();
		}
        fclose(userfired);
    }
}
