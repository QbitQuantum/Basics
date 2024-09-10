/**
 * Daemonizes the current process.
 *
 * @param directory We will chdir() to this directory. A value of NULL
 *                  implies the root directory.
 */
int
compat_daemonize(const char *directory)
{
#ifndef MINGW32	/* FIXME MINGW32 */
	pid_t pid;
	int i;

	if (!directory) {
		directory = "/";
	}

	for (i = 0; i < 2; i++) {
		/* A handler for SIGCHLD should already be installed. */

		fflush(NULL);
		pid = fork();
		if ((pid_t) -1 == pid) {
			g_warning("fork() failed: %s", g_strerror(errno));
			return -1;
		}

		if (pid) {
			_exit(0);
			/* NOTREACHED */
			return -1;
		}

		/* Create a new session after the first fork() */
		if (0 == i && (pid_t) -1 == setsid()) {
			g_warning("setsid() failed: %s", g_strerror(errno));
			return -1;
		}
	}

	pid = getpid();
	if (setpgid(0, pid)) {
		g_warning("setpgid(0, %lu) failed: %s",
				(unsigned long) pid, g_strerror(errno));
		return -1;
	}

	if (chdir(directory)) {
		g_warning("chdir(\"%s\") failed: %s", directory, g_strerror(errno));
		return -1;
	}

	/*
	 * Make sure we don't create any files with an s-bit set or
	 * a world-writeable file.
	 */
	umask(umask(0) | S_IWOTH | S_ISUID | S_ISGID);

	/*
	 * Close all standard streams.
	 */

	if (!freopen("/dev/null", "r", stdin)) {
		g_warning("freopen() failed for stdin");
		return -1;
	}
	if (!freopen("/dev/null", "w", stdout)) {
		g_warning("freopen() failed for stdout");
		return -1;
	}
	if (!freopen("/dev/null", "w", stderr)) {
		g_warning("freopen() failed for stderr");
		return -1;
	}
#endif	/* !MINGW32 */
	return 0;
}