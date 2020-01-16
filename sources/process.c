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

void launchProcessPiped(char** args, char** argspiped)
{
    int pipefd[2]; // 0 = read end, 1 = write end
    if (pipe(pipefd) < 0) { 
        printf("\nPipe could not be initialized"); 
        return; 
    }

    pid_t p1 = fork(); 
    if (p1 < 0) { 
        printf("\nCould not fork"); 
        return; 
    }
  
    if (p1 == 0) { 
        close(pipefd[0]); 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 
  
        if (execvp(args[0], args) < 0) {
            printf("\nCould not execute command 1.."); 
            exit(0); 
        } 
    } else { 
        pid_t p2 = fork();
        if (p2 < 0) { 
            printf("\nCould not fork"); 
            return; 
        } 
        
        if (p2 == 0) { 
            close(pipefd[1]); 
            dup2(pipefd[0], STDIN_FILENO); 
            close(pipefd[0]); 
            if (execvp(argspiped[0], argspiped) < 0) { 
                printf("\nCould not execute command 2.."); 
                exit(0); 
            } 
        } else { 
            wait(NULL); 
            wait(NULL); 
        } 
    } 
}