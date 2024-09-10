void win_get_fullname(char *fullname,char *path, char *name)
{
	STRCPY(fullname, path);
	strcat(fullname, "/");
	strcat(fullname, name);
}