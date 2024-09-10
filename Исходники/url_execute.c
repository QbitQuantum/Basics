/*
 * popen_with_stderr
 *
 * standard popen doesn't redirect stderr from the child process.
 * we need stderr in order to display the error that child process
 * encountered and show it to the user. This is, therefore, a wrapper
 * around a set of file descriptor redirections and a fork.
 *
 * if 'forwrite' is set then we set the data pipe write side on the
 * parent. otherwise, we set the read side on the parent.
 */
int
popen_with_stderr(int *pipes, const char *exe, bool forwrite)
{
	int data[2];	/* pipe to send data child <--> parent */
	int err[2];		/* pipe to send errors child --> parent */
	int pid = -1;

	const int READ = 0;
	const int WRITE = 1;

	if (pgpipe(data) < 0)
		return -1;

	if (pgpipe(err) < 0)
	{
		close(data[READ]);
		close(data[WRITE]);
		return -1;
	}
#ifndef WIN32

	pid = fork();

	if (pid > 0) /* parent */
	{

		if (forwrite)
		{
			/* parent writes to child */
			close(data[READ]);
			pipes[EXEC_DATA_P] = data[WRITE];
		}
		else
		{
			/* parent reads from child */
			close(data[WRITE]);
			pipes[EXEC_DATA_P] = data[READ];
		}

		close(err[WRITE]);
		pipes[EXEC_ERR_P] = err[READ];

		return pid;
	}
	else if (pid == 0) /* child */
	{

		/*
		 * set up the data pipe
		 */
		if (forwrite)
		{
			close(data[WRITE]);
			close(fileno(stdin));

			/* assign pipes to parent to stdin */
			if (dup2(data[READ], fileno(stdin)) < 0)
			{
				perror("dup2 error");
				exit(EXIT_FAILURE);
			}

			/* no longer needed after the duplication */
			close(data[READ]);
		}
		else
		{
			close(data[READ]);
			close(fileno(stdout));

			/* assign pipes to parent to stdout */
			if (dup2(data[WRITE], fileno(stdout)) < 0)
			{
				perror("dup2 error");
				exit(EXIT_FAILURE);
			}

			/* no longer needed after the duplication */
			close(data[WRITE]);
		}

		/*
		 * now set up the error pipe
		 */
		close(err[READ]);
		close(fileno(stderr));

		if (dup2(err[WRITE], fileno(stderr)) < 0)
		{
			if(forwrite)
				close(data[WRITE]);
			else
				close(data[READ]);

			perror("dup2 error");
			exit(EXIT_FAILURE);
		}

		close(err[WRITE]);

		/* go ahead and execute the user command */
		execl("/bin/sh", "sh", "-c", exe, NULL);

		/* if we're here an error occurred */
		exit(EXIT_FAILURE);
	}
	else
	{
		if(forwrite)
		{
			close(data[WRITE]);
			close(data[READ]);
		}
		else
		{
			close(data[READ]);
			close(data[WRITE]);
		}
		close(err[READ]);
		close(err[WRITE]);

		return -1;
	}
#endif

	return pid;
}