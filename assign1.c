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
    char* argv[500]; // arguments for execvp
    char* prodv[500]; //producer commands for piping
    char* consv[500]; //consumer commands for piping
    int i, j, k = 0; //indices for arrays
    char user_input[500]; // raw input from user
    char user_input_copy[500]; // copy of raw input from user
    // Handle Exit command
    int ExitShell()
    {
        exit(0);
    }

    int printError()
    {
        printf("\ncommand error!\n");
        //return 0 to simply continue the while loop after displaying error
        return 0;
    }

    //parse user input
    //input: user input
    //output: argv, prodv and conv arrays 
    //return: 0 - continue while loop, 1,2 - special commands like cd, exit, newpath, redirect
    int parseInput(char *input)
    {
        //array indices
        i, j, k = 0; 
        //check if input is NULL
        if(input == NULL)
        {
           return printError();
        }

        i = 0;
        //spilt input until NULL
        while(input != NULL)
        {
            //if found 'Redirect' in command -> start populating in prodv array
            if(strcmp(input, "redirect") == 0)
            {
                // if argv has commands stored -> 'redirect' found in the middle of input, so print error message
                if(i > 0)
                {
                    return printError();
                }
                //prodv index to 0
                j = 0;

                input = strtok(NULL, " \t");

                // store into prodv while split input is not NULL
                while(input != NULL)
                {                    
                    if(strcmp(input, "into") == 0)
                    {
                        // if prodv array size is 0, i.e, no command after 'redirect' but 'into'
                        if(j == 0)
                            {
                                return printError();
                            }
                        //consv index to 0
                        k = 0;
                        input = strtok(NULL, " \t");

                        // store into consv until input is NULL
                        while(input != NULL)
                        {
                            consv[k] = input;
                            input = strtok(NULL, " \t");
                            //increment consv index after appending a command
                            k++;
                        }
                        // set last index of cosnv to NULL
                        consv[k] = NULL; 
                        //break while loop of 'redirect' command
                        break;
                    }
                    prodv[j] = input;
                    input = strtok(NULL, " \t");
                    //increment prodv index after appending a command
                    j++;
                }
                //if consv array size is 0
                if(k == 0)
                {
                    return printError();
                }
                // set last index of cosnv to NULL
                prodv[j] = NULL; 
                break;
            }

            //if 'into' found in user input without a 'redirect' 
            else if (strcmp(input, "into") == 0)
            {
               return printError();              
            }

            //if 'newpath' found in user input
            else if(strcmp(input, "newpath") == 0)
            {
                // 'newpath' found in the middle of the input
                if(i > 0)
                {
                    return printError();
                }
                //set argv[0] as 'newpath'
                argv[0] = input;
                //parse the remaining input to obtain the new path by spiltting the string using double-quote character
                char *path_to_set = strtok(user_input_copy, "\"");
                //set argv[1] as newpath value
                argv[1] = strtok(NULL, "\"");
                return 1;
            
            }

            //if no special command detected, append command in argv array
            argv[i] = input;
            input = strtok(NULL, " \t");
            // increment argv array index
            i++;
        }
        //set last index of argv to NULL
        argv[i] = NULL;

        // return 2 for pipe commands (prodv and consv arrays to be taken by execvp())
        if(j > 0 && k > 0)
        {
            return 2;
        }
        //return 1 for other commands
        else
        {
            return 1;
        }   
        
    }


    // method to execute pipe commands
    int execute_pipe()
    {
            int pd[2];
            pipe(pd);
            pid_t kidpid, grandkidpid;

            // child process
            kidpid = fork();

            //error
            if (kidpid == -1) 
            {                 
                printf("error fork!!\n");
                return 1;
            }             

            if (kidpid == 0) 
            {

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

        return 0;
    }

    while(1)
    {
        printf("\nMyShell:");        
        gets(user_input);
        //save a copy of the user input
        strcpy(user_input_copy, user_input);

        //parsing arguments
        char *input_command = strtok(user_input, " \t");   
        // call parseInput to populate argv, prodv, consv arrays   
        int parsed_output = parseInput(input_command);
        // if return value is 0, continue..
        if(parsed_output == 0)
        {
            continue;
        }
        // of return value = 1 
        else if(parsed_output == 1)
        {            
            //handling 'exit' command
            if(strcmp(argv[0], "exit") == 0)         
            {
                ExitShell();
            }
            //handling 'cd' command
            else if (strcmp(argv[0], "cd") == 0)
            {
                if(chdir(argv[1])!=0)  //changing current working directory using chdir
                {
                printf("\npath not found: %s\n",argv[1]);
                }  
                continue;
            }
            //handling 'newpath' command
            else if(strcmp(argv[0], "newpath") == 0)
            {
                // forming argument of putenv()
                char pathname[3000] = "PATH=";
                char *putenv_arg = strcat(pathname,argv[1]);
                if(putenv(putenv_arg)!= 0)
                {
                    printf("ERROR: new path not set!");
                }
                // print newly set path
                printf("\nPATH is set to: %s\n", getenv("PATH"));
                continue;                
            }

            //execute rest of the commands
            int pid;
             
            if((pid = fork()) == 0)
            {
                // child process
                int errno = execvp(argv[0], argv);
                char *error = strerror(errno);
                printf("Error: %s", error);
                _exit(0);
            }
            //wait for the child process to complete
            while(pid != wait(0));
        }

        else
        {
            execute_pipe();
        }
    }
return 0;
}
