void
generate_filename(const char *dirname, const char *prefix, char *filename)
{
#ifdef	WIN32
	int	pid = 0;

	pid = _getpid();
#else
	pid_t	pid = 0;
	struct passwd *ptr = 0;

	ptr = getpwuid(getuid());
	pid = getpid();
#endif
	if (dirname == 0 || filename == 0)
		return;

	strcpy(filename, dirname);
	strcat(filename, DIRSEPARATOR);
	if (prefix != 0)
		strcat(filename, prefix);
#ifndef WIN32
	strcat(filename, ptr->pw_name);
#endif
	sprintf(filename, "%s%u%s", filename, pid, ".log");
	return;
}