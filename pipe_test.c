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
    pipe(pd);

    pid_t pid = fork();
    if (pid == -1) { //error
        // char *error = strerror(errno);
        printf("error fork!!\n");
        return 1;
    } 
    if (pid == 0) { // child process
        close(pd[1]);
        dup2(pd[0], 0);
        execvp(consv[0], consv); // run command AFTER pipe character in userinput
        // char *error = strerror(errno);
        printf("unknown command\n");
        return 0;
    } else { // parent process
        close(pd[0]);
        dup2(pd[1], 1);
        execvp(prodv[0], prodv); // run command BEFORE pipe character in userinput
        // char *error = strerror(errno);
        printf("unknown command\n");
        return 0;
    }
        

    return 0;
}