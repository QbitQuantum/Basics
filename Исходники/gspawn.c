gboolean
g_spawn_command_line_sync (const gchar *command_line,
				gchar **standard_output,
				gchar **standard_error,
				gint *exit_status,
				GError **error)
{
#ifdef G_OS_WIN32
#else
	pid_t pid;
	gchar **argv;
	gint argc;
	int stdout_pipe [2] = { -1, -1 };
	int stderr_pipe [2] = { -1, -1 };
	int status;
	int res;
	
	if (!g_shell_parse_argv (command_line, &argc, &argv, error))
		return FALSE;

	if (standard_output && !create_pipe (stdout_pipe, error))
		return FALSE;

	if (standard_error && !create_pipe (stderr_pipe, error)) {
		if (standard_output) {
			CLOSE_PIPE (stdout_pipe);
		}
		return FALSE;
	}

	pid = fork ();
	if (pid == 0) {
		gint i;

		if (standard_output) {
			close (stdout_pipe [0]);
			dup2 (stdout_pipe [1], STDOUT_FILENO);
		}

		if (standard_error) {
			close (stderr_pipe [0]);
			dup2 (stderr_pipe [1], STDERR_FILENO);
		}
		for (i = getdtablesize () - 1; i >= 3; i--)
			close (i);

		/* G_SPAWN_SEARCH_PATH is always enabled for g_spawn_command_line_sync */
		if (!g_path_is_absolute (argv [0])) {
			gchar *arg0;

			arg0 = g_find_program_in_path (argv [0]);
			if (arg0 == NULL) {
				exit (1);
			}
			//g_free (argv [0]);
			argv [0] = arg0;
		}
		execv (argv [0], argv);
		exit (1); /* TODO: What now? */
	}

	g_strfreev (argv);
	if (standard_output)
		close (stdout_pipe [1]);

	if (standard_error)
		close (stderr_pipe [1]);

	if (standard_output || standard_error) {
		res = read_pipes (stdout_pipe [0], standard_output, stderr_pipe [0], standard_error, error);
		if (res) {
			waitpid (pid, &status, WNOHANG); /* avoid zombie */
			return FALSE;
		}
	}

	NO_INTR (res, waitpid (pid, &status, 0));

	/* TODO: What if error? */
	if (WIFEXITED (status) && exit_status) {
		*exit_status = WEXITSTATUS (status);
	}
#endif
	return TRUE;
}