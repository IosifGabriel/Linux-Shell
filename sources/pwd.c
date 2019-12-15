/* Implementation for pwd in shell -1 prints, 0 stores */
#define NULL 0

int pwd(char* cwdstr, int command)
{
	char temp[1000];
	char* path=getcwd(temp, sizeof(temp));
	if(path!=NULL)
	{
		strcpy(cwdstr, temp);
		if(command == 1)
			printf("%s\n", cwdstr);
	}
	else perror(" ERROR IN GETCWD() : ");
}

	
