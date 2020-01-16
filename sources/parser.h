#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *delimiters = " \n\t";

typedef struct input {
	int noOfCommands, noOfPipedCommands;
	char* commandWords[100];
	char* pipeCommandWords[100];
};

bool isPiped(char line[100]) {
	return strchr(line, "|") == 0;
}

struct input parse(char line[100]) {
	char buf[100];
	strcpy(buf, line);
	
	struct input result;
	char* token = strtok(buf, delimiters);
	result.noOfCommands = 0;
	result.noOfPipedCommands = 0;
	bool piped = isPiped(line);
	char* commandWords[100];	

	while (token != NULL) 
	{
		if (strcmp(token, "|") == 0)
			break;
		result.commandWords[result.noOfCommands++] = malloc(strlen(token));
		strcpy(result.commandWords[result.noOfCommands - 1], token);
		token = strtok(NULL, delimiters);		
	}

	if (piped) {
		token = strtok(NULL, delimiters);
		while (token != NULL) 
		{
			result.pipeCommandWords[result.noOfPipedCommands++] = malloc(strlen(token));
			strcpy(result.pipeCommandWords[result.noOfPipedCommands - 1], token);
			token = strtok(NULL, delimiters);	
		}
	}
	
	result.commandWords[result.noOfCommands++] = NULL;
	result.pipeCommandWords[result.noOfPipedCommands++] = NULL;

	return result;
}
