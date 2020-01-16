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

#define DEF "\x1B[0m"

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
	if(name->d_type == DT_REG)  // regular file
	{
		printf("%s%s%s", "\x1b[94m", name->d_name, followup);
	}
	else if (name->d_type == DT_DIR) //directory
	{
		printf("%s%s%s", "\x1b[92m", name->d_name, followup);
	}
	else // ordinary file
	{
		printf("%s%s%s", "\x1b[96m", name->d_name, followup);
	}
}


void listcwd() // list curent working directory
{
	int i=0;
	struct dirent **listr;
	int listn=scandir(".",&listr,0,alphasort);
	if(listn >=0)
	{
		printf("+--- Total %d objects in this directory\n",listn-2);
			for(i=0;i<listn;i++)
			{
				if(strcmp(listr[i]->d_name,".")==0 || strcmp(listr[i]->d_name,"..")==0)
				{
					continue;
				}
				else nameFile(listr[i]," ");
				if(i%8==0) printf("\n");
			}
			printf("%s\n", "\x1b[92m");
	}
	else
	{
		perror("error in ls");

	}

}

void listcwdlong()
{
	int i=0,total = 0;
	char timer[14];	
	struct dirent **listr;
	struct stat details;
	int listn = scandir(".", &listr, 0, alphasort);
	if(listn >0)
	{
		printf("+--- Total %d objects in this directory \n", listn-2);
		for(i=0;i<listn;i++)
		{
			if(strcmp(listr[i]->d_name, ".")==0 || strcmp(listr[i]->d_name, "..") == 0)
			{
				continue;
			}
			else if ( stat(listr[i]->d_name, &details)==0)
			{
				total += details.st_blocks;
				printf("%s%ls", DEF, (S_ISDIR(details.st_mode)) ? "d" :"-");
				printf("%s%ls", DEF, (details.st_mode & S_IRUSR) ? "r" : "-");
				printf("%s%ls", DEF, (details.st_mode & S_IWUSR) ? "w" : "-");
				printf("%s%ls", DEF, (details.st_mode & S_IXUSR) ? "x" : "-");
				printf("%s%ls", DEF, (details.st_mode & S_IRUSR) ? "r" : "-");
				printf("%s%ls", DEF, (details.st_mode & S_IWUSR) ? "w" : "-");
				printf("%s%ls", DEF, (details.st_mode & S_IXUSR) ? "x" : "-");
				printf("%s%ls", DEF, (details.st_mode & S_IRUSR) ? "r" : "-");
				printf("%s%ls", DEF, (details.st_mode & S_IWUSR) ? "w" : "-");
				printf("%s%ls", DEF, (details.st_mode & S_IXUSR) ? "x" : "-");
				
				printf("%2ld ",(unsigned long)(details.st_nlink));
				printf("%s ", (getpwuid(details.st_uid))->pw_name);
				printf("%s ", (getgrgid(details.st_gid))->gr_name);

				printf("%5lld ",(unsigned long long) details.st_size);
				strftime (timer,14, "%h %d %H:%M", localtime(&details.st_mtime));
				printf("%s ", timer);
				nameFile(listr[i]."\n");
			}
		}
		printf("+--- Total %d object contents \n", total/2);
	}	
	else
	{
		printf("+--- Empty directory \n");
	}
}

	

void clearscreen()
{
	const char* blank= "\e[1;1H\e[2J";
	write(STDOUT_FILENO,blank,11);
}

void removeDirectory(char *name)
{	
	int statrm = rmdir(name);
	if(statrm==-1)
	{
		perror("directory not found!");
	}
}

void exitProgram()
{	
	printf("Exiting shell...\n");
	sleep(2);
	exit(0);
}

#endif
