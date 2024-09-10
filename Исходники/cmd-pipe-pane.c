enum cmd_retval
cmd_pipe_pane_exec(struct cmd *self, struct cmd_q *cmdq)
{
	struct args		*args = self->args;
	struct client		*c;
	struct window_pane	*wp;
	char			*command;
	int			 old_fd, pipe_fd[2], null_fd;

	if (cmd_find_pane(cmdq, args_get(args, 't'), NULL, &wp) == NULL)
		return (CMD_RETURN_ERROR);
	c = cmd_find_client(cmdq, NULL, 1);

	/* Destroy the old pipe. */
	old_fd = wp->pipe_fd;
	if (wp->pipe_fd != -1) {
		bufferevent_free(wp->pipe_event);
		close(wp->pipe_fd);
		wp->pipe_fd = -1;
	}

	/* If no pipe command, that is enough. */
	if (args->argc == 0 || *args->argv[0] == '\0')
		return (CMD_RETURN_NORMAL);

	/*
	 * With -o, only open the new pipe if there was no previous one. This
	 * allows a pipe to be toggled with a single key, for example:
	 *
	 *	bind ^p pipep -o 'cat >>~/output'
	 */
	if (args_has(self->args, 'o') && old_fd != -1)
		return (CMD_RETURN_NORMAL);

	/* Open the new pipe. */
	if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, pipe_fd) != 0) {
		cmdq_error(cmdq, "socketpair error: %s", strerror(errno));
		return (CMD_RETURN_ERROR);
	}

	/* Fork the child. */
	switch (fork()) {
	case -1:
		cmdq_error(cmdq, "fork error: %s", strerror(errno));
		return (CMD_RETURN_ERROR);
	case 0:
		/* Child process. */
		close(pipe_fd[0]);
		clear_signals(1);

		if (dup2(pipe_fd[1], STDIN_FILENO) == -1)
			_exit(1);
		if (pipe_fd[1] != STDIN_FILENO)
			close(pipe_fd[1]);

		null_fd = open(_PATH_DEVNULL, O_WRONLY, 0);
		if (dup2(null_fd, STDOUT_FILENO) == -1)
			_exit(1);
		if (dup2(null_fd, STDERR_FILENO) == -1)
			_exit(1);
		if (null_fd != STDOUT_FILENO && null_fd != STDERR_FILENO)
			close(null_fd);

		closefrom(STDERR_FILENO + 1);

		command = status_replace(
		    c, NULL, NULL, NULL, args->argv[0], time(NULL), 0);
		execl(_PATH_BSHELL, "sh", "-c", command, (char *) NULL);
		_exit(1);
	default:
		/* Parent process. */
		close(pipe_fd[1]);

		wp->pipe_fd = pipe_fd[0];
		wp->pipe_off = EVBUFFER_LENGTH(wp->event->input);

		wp->pipe_event = bufferevent_new(wp->pipe_fd,
		    NULL, NULL, cmd_pipe_pane_error_callback, wp);
		bufferevent_enable(wp->pipe_event, EV_WRITE);

		setblocking(wp->pipe_fd, 0);
		return (CMD_RETURN_NORMAL);
	}
}