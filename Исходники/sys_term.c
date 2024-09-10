void
start_login(char *host, int autologin, char *name)
{
	char **argv;
#define	TABBUFSIZ	512
	char	defent[TABBUFSIZ];
	char	defstrs[TABBUFSIZ];
#undef	TABBUFSIZ
	const char *loginprog = NULL;
	extern struct sockaddr_storage from;
	char buf[sizeof(from) * 4 + 1];

	scrub_env();

	/*
	 * -a : pass on the address of the host.
	 * -h : pass on name of host.
	 *	WARNING:  -h and -a are accepted by login
	 *	if and only if getuid() == 0.
	 * -p : don't clobber the environment (so terminal type stays set).
	 *
	 * -f : force this login, he has already been authenticated
	 */
	argv = addarg(0, "login");

	argv = addarg(argv, "-a");
	(void)strvisx(buf, (const char *)(const void *)&from, sizeof(from),
	    VIS_WHITE);
	argv = addarg(argv, buf);

	argv = addarg(argv, "-h");
	argv = addarg(argv, host);

	argv = addarg(argv, "-p");
#ifdef	LINEMODE
	/*
	 * Set the environment variable "LINEMODE" to either
	 * "real" or "kludge" if we are operating in either
	 * real or kludge linemode.
	 */
	if (lmodetype == REAL_LINEMODE)
		setenv("LINEMODE", "real", 1);
# ifdef KLUDGELINEMODE
	else if (lmodetype == KLUDGE_LINEMODE || lmodetype == KLUDGE_OK)
		setenv("LINEMODE", "kludge", 1);
# endif
#endif
#ifdef SECURELOGIN
	/*
	 * don't worry about the -f that might get sent.
	 * A -s is supposed to override it anyhow.
	 */
	if (require_secure_login)
		argv = addarg(argv, "-s");
#endif
#ifdef AUTHENTICATION
	if (auth_level >= 0 && autologin == AUTH_VALID) {
		argv = addarg(argv, "-f");
		argv = addarg(argv, "--");
		argv = addarg(argv, name);
	} else
#endif
	if (getenv("USER")) {
		argv = addarg(argv, "--");
		argv = addarg(argv, getenv("USER"));
		/*
		 * Assume that login will set the USER variable
		 * correctly.  For SysV systems, this means that
		 * USER will no longer be set, just LOGNAME by
		 * login.  (The problem is that if the auto-login
		 * fails, and the user then specifies a different
		 * account name, he can get logged in with both
		 * LOGNAME and USER in his environment, but the
		 * USER value will be wrong.
		 */
		unsetenv("USER");
	}
        if (getent(defent, gettyname) == 1) {
                char *cp = defstrs;

                loginprog = getstr("lo", &cp);
        }
        if (loginprog == NULL)
                loginprog = _PATH_LOGIN;
	closelog();
	/*
	 * This sleep(1) is in here so that telnetd can
	 * finish up with the tty.  There's a race condition
	 * the login banner message gets lost...
	 */
	sleep(1);
        execv(loginprog, argv);

        syslog(LOG_ERR, "%s: %m", loginprog);
        fatalperror(net, loginprog);
	/*NOTREACHED*/
}