#include <stdio.h>
#include<string.h> 
#include <stdbool.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 

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
  
    while (true)
    {
        printf("> ");
        char *line = readLine();
        printf("Entered: %s", line);
    }

    return 0;
}