/* replacement for execve() of kLIBC */
int
execve(const char *name, char * const *argv, char * const *envp)
{
	const char *exec_name;
	FILE *fp;
	char sign[2];
	char *rsp_argv[3];
	char *rsp_name_arg;
	int pid;
	int status;
	int fd;
	int rc;

	/*
	 * #! /bin/sh : append .exe
	 * extproc sh : search sh.exe in PATH
	 */
	exec_name = search_path(name, path, X_OK, NULL);
	if (!exec_name) {
		errno = ENOENT;
		return (-1);
	}

	/*-
	 * kLIBC execve() has problems when executing scripts.
	 * 1. it fails to execute a script if a directory whose name
	 *    is same as an interpreter exists in a current directory.
	 * 2. it fails to execute a script not starting with sharpbang.
	 * 3. it fails to execute a batch file if COMSPEC is set to a shell
	 *    incompatible with cmd.exe, such as /bin/sh.
	 * And ksh process scripts more well, so let ksh process scripts.
	 */
	errno = 0;
	if (!(fp = fopen(exec_name, "rb")))
		errno = ENOEXEC;

	if (!errno && fread(sign, 1, sizeof(sign), fp) != sizeof(sign))
		errno = ENOEXEC;

	if (fp && fclose(fp))
		errno = ENOEXEC;

	if (!errno &&
	    !((sign[0] == 'M' && sign[1] == 'Z') ||
	      (sign[0] == 'N' && sign[1] == 'E') ||
	      (sign[0] == 'L' && sign[1] == 'X')))
		errno = ENOEXEC;

	if (errno == ENOEXEC)
		return (-1);

	rsp_name_arg = make_response_file(argv);

	if (rsp_name_arg) {
		rsp_argv[0] = argv[0];
		rsp_argv[1] = rsp_name_arg;
		rsp_argv[2] = NULL;

		argv = rsp_argv;
	}

	pid = spawnve(P_NOWAIT, exec_name, argv, envp);

	afree(rsp_name_arg, ATEMP);

	if (pid == -1) {
		cleanup_temps();

		return (-1);
	}

	/* close all opened handles */
	for (fd = 0; fd < NUFILE; fd++) {
		if (fcntl(fd, F_GETFD) == -1)
			continue;

		close(fd);
	}

	while ((rc = waitpid(pid, &status, 0)) < 0 && errno == EINTR)
		/* nothing */;

	cleanup_temps();

	/* Is this possible? And is this right? */
	if (rc == -1)
		return (-1);

	if (WIFSIGNALED(status))
		_exit(ksh_sigmask(WTERMSIG(status)));

	_exit(WEXITSTATUS(status));
}