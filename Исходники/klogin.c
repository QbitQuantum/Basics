int
main(int argc, char **argv)
{
    char *namep;
    int pflag = 0, hflag = 0, t, f, c;
    int invalid, quietlog;
    FILE *nlfd;
    char *ttyn, *tty;
    int ldisc = 0, zero = 0, i;
    char **envnew;

#ifdef	AFS_AIX32_ENV
    /*
     * The following signal action for AIX is necessary so that in case of a
     * crash (i.e. core is generated) we can include the user's data section
     * in the core dump. Unfortunately, by default, only a partial core is
     * generated which, in many cases, isn't too useful.
     */
    struct sigaction nsa;

    sigemptyset(&nsa.sa_mask);
    nsa.sa_handler = SIG_DFL;
    nsa.sa_flags = SA_FULLDUMP;
    sigaction(SIGSEGV, &nsa, NULL);
#endif
    signal(SIGALRM, timedout);
    alarm(timeout);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    setpriority(PRIO_PROCESS, 0, 0);
    quota(Q_SETUID, 0, 0, 0);

    /* create a dummy user */
    memset(&nouser, 0, sizeof(nouser));
    nouser.pw_name = "";
    nouser.pw_passwd = "*";
    nouser.pw_dir = nouser.pw_shell = "";
    nouser.pw_uid = nouser.pw_gid = -1;

    /*
     * -p is used by getty to tell login not to destroy the environment
     * -r is used by rlogind to cause the autologin protocol;
     * -h is used by other servers to pass the name of the
     * remote host to login so that it may be placed in utmp and wtmp
     */
    while (argc > 1) {
	if (strcmp(argv[1], "-r") == 0) {
	    if (rflag || hflag) {
		printf("Only one of -r and -h allowed\n");
		exit(1);
	    }
	    rflag = 1;
	    usererr = doremotelogin(argv[2]);
	    SCPYN(utmp.ut_host, argv[2]);
	    argc -= 2;
	    argv += 2;
	    continue;
	}
	if (strcmp(argv[1], "-h") == 0 && getuid() == 0) {
	    if (rflag || hflag) {
		printf("Only one of -r and -h allowed\n");
		exit(1);
	    }
	    hflag = 1;
	    SCPYN(utmp.ut_host, argv[2]);
	    argc -= 2;
	    argv += 2;
	    continue;
	}
	if (strcmp(argv[1], "-p") == 0) {
	    argc--;
	    argv++;
	    pflag = 1;
	    continue;
	}
	break;
    }
    ioctl(0, TIOCLSET, &zero);
    ioctl(0, TIOCNXCL, 0);
    ioctl(0, FIONBIO, &zero);
    ioctl(0, FIOASYNC, &zero);
    ioctl(0, TIOCGETP, &ttyb);
    /*
     * If talking to an rlogin process,
     * propagate the terminal type and
     * baud rate across the network.
     */
    if (rflag)
	doremoteterm(term, &ttyb);
    ttyb.sg_erase = CERASE;
    ttyb.sg_kill = CKILL;
    ioctl(0, TIOCSLTC, &ltc);
    ioctl(0, TIOCSETC, &tc);
    ioctl(0, TIOCSETP, &ttyb);
    for (t = getdtablesize(); t > 2; t--)
	close(t);
    ttyn = ttyname(0);
    if (ttyn == (char *)0 || *ttyn == '\0')
	ttyn = "/dev/tty??";
    tty = strrchr(ttyn, '/');
    if (tty == NULL)
	tty = ttyn;
    else
	tty++;
    openlog("login", LOG_ODELAY, LOG_AUTH);
    t = 0;
    invalid = FALSE;
    do {
	ldisc = 0;
	ioctl(0, TIOCSETD, &ldisc);
	SCPYN(utmp.ut_name, "");
	/*
	 * Name specified, take it.
	 */
	if (argc > 1) {
	    SCPYN(utmp.ut_name, argv[1]);
	    argc = 0;
	}
	/*
	 * If remote login take given name,
	 * otherwise prompt user for something.
	 */
	if (rflag && !invalid)
	    SCPYN(utmp.ut_name, lusername);
	else
	    getloginname(&utmp);
	invalid = FALSE;
	if (!strcmp(pwd->pw_shell, "/bin/csh")) {
	    ldisc = NTTYDISC;
	    ioctl(0, TIOCSETD, &ldisc);
	}
	/*
	 * If no remote login authentication and
	 * a password exists for this user, prompt
	 * for one and verify it.
	 */
	if (usererr == -1 && *pwd->pw_passwd != '\0') {
#ifdef KAUTH
	    char password[BUFSIZ];
	    char *reason;
	    if (ka_UserReadPassword
		("Password:"******"Unable to login because %s,\n", reason);
		invalid = TRUE;
	    } else
		if (ka_UserAuthenticate
		    (pwd->pw_name, /*inst */ 0, /*realm */ 0, password,
		     /*sepag */ 1, &reason)) {
		printf("Unable to authenticate to AFS because %s.\n", reason);
		printf("  proceeding with local authentication... \n");
		/* try local login */
		namep = crypt(password, pwd->pw_passwd);
		if (strcmp(namep, pwd->pw_passwd))
		    invalid = TRUE;
	    }
#else
	    char *pp;
	    setpriority(PRIO_PROCESS, 0, -4);
	    pp = getpass("Password:"******"r")) != 0) {
	    while ((c = getc(nlfd)) != EOF)
		putchar(c);
	    fflush(stdout);
	    sleep(5);
	    exit(0);
	}
	/*
	 * If valid so far and root is logging in,
	 * see if root logins on this terminal are permitted.
	 */
	if (!invalid && pwd->pw_uid == 0 && !rootterm(tty)) {
	    if (utmp.ut_host[0])
		syslog(LOG_CRIT, "ROOT LOGIN REFUSED ON %s FROM %.*s", tty,
		       HMAX, utmp.ut_host);
	    else
		syslog(LOG_CRIT, "ROOT LOGIN REFUSED ON %s", tty);
	    invalid = TRUE;
	}
	if (invalid) {
	    printf("Login incorrect\n");
	    if (++t >= 5) {
		if (utmp.ut_host[0])
		    syslog(LOG_CRIT,
			   "REPEATED LOGIN FAILURES ON %s FROM %.*s, %.*s",
			   tty, HMAX, utmp.ut_host, NMAX, utmp.ut_name);
		else
		    syslog(LOG_CRIT, "REPEATED LOGIN FAILURES ON %s, %.*s",
			   tty, NMAX, utmp.ut_name);
		ioctl(0, TIOCHPCL, NULL);
		close(0), close(1), close(2);
		sleep(10);
		exit(1);
	    }
	}
	if (*pwd->pw_shell == '\0')
	    pwd->pw_shell = "/bin/sh";
	if (chdir(pwd->pw_dir) < 0 && !invalid) {
	    if (chdir("/") < 0) {
		printf("No directory!\n");
		invalid = TRUE;
	    } else {
		printf("No directory! %s\n", "Logging in with home=/");
		pwd->pw_dir = "/";
	    }
	}
	/*
	 * Remote login invalid must have been because
	 * of a restriction of some sort, no extra chances.
	 */
	if (!usererr && invalid)
	    exit(1);
    } while (invalid);
