int
open_process(SUBPROC *proc, char *av[])
{
	char *cmdpath;
	char *cmdstr;

	proc->running = 0;
	if (av == NULL) { return -1; }
	cmdpath = getpath(av[0], getenv("PATH"), X_OK);
	cmdstr = quoted_cmdline(cmdpath, av+1);
	if (cmdstr == NULL) { return 0; }
	return start_process(proc, cmdstr);
}