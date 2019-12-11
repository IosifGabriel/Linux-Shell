#include "process.h"

void launchProcess(char **args)
{
    pid_t pid = fork(); 
    if (pid < 0)
    { 
        printf("Failed forking child\n"); 
    }
    else if (pid == 0)
    { 
        if (execvp(args[0], args) < 0)
            printf("Could not execute command..\n");
    }
    else
    {
        wait(NULL);
    } 
}
