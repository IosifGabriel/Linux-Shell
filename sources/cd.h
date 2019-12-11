void cd(char* path)
{
	int ret = chdir(path);
	if(ret == 0)
		pwd(cwd, 0);
	else perror(" ERROR IN CD ");
}
