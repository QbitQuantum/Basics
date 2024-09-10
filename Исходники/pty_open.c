/* Run the given command (if specified), using the given descriptor as the
 * controlling terminal. */
static int
_pty_run_on_pty(int fd, gboolean login,
			  int stdin_fd, int stdout_fd, int stderr_fd, 
			  int ready_reader, int ready_writer,
			  char **env_add, const char *command, char **argv,
			  const char *directory)
{
	int i;
	char c;
	char **args, *arg;

#ifdef HAVE_STROPTS_H
	if (!ioctl (fd, I_FIND, "ptem") && ioctl (fd, I_PUSH, "ptem") == -1) {
		close (fd);
		_exit (0);
		return -1;
	}

	if (!ioctl (fd, I_FIND, "ldterm") && ioctl (fd, I_PUSH, "ldterm") == -1) {
		close (fd);
		_exit (0);
		return -1;
	}

	if (!ioctl (fd, I_FIND, "ttcompat") && ioctl (fd, I_PUSH, "ttcompat") == -1) {
		perror ("ioctl (fd, I_PUSH, \"ttcompat\")");
		close (fd);
		_exit (0);
		return -1;
	}
#endif /* HAVE_STROPTS_H */

	/* Set any environment variables. */
	for (i = 0; (env_add != NULL) && (env_add[i] != NULL); i++) {
		if (putenv(g_strdup(env_add[i])) != 0) {
			g_warning("Error adding `%s' to environment, "
				    "continuing.", env_add[i]);
		}
	}

	/* Reset our signals -- our parent may have done any number of
	 * weird things to them. */
	_pty_reset_signal_handlers();

	/* Change to the requested directory. */
	if (directory != NULL) {
		i = chdir(directory);
	}

#ifdef HAVE_UTMP_H
	/* This sets stdin, stdout, stderr to the socket */	
	if (login && login_tty (fd) == -1) {
		g_printerr ("mount child process login_tty failed: %s\n", g_strerror (errno));
		return -1;
	}
#endif
	
	/* Signal to the parent that we've finished setting things up by
	 * sending an arbitrary byte over the status pipe and waiting for
	 * a response.  This synchronization step ensures that the pty is
	 * fully initialized before the parent process attempts to do anything
	 * with it, and is required on systems where additional setup, beyond
	 * merely opening the device, is required.  This is at least the case
	 * on Solaris. */
	/* Initialize so valgrind doesn't complain */
	c = 0;
	n_write(ready_writer, &c, 1);
	fsync(ready_writer);
	n_read(ready_reader, &c, 1);
	close(ready_writer);
	if (ready_writer != ready_reader) {
		close(ready_reader);
	}

	/* If the caller provided a command, we can't go back, ever. */
	if (command != NULL) {
		/* Outta here. */
		if (argv != NULL) {
			for (i = 0; (argv[i] != NULL); i++) ;
			args = g_malloc0(sizeof(char*) * (i + 1));
			for (i = 0; (argv[i] != NULL); i++) {
				args[i] = g_strdup(argv[i]);
			}
			execvp(command, args);
		} else {
			arg = g_strdup(command);
			execlp(command, arg, NULL);
		} 

		/* Avoid calling any atexit() code. */
		_exit(0);
		g_assert_not_reached();
	}

	return 0;
}