static void
fork_and_print_environment (void)
{
	int status;
	pid_t pid;
	int fd, i;

	if (run_foreground) {
		print_environment (getpid ());
		return;
	}

	pid = fork ();

	if (pid != 0) {

		/* Here we are in the initial process */

		if (run_daemonized) {

			/* Initial process, waits for intermediate child */
			if (pid == -1)
				exit (1);

			waitpid (pid, &status, 0);
			if (WEXITSTATUS (status) != 0)
				exit (WEXITSTATUS (status));

		} else {
			/* Not double forking, we know the PID */
			print_environment (pid);
		}

		/* The initial process exits successfully */
		exit (0);
	}

	if (run_daemonized) {

		/* Double fork if need to daemonize properly */
		pid = fork ();

		if (pid != 0) {

			/* Here we are in the intermediate child process */

			/*
			 * This process exits, so that the final child will inherit
			 * init as parent to avoid zombies
			 */
			if (pid == -1)
				exit (1);

			/* We've done two forks. Now we know the PID */
			print_environment (pid);

			/* The intermediate child exits */
			exit (0);
		}

	}

	/* Here we are in the resulting daemon or background process. */

	for (i = 0; i < 3; ++i) {
		fd = open ("/dev/null", O_RDONLY);
		sane_dup2 (fd, i);
		close (fd);
	}
}