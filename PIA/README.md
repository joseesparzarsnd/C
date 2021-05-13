# Final Project.
My final project will be an improved version of the homework 7. 
## How will it work?
The new version of the program will include a paying system. The employee will get paid a certain amount of money per hour depending on the department they work at, 
with extra hours being worth an extra 15%. The program will also be able to determine the performance of the employee depending on how many hours they work. If the
user works the required number of hours a week, they will keep their position. If they work enough extra hours, they will be ascended. If they don’t work well enough, 
they will be descended to a lower-paying department. If they barely work, they will be fired and their data will be inaccessible.

The program will keep the same commands I put in originally:

![image](https://user-images.githubusercontent.com/78566958/118166580-41f20a80-b3eb-11eb-8815-6061a628f9af.png)

The difference will be that “wr”, “ar”, “logs” and “see” commands will no longer be accessible from the main menu. Also, there will be two new commands, “login” and 
"logout" to log in and out of the system and see some special stuff. If an employee logs in, they will see the options “balance” and “twh”. “balance” command will 
show them the amount of money they’ve made so far, and “twh” command will show them how many hours they’ve worked and if they’re on risk of being fired or not. Once
they use "logout" the program will return to the main menu. 

People with higher ranks, like the boss of a department, or an admin, will be able to access the “wr”, “ar”, “logs” and “see” commands after login in with a special pin.

The program will be able to print and read information inside .txt files to make sure the inserted pin belongs to a user registered in the system, and to be able to print
the information of that user whenever it’s requested.
