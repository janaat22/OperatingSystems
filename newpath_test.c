#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>

int main(void)
{
    char newpath[] = "      newpath     \"a new\"";
    char pathtogive[500];
    strcpy(pathtogive,newpath);
    // printf("PATH : %s\n", getenv("PATH"));
    // // printf("HOME : %s\n", getenv("HOME"));
    // // printf("ROOT : %s\n", getenv("ROOT"));
    // char path[3000] = "PATH=";
    // char *argg = strcat(path,newpath);
    // printf("concated %s", argg);
    // if(putenv(argg)!= 0)
    // {
    //     printf("new path not set");
    // }

    // printf("PATH : %s\n", getenv("PATH"));
// printf("newpath is %s", newpath);
    char *input_command = strtok(newpath, " \t"); 
    printf("input prog is %s\n", input_command);
    char *path = strtok(pathtogive, "\"");
    printf("new path is %s\n",  strtok(NULL, "\""));
    
    // const char *start_ptr = strchr(newpath, '\"');
    // if(ptr) {
    // int index = ptr - newpath;
    // printf("index is :%d", index);
    // // do something
    // }


    

    return 0;
}