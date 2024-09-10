main(int argc, char *argv[])
{
	char	exe[128], uex[128];
	int	n;
	
	if (argc <= 1)
		return 1;
	n = strlen(argv[1]);
	if (n > 4  &&  !stricmp(argv[1]+n-4, ".exe")) {
		strcpy(exe, argv[1]);
		strcpy(uex, argv[1]);
		uex[n-4] = '\0';
		strcat(uex, ".uex");
	} else {
		strcpy(exe, argv[1]);
		strcat(exe, ".exe");
		strcpy(uex, argv[1]);
		strcat(uex, ".uex");
	}
	if (!_access(uex, 4)) {
		_unlink(exe);
		rename(uex, exe);
	}
	_execv(argv[1], argv+1);
	return 2;
}