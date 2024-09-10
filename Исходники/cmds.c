char *
expand(char name[])
{
	static char xname[BUFSIZ];
	char cmdbuf[BUFSIZ];
	int pid, l;
	char *cp, *Shell;
	int s, pivec[2];

	if (!anyof(name, "~{[*?$`'\"\\"))
		return (name);
	if (pipe(pivec) < 0) {
		perror("pipe");
		return (name);
	}
	(void) snprintf(cmdbuf, sizeof (cmdbuf), "echo %s", name);
	if ((pid = vfork()) == 0) {
		userperm();
		Shell = value(SHELL);
		if (Shell == NOSTR)
			Shell = "/bin/sh";
		(void) close(pivec[0]);
		(void) close(1);
		(void) dup(pivec[1]);
		(void) close(pivec[1]);
		(void) close(2);
		(void) execl(Shell, Shell, "-c", cmdbuf, 0);
		_exit(1);
	}
	if (pid == -1) {
		perror("fork");
		(void) close(pivec[0]);
		(void) close(pivec[1]);
		return (NOSTR);
	}
	(void) close(pivec[1]);
	l = read(pivec[0], xname, BUFSIZ);
	(void) close(pivec[0]);
	while (wait(&s) != pid)
		;
	s &= 0377;
	if (s != 0 && s != SIGPIPE) {
		(void) fprintf(stderr, "\"Echo\" failed\n");
		return (NOSTR);
	}
	if (l < 0) {
		perror("read");
		return (NOSTR);
	}
	if (l == 0) {
		(void) fprintf(stderr, "\"%s\": No match\n", name);
		return (NOSTR);
	}
	if (l == BUFSIZ) {
		(void) fprintf(stderr, "Buffer overflow expanding \"%s\"\n",
		    name);
		return (NOSTR);
	}
	xname[l] = 0;
	for (cp = &xname[l-1]; *cp == '\n' && cp > xname; cp--)
		;
	*++cp = '\0';
	return (xname);
}