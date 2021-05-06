//INSTRUCCIONES DE USO: Puedes compilarlo en OnlineGDB. Solo crea los siguientes archivos:
//"header.h", "logs.txt", "users.txt", "attendance.txt" y "workedhours.txt"
//Recuerda copiar la información en su archivo correspondiente.
//Los archivos de texto del repositorio sólo son ejemplos. NO necesitas copiar nada, a menos que quieras iniciar imprimiendo los reportes.
//Hay una falla en el programa: Sólo puedes iniciar sesión con el último PIN que el programa te dio, de otra forma no podrás usar los comandos cin y cout.
//Es decir, si te registras y te dan el PIN 101, y te registras de nuevo y usas el PIN 102, cin y cout sólo funcionarán con el PIN 102.
//Aún así, el programa imprimirá en un archivo .txt ambos pines.
//El programa usa scanf, así que asegúrate de que introduzcas los datos como se te pide.
//NOTA: Si usas OnlineGDB, notarás que el tiempo que imprime al usar cin, cout o logs es diferente al de tu computador.
#include "header.h"

int main(){
    menu();
    return 0;
}

int menu(){
    char cmd[MAXCMD];
    printf("\nAvailable commands:\n\treg - registers user into system.\n\tcin - clocks you in for work.\n\tcout - clocks you out of work.");
    printf("\n\twr - prints report of total hours worked by each user.\n\tar - prints attendance reports of users.\n\tlogs - prints logs.");
    printf("\n\tsee - prints registered users. \n\texit - exits program.\nType your command: ");
    scanf("%s", cmd);
    if(strstr(cmd, "reg"))
        generatePin();
    else if(strstr(cmd, "cin"))
        clockIn();
    else if(strstr(cmd, "cout"))
        clockOut();
    else if(strstr(cmd, "wr"))
        printWhReport();
    else if(strstr(cmd, "ar"))
        printAReport();
    else if(strstr(cmd, "logs"))
        printLogs();
    else if(strstr(cmd, "see"))
        printUserInfo();
    else if(strstr(cmd, "exit"))
        exit(0);
    else{
        printf("Error: Please check your entry and then try again.\n");
        menu();
    }
}

void generatePin(){
    int count;
    count = countRegisteredUsers() + 1;
    char user[MAX];
    extern int pin, tmppin;
    pin = 100 + count;
    printf("\nYour PIN is: %d\n", pin);
    printf("Insert your username: ");
    scanf("%s", user);
    printf("Registered user <%s> with PIN <%d>\n", user, pin);
    tmppin = pin;
    FILE *userinfo = fopen("users.txt", "a");
    fprintf(userinfo, "Registered user <%s> with PIN <%d>\n", user, pin);
    fclose(userinfo);
    menu();
}

void clockIn(){
    extern int pin, tmppin;
    printf("\nType your PIN to clock in for work: ");
    scanf("%d", &pin);
    if(pin==tmppin){
        printf("You're now working!\n\n");
        time_t mytime = time(NULL);
        char * time_str = ctime(&mytime);
        time_str[strlen(time_str)-1] = '\0';
        printf("Clocked in at: %s\n", time_str);
        FILE* logs = fopen("logs.txt", "a");
        fprintf(logs, "%d: Clocked in at %s\n", pin, time_str);
        fclose(logs);
        work();
    }else{
        if(tmppin==0){
            printf("There's no users in database. Sending you to menu...\n");
            menu();
        }
        printf("Error: Please check your entry and type again.\n");
        pin = tmppin;
        clockIn();
    }
    menu();
}

void clockOut(){
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
        if(tmppin==0){
            printf("There's no users in database. Sending you to menu...\n");
            menu();
        }
        printf("Error: Please check your entry and type again.\n");
        pin = tmppin;
        clockOut();
    }
    menu();
}

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

