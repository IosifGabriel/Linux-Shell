#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void changeDirectory(char* path)
{
	int result = chdir(path);
	if(result != 0)
        perror(NULL);
}

char* getCurrentDirectory()
{
    const int BUFFER_SIZE = 1000;
	char buffer[BUFFER_SIZE];

	char* path = getcwd(buffer, sizeof(buffer));

	if(path != NULL)
	    return path;
    
    perror(NULL);

    return NULL;
}

void createDirectory(char *name)
{
	int result= mkdir(name, 0777);
    if(result != 0)
        perror(NULL);
}

#endif