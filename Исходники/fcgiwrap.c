static void handle_fcgi_request(void)
{
	int pipe_in[2];
	int pipe_out[2];
	int pipe_err[2];
	char *filename;
	char *last_slash;
	char *p;
	pid_t pid;

	struct fcgi_context fc;

	if (pipe(pipe_in) < 0) goto err_pipein;
	if (pipe(pipe_out) < 0) goto err_pipeout;
	if (pipe(pipe_err) < 0) goto err_pipeerr;

	switch((pid = fork())) {
		case -1:
			goto err_fork;

		case 0: /* child */
			close(pipe_in[1]);
			close(pipe_out[0]);
			close(pipe_err[0]);

			dup2(pipe_in[0], 0);
			dup2(pipe_out[1], 1);
			dup2(pipe_err[1], 2);

			close(pipe_in[0]);
			close(pipe_out[1]);
			close(pipe_err[1]);

			close(FCGI_fileno(FCGI_stdout));

			signal(SIGCHLD, SIG_DFL);
			signal(SIGPIPE, SIG_DFL);

			filename = get_cgi_filename();
			inherit_environment();
			if (!filename)
				cgi_error("403 Forbidden", "Cannot get script name, are DOCUMENT_ROOT and SCRIPT_NAME (or SCRIPT_FILENAME) set and is the script executable?", NULL);

			if (!is_allowed_program(filename))
				cgi_error("403 Forbidden", "The given script is not allowed to execute", filename);

			p = getenv("FCGI_CHDIR");
			if (p == NULL) {
				last_slash = strrchr(filename, '/');
				if (!last_slash)
					cgi_error("403 Forbidden", "Script name must be a fully qualified path", filename);

				*last_slash = 0;
				if (chdir(filename) < 0)
					cgi_error("403 Forbidden", "Cannot chdir to script directory", filename);

				*last_slash = '/';
			} else if (strcmp(p, "-") != 0) {
				if (chdir(p) < 0) {
					cgi_error("403 Forbidden", "Cannot chdir to FCGI_CHDIR directory", p);
				}
			}

			execl(filename, filename, (void *)NULL);
			cgi_error("502 Bad Gateway", "Cannot execute script", filename);

		default: /* parent */
			close(pipe_in[0]);
			close(pipe_out[1]);
			close(pipe_err[1]);

			fc.fd_stdin = pipe_in[1];
			fc.fd_stdout = pipe_out[0];
			fc.fd_stderr = pipe_err[0];
			fc.reply_state = REPLY_STATE_INIT;
			fc.cgi_pid = pid;

			fcgi_pass(&fc);
	}
	return;

err_fork:
	close(pipe_err[0]);
	close(pipe_err[1]);

err_pipeerr:
	close(pipe_out[0]);
	close(pipe_out[1]);

err_pipeout:
	close(pipe_in[0]);
	close(pipe_in[1]);

err_pipein:

	FCGI_puts("Status: 502 Bad Gateway\nContent-type: text/plain\n");
	FCGI_puts("System error");
}