void work(){
    extern int pin;
    int mon, tue, wed, thu, fri, sat;
    float hrs, totalhrs;
    printf("Please type how many days you'll work today. 1 means you'll work, 0 means you'll skip work. Follow this format:\n");
    printf("'1 1 1 1 0 0'\nNote: You can work from monday to saturday.\n");
    printf("Insert days: ");
    scanf("%d %d %d %d %d %d", &mon, &tue, &wed, &thu, &fri, &sat);
    if((mon<0||mon>1)||(tue<0||tue>1)||(wed<0||wed>1)||(thu<0||thu>1)||(fri<0||fri>1)||(sat<0||sat>1)){
        printf("Error: Please check that your input consists only of zeros and ones (0, 1)\n\n");
        work();
    }
    if(mon==0&&tue==0&&wed==0&&thu==0&&fri==0&&sat==0){
        printf("You skipped an entire week of work. Your boss isn't happy with you!\n");
        FILE* ar = fopen("attendance.txt", "a");
        fprintf(ar, "%d Didn't attend a single day!\n", pin);
        fclose(ar);       
        FILE* wh = fopen("workedhours.txt", "a");
        fprintf(wh, "%d: Worked a total amount of 0 hours!\n", pin);
        fclose(wh);
        printf("You didn't work. You still have to clock out, though. Sending you to clock out...\n");
        clockOut();  
    }
    printf("\nNow type the amount of hours you'll work per day (from 1 up to 16): ");
    scanf("%f", &hrs);
    if(hrs>0 && hrs<=16){
        if(mon==1)
            totalhrs += hrs;
        if(tue==1)
            totalhrs += hrs;
        if(wed==1)
            totalhrs += hrs;
        if(thu==1)
            totalhrs += hrs;
        if(fri==1)
            totalhrs += hrs;
        if(sat==1)
            totalhrs += hrs;
        printf("Perfect! Now wait until your shifts end (one second per hour, total seconds to wait: %.2f).\n", totalhrs);
        FILE* ar = fopen("attendance.txt", "a");
        fprintf(ar, "%d attended on: MON %d - TUE %d - WED %d - THU %d - FRI %d - SAT %d\n", pin, mon, tue, wed, thu, fri, sat);
        fclose(ar);       
        FILE* wh = fopen("workedhours.txt", "a");
        fprintf(wh, "%d: Worked %.2f hours this week.\n", pin, totalhrs);
        fclose(wh);
        time_t start, end;
        time(&start);
        do time(&end); while(difftime(end, start) <= totalhrs);
        printf("You finished working. Sending you to clock out...\n");
        clockOut();
    }else{
        printf("Error: Please check your input and try again.\n\n");
        work();
    }
}

int printWhReport(){
    char c;
    printf("\n");
    FILE* wr = fopen("workedhours.txt", "r");
    if(wr==NULL){
        printf("Cannot open file. Make sure you created the corresponding file.\n");
        return 0;
    }
    c = fgetc(wr);
    while(c!=EOF){
        printf("%c", c);
        c = fgetc(wr);
    }
    fclose(wr);
    menu();
}

int printAReport(){
    char c;
    printf("\n");
    FILE* ar = fopen("attendance.txt", "r");
    if(ar==NULL){
        printf("Cannot open file. Make sure you created the corresponding file.\n");
        return 0;
    }
    c = fgetc(ar);
    while(c!=EOF){
        printf("%c", c);
        c = fgetc(ar);
    }
    fclose(ar);
    menu();   
}

int printLogs(){
    char c;
    printf("\n");
    FILE* logs = fopen("logs.txt", "r");
    if(logs==NULL){
        printf("Cannot open file. Make sure you created the corresponding file.\n");
        return 0;
    }
    c = fgetc(logs);
    while(c!=EOF){
        printf("%c", c);
        c = fgetc(logs);
    }
    fclose(logs);
    menu();   
}

int printUserInfo(){
    char c;
    printf("\n");
    FILE* userdata = fopen("users.txt", "r");
    if(userdata==NULL){
        printf("Cannot open file. Make sure you created the corresponding file.\n");
        return 0;
    }
    c = fgetc(userdata);
    while(c!=EOF){
        printf("%c", c);
        c = fgetc(userdata);
    }
    fclose(userdata);
    menu();   
}
