#include "cd.h"


void cd(char* cwd)
{	
	int ret;
	if(strcmp(cwd, "~")==0)
		ret = chdir("home");
	ret = chdir(cwd);
	if(ret == 0)
		pwd(cwd, 1);
	else perror(" ERROR IN CD ");
}

