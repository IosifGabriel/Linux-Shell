#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *delimiters = " \n\t";

typedef struct input {
	int noOfCommands;
	char* commandWords[100];
};

struct input parse(char line[100]) {
	char buf[100];
	strcpy(buf, line);
	
	struct input result;
	char* token = strtok(buf, delimiters);
	result.noOfCommands = 0;
	char* commandWords[100];	

	while (token != NULL) 
	{
		result.commandWords[result.noOfCommands++] = malloc(strlen(token));
		strcpy(result.commandWords[result.noOfCommands - 1], token);
		token = strtok(NULL, delimiters);		
	}
	result.commandWords[result.noOfCommands++] = NULL;

	return result;
}