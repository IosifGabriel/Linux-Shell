#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct input {
	int noOfCommands;
	char* commandWords[100];
};

struct input parse(char line[100]) {
	char buf[100];
	strcpy(buf, line);
	
	struct input result;
	char* token = strtok(buf, " ");
	result.noOfCommands = 0;
	char* commandWords[100];	

	while (token != NULL) 
	{
		result.commandWords[result.noOfCommands++] = malloc(strlen(token));
		strcpy(result.commandWords[result.noOfCommands - 1], token);
		printf("%s ", result.commandWords[result.noOfCommands - 1]);
		token = strtok(NULL, " ");		
	}
	return result;
	
}

int main(int argc, char* args[100]) 
{
	char idk[100];
	fgets(idk, 100, stdin);
	parse(idk);
	return 0;
}


