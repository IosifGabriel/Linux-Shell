#include <stdio.h>
#include <string.h>


void addToHistory(char* line) {
	FILE* historyFile = fopen("history.txt", "a+");
	if (historyFile == NULL) {
		perror("Error appending to history.");
	} else {
		fprintf(historyFile,"%s", line);
		fflush(historyFile);	
	}
}

void printHistory() {
	FILE* historyFile = fopen("history.txt", "r");	

	int chunk = 1000;
	char* buf = malloc(chunk);
	if (buf == NULL) {
		perror("Malloc failed");
	}
	int nread = 0;
	printf("Displaying command history...\n");
	while((nread = fread(buf, 1, chunk, historyFile)) > 0) {
		printf(buf);
	} 
}
