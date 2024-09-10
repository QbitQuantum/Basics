/**
 * mate_execute_async_with_env_fds:
 * @dir: Directory in which child should be executed, or %NULL for current
 *       directory
 * @argc: Number of arguments
 * @argv: Argument vector to exec child
 * @envc: Number of environment slots
 * @envv: Environment vector
 * @close_fds: If %TRUE will close all fds but 0,1, and 2
 *
 * Description:  Like mate_execute_async_with_env() but has a flag to
 * decide whether or not to close fd's
 *
 * Returns: the process id, or %-1 on error.
 **/
int mate_execute_async_with_env_fds (const char* dir, int argc, char* const argv[], int envc, char* const envv[], gboolean close_fds)
{
	#ifndef G_OS_WIN32
		int parent_comm_pipes[2], child_comm_pipes[2];
		int child_errno, itmp, i, open_max;
		gssize res;
		char** cpargv;
		pid_t child_pid, immediate_child_pid;

		if(pipe(parent_comm_pipes))
			return -1;

		child_pid = immediate_child_pid = fork();

		switch (child_pid)
		{
			case -1:
				close(parent_comm_pipes[0]);
				close(parent_comm_pipes[1]);
				return -1;

			case 0: /* START PROCESS 1: child */
				child_pid = -1;
				res = pipe(child_comm_pipes);
				close(parent_comm_pipes[0]);

				if (!res)
					child_pid = fork();

				switch (child_pid)
				{
					case -1:
						itmp = errno;
						child_pid = -1; /* simplify parent code */
						write(parent_comm_pipes[1], &child_pid, sizeof(child_pid));
						write(parent_comm_pipes[1], &itmp, sizeof(itmp));
						close(child_comm_pipes[0]);
						close(child_comm_pipes[1]);
						_exit(0);
						break;      /* END PROCESS 1: monkey in the middle dies */

					default:
						{
							char buf[16];

							close(child_comm_pipes[1]);

							while ((res = safe_read(child_comm_pipes[0], buf, sizeof(buf))) > 0)
								write(parent_comm_pipes[1], buf, res);

							close(child_comm_pipes[0]);
							_exit(0); /* END PROCESS 1: monkey in the middle dies */
						}
						break;

					case 0:                 /* START PROCESS 2: child of child */
						close(parent_comm_pipes[1]);
						/* pre-exec setup */
						close (child_comm_pipes[0]);
						set_cloexec (child_comm_pipes[1]);
						child_pid = getpid();
						res = write(child_comm_pipes[1], &child_pid, sizeof(child_pid));

						if (envv)
						{
							for (itmp = 0; itmp < envc; itmp++)
								putenv(envv[itmp]);
						}

						if (dir)
						{
							if (chdir(dir))
								_exit(-1);
						}

						cpargv = g_alloca((argc + 1) * sizeof(char *));
						memcpy(cpargv, argv, argc * sizeof(char *));
						cpargv[argc] = NULL;

						if(close_fds)
						{
							int stdinfd;
							/* Close all file descriptors but stdin stdout and stderr */
							open_max = sysconf(_SC_OPEN_MAX);

							for (i = 3; i < open_max; i++)
								set_cloexec (i);

							if(child_comm_pipes[1] != 0)
							{
								close(0);
								/* Open stdin as being nothingness, so that if someone tries to
								read from this they don't hang up the whole MATE session. BUGFIX #1548 */
								stdinfd = open("/dev/null", O_RDONLY);
								g_assert(stdinfd >= 0);

								if (stdinfd != 0)
								{
									dup2(stdinfd, 0);
									close(stdinfd);
								}
							}
						}

						setsid();
						signal(SIGPIPE, SIG_DFL);
						/* doit */
						execvp(cpargv[0], cpargv);

						/* failed */
						itmp = errno;
						write(child_comm_pipes[1], &itmp, sizeof(itmp));
						_exit(1);
						break;      /* END PROCESS 2 */
				}

				break;

			default: /* parent process */
				/* do nothing */
				break;
		}

		close(parent_comm_pipes[1]);

		res = safe_read(parent_comm_pipes[0], &child_pid, sizeof(child_pid));

		if (res != sizeof(child_pid))
		{
			g_message("res is %ld instead of %d", (long) res, (int) sizeof(child_pid));
			child_pid = -1; /* really weird things happened */
		}
		else if (safe_read(parent_comm_pipes[0], &child_errno, sizeof(child_errno)) == sizeof(child_errno))
		{
			errno = child_errno;
			child_pid = -1;
		}

		/* do this after the read's in case some OS's handle blocking on pipe writes
		 * differently
		 */
		while ((waitpid(immediate_child_pid, &itmp, 0)== -1) && (errno == EINTR))
			; /* eat zombies */

		close(parent_comm_pipes[0]);

		if(child_pid < 0)
			g_message("mate_execute_async_with_env_fds: returning %d", child_pid);

		return child_pid;
	#else /* !G_OS_WIN32 */
		/* FIXME: Implement if needed */
		g_warning("mate_execute_async_with_env_fds: Not implemented");

		return -1;
	#endif /* G_OS_WIN32 */
}