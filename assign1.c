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
    char user_input[500];
    char user_input_copy[500];
    int terminate_while = 0;
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
                            // printf("\n adding this to consv: %s", consv[k]);
                            input = strtok(NULL, " \t");
                            k++;
                        }
                        consv[k] = NULL;
                        break;
                    }
                    prodv[j] = input;
                    // printf("\n adding this to prodv: %s", input);
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

            else if(strcmp(input, "newpath") == 0)
            {
                argv[0] = input;
                char *path_to_set = strtok(user_input_copy, "\"");
                argv[1] = strtok(NULL, "\"");
                return 1;
            
            }

            argv[i] = input;

            // printf("\ninput added to argv : %s\n", input);

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

    int execute_pipe()
    {
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
                // terminate_while = 1;
            } else { // parent process
                close(pd[0]);
                dup2(pd[1], 1);
                execvp(prodv[0], prodv); // run command BEFORE pipe character in userinput
                // char *error = strerror(errno);
                printf("unknown command\n");
                // terminate_while = 1;
            }

            return 0;
    }

    while(!terminate_while)
    {
        printf("\nMyShell:");        
        gets(user_input);
        
        strcpy(user_input_copy, user_input);

        char *input_command = strtok(user_input, " \t");        //parsing arguments
        int parsed_output = parseInput(input_command);
        if(parsed_output == 0)
        {
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
                continue;
            }
            else if(strcmp(argv[0], "newpath") == 0)
            {
                char pathname[3000] = "PATH=";
                char *putenv_arg = strcat(pathname,argv[1]);
                if(putenv(putenv_arg)!= 0)
                {
                    printf("ERROR: new path not set!");
                }
                printf("\nPath is : %s\n", getenv("PATH"));
                continue;
                
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

            int return_pipe = execute_pipe();
            printf("return from pipe %d", return_pipe);
            continue;

        }
    }
return 0;
}
