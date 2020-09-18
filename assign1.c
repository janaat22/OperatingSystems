#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>

int main(void)
{
    char* PATH_VAR = getenv("PATH"); //get PATH
    char* argv[500];
    int i = 0;
    int ExitShell()
    {
        exit(0);
    }
    while(1)
    {
        
        printf("\nMyShell:");
        char user_input[500];
        gets(user_input);
        // printf("User input is : %s", user_input);
        // printf("PATH is : %s", PATH_VAR);

        if(strcmp(user_input, "exit") == 0)         //handling exit command
        {
            ExitShell();
        }

        char *ptr = strtok(user_input, " ");        //parsing arguments
        i = 0;
        while(ptr != NULL)
        {
            // printf("'%s'\n", ptr);
            argv[i] = ptr;
            ptr = strtok(NULL, " ");
            i++;
        }
        argv[i] = NULL;
        // printf("argv 2 is :%s", argv[2]);

        int pid;
        if((pid = fork()) == 0)
        {
            execvp(argv[0], argv);
            _exit(0);
        }
        while(pid != wait(0));
    }
return 0;
}

