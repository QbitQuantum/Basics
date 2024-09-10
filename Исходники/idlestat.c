static int execute(int argc, char *argv[], char *const envp[],
		   struct program_options *options)
{
	pid_t pid;
	int status;

	/* Nothing to execute, just wait an amount of time */
	if (!argc)
		return sleep(options->duration);

	pid = fork();
	if (pid < 0) {
		perror("fork");
		return -1;
	}

	if (pid == 0 && execvpe(argv[0], argv, envp)) {
		/* Forked child */
		perror("execvpe");
		exit(1);
	}

	if (pid) {

		struct sigaction s = {
			.sa_handler = sighandler,
			.sa_flags = SA_RESETHAND,
		};

		sigaddset(&s.sa_mask, SIGALRM);
		sigaction(SIGALRM, &s, NULL);
		alarm(options->duration);
	again:
		if (waitpid(pid, &status, 0) < 0) {
			if (errno == EINTR && sigalrm)
				kill(pid, SIGTERM);
			goto again;
		}

		if (WIFEXITED(status)) {
			/*
			 * Cancel the timer in case the program
			 * finished before the timeout
			 */
			alarm(0);
			return 0;
		}

		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGTERM)
			return 0;
	}

	return -1;
}