/* committed to login turn off timeout */
    alarm(0);

    if (quota(Q_SETUID, pwd->pw_uid, 0, 0) < 0 && errno != EINVAL) {
	if (errno == EUSERS)
	    printf("%s.\n%s.\n", "Too many users logged on already",
		   "Try again later");
	else if (errno == EPROCLIM)
	    printf("You have too many processes running.\n");
	else
	    perror("quota (Q_SETUID)");
	sleep(5);
	exit(0);
    }
    time(&utmp.ut_time);
    t = ttyslot();
    if (t > 0 && (f = open("/etc/utmp", O_WRONLY)) >= 0) {
	lseek(f, (afs_int32) (t * sizeof(utmp)), 0);
	SCPYN(utmp.ut_line, tty);
	write(f, (char *)&utmp, sizeof(utmp));
	close(f);
    }
    if ((f = open("/usr/adm/wtmp", O_WRONLY | O_APPEND)) >= 0) {
	write(f, (char *)&utmp, sizeof(utmp));
	close(f);
    }
    quietlog = access(qlog, F_OK) == 0;
    if ((f = open(lastlog, O_RDWR)) >= 0) {
	struct lastlog ll;

	lseek(f, (afs_int32) pwd->pw_uid * sizeof(struct lastlog), 0);
	if (read(f, (char *)&ll, sizeof ll) == sizeof ll && ll.ll_time != 0
	    && !quietlog) {
	    printf("Last login: %.*s ", 24 - 5, (char *)ctime(&ll.ll_time));
	    if (*ll.ll_host != '\0')
		printf("from %.*s\n", sizeof(ll.ll_host), ll.ll_host);
	    else
		printf("on %.*s\n", sizeof(ll.ll_line), ll.ll_line);
	}
	lseek(f, (afs_int32) pwd->pw_uid * sizeof(struct lastlog), 0);
	time(&ll.ll_time);
	SCPYN(ll.ll_line, tty);
	SCPYN(ll.ll_host, utmp.ut_host);
	write(f, (char *)&ll, sizeof ll);
	close(f);
    }
    chown(ttyn, pwd->pw_uid, TTYGID(pwd->pw_gid));
    if (!hflag && !rflag)	/* XXX */
	ioctl(0, TIOCSWINSZ, &win);
    chmod(ttyn, 0620);
    setgid(pwd->pw_gid);
    strncpy(name, utmp.ut_name, NMAX);
    name[NMAX] = '\0';
    initgroups(name, pwd->pw_gid);
    quota(Q_DOWARN, pwd->pw_uid, (dev_t) - 1, 0);
    setuid(pwd->pw_uid);
    /* destroy environment unless user has asked to preserve it */
    if (!pflag)
	environ = envinit;

    /* set up environment, this time without destruction */
    /* copy the environment before setenving */
    i = 0;
    while (environ[i] != NULL)
	i++;
    envnew = malloc(sizeof(char *) * (i + 1));
    for (; i >= 0; i--)
	envnew[i] = environ[i];
    environ = envnew;

    setenv("HOME=", pwd->pw_dir, 1);
    setenv("SHELL=", pwd->pw_shell, 1);
    if (term[0] == '\0')
	strncpy(term, stypeof(tty), sizeof(term));
    setenv("TERM=", term, 0);
    setenv("USER="******"PATH=", ":/usr/ucb:/bin:/usr/bin", 0);

    if ((namep = strrchr(pwd->pw_shell, '/')) == NULL)
	namep = pwd->pw_shell;
    else
	namep++;
    strcat(minusnam, namep);
    if (tty[sizeof("tty") - 1] == 'd')
	syslog(LOG_INFO, "DIALUP %s, %s", tty, pwd->pw_name);
    if (pwd->pw_uid == 0)
	if (utmp.ut_host[0])
	    syslog(LOG_NOTICE, "ROOT LOGIN %s FROM %.*s", tty, HMAX,
		   utmp.ut_host);
	else
	    syslog(LOG_NOTICE, "ROOT LOGIN %s", tty);
    if (!quietlog) {
	struct stat st;

	showmotd();
	strcat(maildir, pwd->pw_name);
	if (stat(maildir, &st) == 0 && st.st_size != 0)
	    printf("You have %smail.\n",
		   (st.st_mtime > st.st_atime) ? "new " : "");
    }
    signal(SIGALRM, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    signal(SIGTSTP, SIG_IGN);
    execlp(pwd->pw_shell, minusnam, 0);
    perror(pwd->pw_shell);
    printf("No shell\n");
    exit(0);
}