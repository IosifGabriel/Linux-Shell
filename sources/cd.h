void cd(char* path)
{
	int ret = chdir(path);
	if(ret == 0)
		pwd();
	else perror(" ERROR IN CD ");
}
