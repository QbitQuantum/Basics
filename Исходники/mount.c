static int
exec_mountprog(const char *name, const char *execname, char *const argv[])
{
	pid_t pid;
	int status;

	switch (pid = fork()) {
	case -1:				/* Error. */
		warn("fork");
		exit (1);
	case 0:					/* Child. */
		/* Go find an executable. */
		execvP(execname, _PATH_SYSPATH, argv);
		if (errno == ENOENT) {
			warn("exec %s not found", execname);
			if (execname[0] != '/') {
				warnx("in path: %s", _PATH_SYSPATH);
			}
		}
		exit(1);
	default:				/* Parent. */
		if (waitpid(pid, &status, 0) < 0) {
			warn("waitpid");
			return (1);
		}

		if (WIFEXITED(status)) {
			if (WEXITSTATUS(status) != 0)
				return (WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			warnx("%s: %s", name, sys_siglist[WTERMSIG(status)]);
			return (1);
		}
		break;
	}

	return (0);
}