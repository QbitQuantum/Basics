static int open_dso(const char * path, pid_t * pidp, rpm_loff_t *fsizep)
{
    static const char * cmd = NULL;
    static int initted = 0;
    int fdno;

    if (!initted) {
	cmd = rpmExpand("%{?__prelink_undo_cmd}", NULL);
	initted++;
    }

    if (pidp) *pidp = 0;

    if (fsizep) {
	struct stat sb, * st = &sb;
	if (stat(path, st) < 0)
	    return -1;
	*fsizep = st->st_size;
    }

    fdno = open(path, O_RDONLY);
    if (fdno < 0)
	return fdno;

    if (!(cmd && *cmd))
	return fdno;

    if (pidp != NULL && is_prelinked(fdno)) {
	int pipes[2];
	pid_t pid;

	close(fdno);
	pipes[0] = pipes[1] = -1;
	if (pipe(pipes) < 0)
	    return -1;

	pid = fork();
	if (pid < 0) {
	    close(pipes[0]);
	    close(pipes[1]);
	    return -1;
	}

	if (pid == 0) {
	    ARGV_t av, lib;
	    int dfd;
	    argvSplit(&av, cmd, " ");

	    close(pipes[0]);
	    dfd = dup2(pipes[1], STDOUT_FILENO);
	    close(pipes[1]);
	    if (dfd >= 0 && (lib = argvSearch(av, "library", NULL)) != NULL) {
		*lib = (char *) path;
		unsetenv("MALLOC_CHECK_");
		execve(av[0], av+1, environ);
	    }
	    _exit(127); /* not normally reached */
	} else {
	    *pidp = pid;
	    fdno = pipes[0];
	    close(pipes[1]);
	}
    }

    return fdno;
}