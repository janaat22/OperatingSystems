#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>

int main(void)
{
    char* prodv[500];
    char* consv[500];
    int i ;
    while(1)
    {
    printf("\n First program:");
        char user_input1[500];
        gets(user_input1);
        char *ptr = strtok(user_input1, " \t");        //parsing arguments
        i = 0;
        while(ptr != NULL)
        {
            // printf("'%s'\n", ptr);
            prodv[i] = ptr;
            ptr = strtok(NULL, " \t");
            i++;
        }
        prodv[i] = NULL;

    printf("\n Second program:");
        char user_input2[500];
        gets(user_input2);  
        char *ptr1 = strtok(user_input2, " \t");        //parsing arguments
        i = 0;
        while(ptr1 != NULL)
        {
            // printf("'%s'\n", ptr);
            consv[i] = ptr1;
            ptr1 = strtok(NULL, " \t");
            i++;
        }
        consv[i] = NULL;  

    int pd[2];

    // pid_t pid = fork();
    // if (pid == -1) { //error
    //     // char *error = strerror(errno);
    //     printf("error fork!!\n");
    //     return 1;
    // } 
    // if (pid == 0) { // child process
    //     close(pd[1]);
    //     dup2(pd[0], 0);
    //     execvp(consv[0], consv); // run command AFTER pipe character in userinput
    //     // char *error = strerror(errno);
    //     printf("unknown command\n");
    //     exit(0);
    // } else { // parent process
    //     close(pd[0]);
    //     dup2(pd[1], 1);
    //     execvp(prodv[0], prodv); // run command BEFORE pipe character in userinput
    //     // char *error = strerror(errno);
    //     printf("unknown command\n");
    // }
    // while(pid != wait(0));    

    // pid_t pid1;
    // pid_t pid2;
    // if ( (pid1 = fork()) == 0 ) {
    //     /* Redirect output of process into pipe */
    //     close(stdout);
    //     close(pd[0]);
    //     dup2( pd[1], stdout );
    //     execvp(consv[0], consv);
    // } 
    // if ( (pid2 = fork()) == 0 ) {
    //     /* Redirect input of process out of pipe */
    //     close(stdin);
    //     close(pd[1]);
    //     dup2( pd[0], stdin );
    //     execvp(prodv[0], prodv);
    // }

    pid_t kidpid, grandkidpid;
    kidpid = fork();
    if (kidpid == 0) {

            // shell child creates the pipe

            pipe(pd);

            // shell child creates grandchild
            grandkidpid =fork();
            if (grandkidpid == 0) 
            {                               
                close(pd[0]);
                // dup into stdout
                dup2(pd[1], 1);
                // run command BEFORE pipe character in userinput
                execvp(prodv[0], prodv); 
                // char *error = strerror(errno);
                close(pd[1]);

                _exit(1); // execvp() failed

            } 
            else 
            {
                close(pd[1]);
                // dup into stdin
                dup2(pd[0], 0);
                // run command AFTER pipe character in userinput
                execvp(consv[0], consv); 
                // char *error = strerror(errno);
                close(pd[0]);
            } // innermost if-else

        }

        while(kidpid != wait(0)); 

     

           // back to the shell

   
/* Main process */
    // close( pd[0] );
    // close( pd[1] );
    
    }
    return 0;
}