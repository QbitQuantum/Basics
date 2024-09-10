static void process_exec(PROCESS_REC *rec, const char *cmd)
{
	const char *shell_args[4] = { "/bin/sh", "-c", NULL, NULL };
        char **args;
	int in[2], out[2];
        int n;

	if (pipe(in) == -1)
                return;
	if (pipe(out) == -1)
		return;

	shell_args[2] = cmd;
	rec->pid = fork();
	if (rec->pid == -1) {
                /* error */
		close(in[0]); close(in[1]);
                close(out[0]); close(out[1]);
		return;
	}

	if (rec->pid != 0) {
		/* parent process */
                GIOChannel *outio = g_io_channel_unix_new(in[1]);

		rec->in = g_io_channel_unix_new(out[0]);
		rec->out = net_sendbuffer_create(outio, 0);

                close(out[1]);
		close(in[0]);
		pidwait_add(rec->pid);
                return;
	}

	/* child process, try to clean up everything */
	setsid();
	setuid(getuid());
	setgid(getgid());
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_DFL);

	putenv("TERM=tty");

	/* set stdin, stdout and stderr */
        dup2(in[0], STDIN_FILENO);
        dup2(out[1], STDOUT_FILENO);
	dup2(out[1], STDERR_FILENO);

        /* don't let child see our files */
	for (n = 3; n < 256; n++)
                close(n);

	if (rec->shell) {
		execvp(shell_args[0], (char **) shell_args);

		fprintf(stderr, "Exec: /bin/sh: %s\n", g_strerror(errno));
	} else {
		args = g_strsplit(cmd, " ", -1);
                execvp(args[0], args);

		fprintf(stderr, "Exec: %s: %s\n", args[0], g_strerror(errno));
	}

	_exit(-1);
}