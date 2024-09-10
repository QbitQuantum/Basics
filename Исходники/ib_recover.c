/*********************************************************************
Restart the process with the same args. */
static
void
restart(
/*====*/
	int		argc,
	char*		argv[])
{
	(void) argc;

#ifdef __WIN__
	_execvp(argv[0], argv);
#else
	execvp(argv[0], argv);
#endif
	perror("execvp");
	abort();
}