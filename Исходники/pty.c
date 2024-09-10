/*
 * _vte_pty_start_helper:
 * @error: a location to store a #GError, or %NULL
 *
 * Starts the GNOME PTY helper process, if it is not already running.
 *
 * Returns: %TRUE if the helper was already started, or starting it succeeded,
 *   %FALSE on failure with @error filled in
 */
static gboolean
_vte_pty_start_helper(GError **error)
{
	int i, errsv;
        int tunnel = -1;
        int tmp[2] = { -1, -1 };

        if (_vte_pty_helper_started)
                return TRUE;

	/* Create a communication link for use with the helper. */
	tmp[0] = open("/dev/null", O_RDONLY);
	if (tmp[0] == -1) {
		goto failure;
	}
	tmp[1] = open("/dev/null", O_RDONLY);
	if (tmp[1] == -1) {
		goto failure;
	}
	if (_vte_pty_pipe_open(&_vte_pty_helper_tunnel, &tunnel) != 0) {
		goto failure;
	}
	close(tmp[0]);
	close(tmp[1]);
        tmp[0] = tmp[1] = -1;

	/* Now fork and start the helper. */
	_vte_pty_helper_pid = fork();
	if (_vte_pty_helper_pid == -1) {
		goto failure;
	}
	if (_vte_pty_helper_pid == 0) {
		/* Child.  Close descriptors.  No need to close all,
		 * gnome-pty-helper does that anyway. */
		for (i = 0; i < 3; i++) {
			close(i);
		}
		/* Reassign the socket pair to stdio. */
		dup2(tunnel, STDIN_FILENO);
		dup2(tunnel, STDOUT_FILENO);
		close(tunnel);
		close(_vte_pty_helper_tunnel);
		/* Exec our helper. */
		execl(LIBEXECDIR "/gnome-pty-helper",
		      "gnome-pty-helper", NULL);
		/* Bail. */
		_exit(1);
	}
	close(tunnel);
	atexit(_vte_pty_stop_helper);

        _vte_pty_helper_started = TRUE;
	return TRUE;

failure:
        errsv = errno;

        g_set_error(error, VTE_PTY_ERROR,
                    VTE_PTY_ERROR_PTY_HELPER_FAILED,
                    "Failed to start gnome-pty-helper: %s",
                    g_strerror (errsv));

        if (tmp[0] != -1)
                close(tmp[0]);
        if (tmp[1] != -1)
                close(tmp[1]);
        if (tunnel != -1)
                close(tunnel);
        if (_vte_pty_helper_tunnel != -1)
                close(_vte_pty_helper_tunnel);

        _vte_pty_helper_pid = -1;
        _vte_pty_helper_tunnel = -1;

        errno = errsv;
        return FALSE;
}