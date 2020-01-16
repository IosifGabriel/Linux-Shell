#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <grp.h>
#include <time.h>
#include <pwd.h>

#define COLOR_DEFAULT "\x1B[0m"
#define COLOR_GREEN "\x1b[92m"
#define COLOR_BLUE "\x1b[94m"
#define COLOR_CYAN "\x1b[96m"

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

void nameFile(struct dirent* name, char* followup)
{	
	if(name->d_type == DT_REG)
		printf("%s%s%s", COLOR_BLUE, name->d_name, followup); // regular file
	else if (name->d_type == DT_DIR) 
		printf("%s%s%s", COLOR_GREEN, name->d_name, followup); //directory
	else 
		printf("%s%s%s", COLOR_CYAN, name->d_name, followup); // ordinary file
}

void listcwd()
{
	struct dirent **listr;
	int listn = scandir(".", &listr, 0, alphasort);
	if(listn >= 0)
	{
		printf("+--- Total %d objects in this directory\n", listn - 2);
		for(int i = 0; i < listn; i++)
		{
			if(strcmp(listr[i]->d_name, ".") == 0 || strcmp(listr[i]->d_name, "..") == 0)
				continue;
			else
				nameFile(listr[i], "\t");
			if(i % 8 == 0)
				printf("\n");
		}
		printf("%s\n", COLOR_DEFAULT);
	}
	else
	{
		perror("error in ls");
	}
}

void listcwdlong()
{
	int total = 0;
	char timer[14];	
	struct dirent **listr;
	struct stat details;
	int listn = scandir(".", &listr, 0, alphasort);
	if(listn > 0)
	{
		printf("+--- Total %d objects in this directory \n", listn - 2);
		for(int i = 0; i < listn; i++)
		{
			if(strcmp(listr[i]->d_name, ".") == 0 || strcmp(listr[i]->d_name, "..") == 0)
			{
				continue;
			}
			else if (stat(listr[i]->d_name, &details) == 0)
			{
				total += details.st_blocks;
				printf("%s%s", COLOR_DEFAULT, (S_ISDIR(details.st_mode)) ? "d" :"-");
				printf("%s%s", COLOR_DEFAULT, (details.st_mode & S_IRUSR) ? "r" : "-");
				printf("%s%s", COLOR_DEFAULT, (details.st_mode & S_IWUSR) ? "w" : "-");
				printf("%s%s", COLOR_DEFAULT, (details.st_mode & S_IXUSR) ? "x" : "-");
				printf("%s%s", COLOR_DEFAULT, (details.st_mode & S_IRUSR) ? "r" : "-");
				printf("%s%s", COLOR_DEFAULT, (details.st_mode & S_IWUSR) ? "w" : "-");
				printf("%s%s", COLOR_DEFAULT, (details.st_mode & S_IXUSR) ? "x" : "-");
				printf("%s%s", COLOR_DEFAULT, (details.st_mode & S_IRUSR) ? "r" : "-");
				printf("%s%s", COLOR_DEFAULT, (details.st_mode & S_IWUSR) ? "w" : "-");
				printf("%s%s", COLOR_DEFAULT, (details.st_mode & S_IXUSR) ? "x" : "-");
				
				printf("%2ld ",(unsigned long)(details.st_nlink));
				printf("%s ", (getpwuid(details.st_uid))->pw_name);
				printf("%s ", (getgrgid(details.st_gid))->gr_name);

				printf("%5lld ",(unsigned long long) details.st_size);
				strftime (timer,14, "%h %d %H:%M", localtime(&details.st_mtime));
				printf("%s ", timer);
				nameFile(listr[i], "\n");
			}
		}
		printf("+--- Total %d object contents \n", total / 2);
	}	
	else
	{
		printf("+--- Empty directory \n");
	}
}

void clearScreen()
{
	const char* blank= "\e[1;1H\e[2J";
	write(STDOUT_FILENO,blank, 11);
}

void removeDirectory(char *name)
{	
	int statrm = rmdir(name);
	if(statrm == -1)
	{
		perror("Directory not found!");
	}
}

void exitProgram()
{	
	// TODO
	printf("Exiting shell...\n");
	sleep(2);
	exit(0);
}

#endif
