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
    char* prodv[500];
    char* consv[500];
    int i, j, k = 0;
    int ExitShell()
    {
        exit(0);
    }

    int parseInput(char *input)
    {
        i, j, k = 0;
        if(input == NULL)
        {
           printf("\ncommand error!\n");
           return 0;
        }
        i = 0;
        while(input != NULL)
        {
            // printf("'%s'\n", ptr);

            if(strcmp(input, "redirect") == 0)
            {
                printf("\nREDIRECT\n");
                if(i > 0)
                {
                    printf("\ncommand error!\n");
                    return 0;
                }
                j = 0;
                input = strtok(NULL, " \t");
                while(input != NULL)
                {                    
                    if(strcmp(input, "into") == 0)
                    {
                        if(j == 0)
                            {
                                printf("\ncommand error!\n");
                                return 0;
                            }

                        printf("\nINTO\n");
                        k = 0;
                        input = strtok(NULL, " \t");
                        while(input != NULL)
                        {
                            consv[k] = input;
                            printf("\n adding this to consv: %s", consv[k]);
                            input = strtok(NULL, " \t");
                            k++;
                        }
                        consv[k] = NULL;
                        break;
                    }
                    prodv[j] = input;
                    printf("\n adding this to prodv: %s", input);
                    input = strtok(NULL, " \t");
                    j++;
                }

                if(k == 0)
                {
                    printf("\n Command error!\n");
                    return 0;
                }
                prodv[j] = NULL;                
                break;
            }

            else if (strcmp(input, "into") == 0)
            {
                printf("\n Command error!\n");
                return 0;                
            }

            argv[i] = input;
            printf("\ninput added to argv now: %s\n", input);

            input = strtok(NULL, " \t");
            
            i++;
        }

        argv[i] = NULL;

        if(j > 0 && k > 0)
        {
            return 2;
        }
        else
        {
            return 1;
        }   
        
    }

    while(1)
    {
        printf("\nMyShell:");
        char user_input[500];
        gets(user_input);
        // printf("User input is : %s", user_input);
        // printf("PATH is : %s", PATH_VAR);

        char *input_command = strtok(user_input, " \t");        //parsing arguments
        int parsed_output = parseInput(input_command);
        if(parsed_output == 0)
        {
            printf("\n continuing!");
            continue;
        }
        else if(parsed_output == 1)
        {
            if(strcmp(argv[0], "exit") == 0)         //handling exit command
                {
                    ExitShell();
                }
            else if (strcmp(argv[0], "cd") == 0)
            {
                if(chdir(argv[1])!=0)  //changing current working directory using chdir
                {
                printf("\npath not found: %s\n",argv[1]);
                }  
            }

            int pid;
            if((pid = fork()) == 0)
            {
                execvp(argv[0], argv);
                _exit(0);
            }
            while(pid != wait(0));
        }

        else
        {
            printf("\n prod :%s", prodv[0]);
            printf("\n consv :%s", consv[1]);

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

        }

       
        
        // printf("argv 1 & 2 is :%s,  %s", argv[0], argv[1]);


    }
return 0;
}

