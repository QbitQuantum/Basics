/*
 * Runs command in a subprocess. Returns pid on success and a FILE* to the
 * subprocess' stdout or 0 on failure.
 * NB. "command" is only used for logging.
 */
static pid_t
subprocess(const char *tag, struct passwd *pw, const char *command,
    int ac, char **av, FILE **child)
{
	FILE *f;
	struct stat st;
	int devnull, p[2], i;
	pid_t pid;
	char *cp, errmsg[512];
	u_int envsize;
	char **child_env;

	*child = NULL;

	debug3("%s: %s command \"%s\" running as %s", __func__,
	    tag, command, pw->pw_name);

	/* Verify the path exists and is safe-ish to execute */
	if (*av[0] != '/') {
		error("%s path is not absolute", tag);
		return 0;
	}
	temporarily_use_uid(pw);
	if (stat(av[0], &st) < 0) {
		error("Could not stat %s \"%s\": %s", tag,
		    av[0], strerror(errno));
		restore_uid();
		return 0;
	}
	if (auth_secure_path(av[0], &st, NULL, 0,
	    errmsg, sizeof(errmsg)) != 0) {
		error("Unsafe %s \"%s\": %s", tag, av[0], errmsg);
		restore_uid();
		return 0;
	}

	/*
	 * Run the command; stderr is left in place, stdout is the
	 * authorized_keys output.
	 */
	if (pipe(p) != 0) {
		error("%s: pipe: %s", tag, strerror(errno));
		restore_uid();
		return 0;
	}

	/*
	 * Don't want to call this in the child, where it can fatal() and
	 * run cleanup_exit() code.
	 */
	restore_uid();

	switch ((pid = fork())) {
	case -1: /* error */
		error("%s: fork: %s", tag, strerror(errno));
		close(p[0]);
		close(p[1]);
		return 0;
	case 0: /* child */
		/* Prepare a minimal environment for the child. */
		envsize = 5;
		child_env = xcalloc(sizeof(*child_env), envsize);
		child_set_env(&child_env, &envsize, "PATH", _PATH_STDPATH);
		child_set_env(&child_env, &envsize, "USER", pw->pw_name);
		child_set_env(&child_env, &envsize, "LOGNAME", pw->pw_name);
		child_set_env(&child_env, &envsize, "HOME", pw->pw_dir);
		if ((cp = getenv("LANG")) != NULL)
			child_set_env(&child_env, &envsize, "LANG", cp);

		for (i = 0; i < NSIG; i++)
			signal(i, SIG_DFL);

		if ((devnull = open(_PATH_DEVNULL, O_RDWR)) == -1) {
			error("%s: open %s: %s", tag, _PATH_DEVNULL,
			    strerror(errno));
			_exit(1);
		}
		/* Keep stderr around a while longer to catch errors */
		if (dup2(devnull, STDIN_FILENO) == -1 ||
		    dup2(p[1], STDOUT_FILENO) == -1) {
			error("%s: dup2: %s", tag, strerror(errno));
			_exit(1);
		}
		closefrom(STDERR_FILENO + 1);

		/* Don't use permanently_set_uid() here to avoid fatal() */
		if (setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) != 0) {
			error("%s: setresgid %u: %s", tag, (u_int)pw->pw_gid,
			    strerror(errno));
			_exit(1);
		}
		if (setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid) != 0) {
			error("%s: setresuid %u: %s", tag, (u_int)pw->pw_uid,
			    strerror(errno));
			_exit(1);
		}
		/* stdin is pointed to /dev/null at this point */
		if (dup2(STDIN_FILENO, STDERR_FILENO) == -1) {
			error("%s: dup2: %s", tag, strerror(errno));
			_exit(1);
		}

		execve(av[0], av, child_env);
		error("%s exec \"%s\": %s", tag, command, strerror(errno));
		_exit(127);
	default: /* parent */
		break;
	}

	close(p[1]);
	if ((f = fdopen(p[0], "r")) == NULL) {
		error("%s: fdopen: %s", tag, strerror(errno));
		close(p[0]);
		/* Don't leave zombie child */
		kill(pid, SIGTERM);
		while (waitpid(pid, NULL, 0) == -1 && errno == EINTR)
			;
		return 0;
	}
	/* Success */
	debug3("%s: %s pid %ld", __func__, tag, (long)pid);
	*child = f;
	return pid;
}