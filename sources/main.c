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
    printf("$$\\       $$\\                                               $$\\                 $$\\ $$\\ \n");
    printf("$$ |      \\__|                                              $$ |                $$ |$$ |\n");
    printf("$$ |      $$\\ $$$$$$$\\  $$\\   $$\\ $$\\   $$\\        $$$$$$$\\ $$$$$$$\\   $$$$$$\\  $$ |$$ |\n");
    printf("$$ |      $$ |$$  __$$\\ $$ |  $$ |\\$$\\ $$  |      $$  _____|$$  __$$\\ $$  __$$\\ $$ |$$ |\n");
    printf("$$ |      $$ |$$ |  $$ |$$ |  $$ | \\$$$$  /       \\$$$$$$\\  $$ |  $$ |$$$$$$$$ |$$ |$$ |\n");
    printf("$$ |      $$ |$$ |  $$ |$$ |  $$ | $$  $$<         \\____$$\\ $$ |  $$ |$$   ____|$$ |$$ |\n");
    printf("$$$$$$$$\\ $$ |$$ |  $$ |\\$$$$$$  |$$  /\\$$\\       $$$$$$$  |$$ |  $$ |\\$$$$$$$\\ $$ |$$ |\n");
    printf("\\________|\\__|\\__|  \\__| \\______/ \\__/  \\__|      \\_______/ \\__|  \\__| \\_______|\\__|\\__|\n");
    printf("\n\n \t Authors: \t Iosif Gabriel \t Jilavu Alexandru \t Matei Gabriel\n");
    sleep(1);
    system("clear");
    printf(" /$$       /$$                                               /$$                 /$$ /$$\n");
    printf("| $$      |__/                                              | $$                | $$| $$\n");
    printf("| $$       /$$ /$$$$$$$  /$$   /$$ /$$   /$$        /$$$$$$$| $$$$$$$   /$$$$$$ | $$| $$\n");
    printf("| $$      | $$| $$__  $$| $$  | $$|  $$ /$$/       /$$_____/| $$__  $$ /$$__  $$| $$| $$\n");
    printf("| $$      | $$| $$  \\ $$| $$  | $$ \\  $$$$/       |  $$$$$$ | $$  \\ $$| $$$$$$$$| $$| $$\n");
    printf("| $$      | $$| $$  | $$| $$  | $$  >$$  $$        \\____  $$| $$  | $$| $$_____/| $$| $$\n");
    printf("| $$$$$$$$| $$| $$  | $$|  $$$$$$/ /$$/\\  $$       /$$$$$$$/| $$  | $$|  $$$$$$$| $$| $$\n");
    printf("|________/|__/|__/  |__/ \\______/ |__/  \\__/      |_______/ |__/  |__/ \\_______/|__/|__/\n");
    printf("\n\n \t Authors: \t Iosif Gabriel \t Jilavu Alexandru \t Matei Gabriel\n");
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
	else if(strcmp(args[0], "ls")==0){
		
		if(args[1]=="-l");
			listcwdlong();
		else			
			listcwd();	
	}
	else if(strcmp(args[0], "cls")==0){
		clearscreen();	
	}
	else if(strcmp(args[0], "rmdir") == 0) {
		removeDirectory(args[1]);	
	}
        else {
            launchProcess(args);
        }
    }

    return 0;
}
