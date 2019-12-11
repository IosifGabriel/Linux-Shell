/* make folder */
void mkdir(char *name)
{
	int stat= mkdir(name, 0777);
	if(stat == -1)
		perror( " ERROR IN MAKING NEW DIRECTORY ");
}
