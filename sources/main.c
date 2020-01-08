#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include "parser.h"
#include "process.h"
#include "command.h"

void welcome()
{
    system("clear"); 
    printf("\n\nWelcome to shell!\n\n");
    sleep(1);
    system("clear");
}

char *readLine()
{
    char *buffer = NULL;
    size_t bufferSize = 0;

    getline(&buffer, &bufferSize, stdin);
    
    return buffer;
}

int main() 
{
    welcome(); 
  
    char *path;

    while (true)
    {
        path = getCurrentDirectory();

        printf("%s> ", path);
        
        char *line = readLine();
        char **args = parse(line).commandWords;

        if(strcmp(args[0], "exit") == 0) {
            exitProgram();
        }
        else if(strcmp(args[0], "cd") == 0) {
            changeDirectory(args[1]);
        }
        else if(strcmp(args[0],"pwd") == 0) {
            printf("%s \n", path);
        }
        else if(strcmp(args[0], "mkdir") == 0) {
            createDirectory(args[1]);
        }
        else {
            launchProcess(args);
        }
    }

    return 0;
}