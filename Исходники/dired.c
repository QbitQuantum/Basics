/* ARGSUSED */
int
d_shell_command(int f, int n)
{
#ifdef MONA
  ewprintf("shell command is not supported");
  return (FALSE);
#else
	char	 command[512], fname[MAXPATHLEN], buf[BUFSIZ], *bufp, *cp;
	int	 infd, fds[2];
	pid_t	 pid;
	struct	 sigaction olda, newa;
	struct buffer	*bp;
	struct mgwin	*wp;
	FILE	*fin;

	bp = bfind("*Shell Command Output*", TRUE);
	if (bclear(bp) != TRUE)
		return (ABORT);

	if (d_makename(curwp->w_dotp, fname, sizeof(fname)) != FALSE) {
		ewprintf("bad line");
		return (ABORT);
	}

	command[0] = '\0';
	if ((bufp = eread("! on %s: ", command, sizeof(command), EFNEW,
	    basename(fname))) == NULL)
		return (ABORT);
	infd = open(fname, O_RDONLY);
	if (infd == -1) {
		ewprintf("Can't open input file : %s", strerror(errno));
		return (FALSE);
	}
	if (pipe(fds) == -1) {
		ewprintf("Can't create pipe : %s", strerror(errno));
		close(infd);
		return (FALSE);
	}

	newa.sa_handler = reaper;
	newa.sa_flags = 0;
	if (sigaction(SIGCHLD, &newa, &olda) == -1) {
		close(infd);
		close(fds[0]);
		close(fds[1]);
		return (ABORT);
	}
	pid = fork();
	switch (pid) {
	case -1:
		ewprintf("Can't fork");
		return (ABORT);
	case 0:
		close(fds[0]);
		dup2(infd, STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		dup2(fds[1], STDERR_FILENO);
		execl("/bin/sh", "sh", "-c", bufp, (char *)NULL);
		exit(1);
		break;
	default:
		close(infd);
		close(fds[1]);
		fin = fdopen(fds[0], "r");
		if (fin == NULL)	/* "r" is surely a valid mode! */
			panic("can't happen");
		while (fgets(buf, sizeof(buf), fin) != NULL) {
			cp = strrchr(buf, '\n');
			if (cp == NULL && !feof(fin)) {	/* too long a line */
				int c;
				addlinef(bp, "%s...", buf);
				while ((c = getc(fin)) != EOF && c != '\n')
					;
				continue;
			} else if (cp)
				*cp = '\0';
			addline(bp, buf);
		}
		fclose(fin);
		close(fds[0]);
		break;
	}
	wp = popbuf(bp);
	if (wp == NULL)
		return (ABORT);	/* XXX - free the buffer?? */
	curwp = wp;
	curbp = wp->w_bufp;
	if (sigaction(SIGCHLD, &olda, NULL) == -1)
		ewprintf("Warning, couldn't reset previous signal handler");
	return (TRUE);
#endif
}