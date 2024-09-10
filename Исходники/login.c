int
main(int argc, char **argv)
{
	struct group *gr;
	struct stat st;
	int retries, backoff;
	int ask, ch, cnt, quietlog, rootlogin, rval;
	uid_t uid, euid;
	gid_t egid;
	char *term;
	char *p, *ttyn;
	char tname[sizeof(_PATH_TTY) + 10];
	char *arg0;
	const char *tp;
	const char *shell = NULL;
	login_cap_t *lc = NULL;
	login_cap_t *lc_user = NULL;
	pid_t pid;
#ifdef USE_BSM_AUDIT
	char auditsuccess = 1;
#endif

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	if (setjmp(timeout_buf)) {
		if (failures)
			badlogin(username);
		fprintf(stderr, "Login timed out after %d seconds\n",
		    timeout);
		bail(NO_SLEEP_EXIT, 0);
	}
	signal(SIGALRM, timedout);
	alarm(timeout);
	setpriority(PRIO_PROCESS, 0, 0);

	openlog("login", LOG_ODELAY, LOG_AUTH);

	uid = getuid();
	euid = geteuid();
	egid = getegid();

	while ((ch = getopt(argc, argv, "fh:p")) != -1)
		switch (ch) {
		case 'f':
			fflag = 1;
			break;
		case 'h':
			if (uid != 0)
				errx(1, "-h option: %s", strerror(EPERM));
			if (strlen(optarg) >= MAXHOSTNAMELEN)
				errx(1, "-h option: %s: exceeds maximum "
				    "hostname size", optarg);
			hflag = 1;
			hostname = optarg;
			break;
		case 'p':
			pflag = 1;
			break;
		case '?':
		default:
			if (uid == 0)
				syslog(LOG_ERR, "invalid flag %c", ch);
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc > 0) {
		username = strdup(*argv);
		if (username == NULL)
			err(1, "strdup()");
		ask = 0;
	} else {
		ask = 1;
	}

	setproctitle("-%s", getprogname());

	for (cnt = getdtablesize(); cnt > 2; cnt--)
		close(cnt);

	/*
	 * Get current TTY
	 */
	ttyn = ttyname(STDIN_FILENO);
	if (ttyn == NULL || *ttyn == '\0') {
		snprintf(tname, sizeof(tname), "%s??", _PATH_TTY);
		ttyn = tname;
	}
	if (strncmp(ttyn, _PATH_DEV, sizeof(_PATH_DEV) -1) == 0)
		tty = ttyn + sizeof(_PATH_DEV) -1;
	else
		tty = ttyn;

	/*
	 * Get "login-retries" & "login-backoff" from default class
	 */
	lc = login_getclass(NULL);
	prompt = login_getcapstr(lc, "login_prompt",
	    default_prompt, default_prompt);
	passwd_prompt = login_getcapstr(lc, "passwd_prompt",
	    default_passwd_prompt, default_passwd_prompt);
	retries = login_getcapnum(lc, "login-retries",
	    DEFAULT_RETRIES, DEFAULT_RETRIES);
	backoff = login_getcapnum(lc, "login-backoff",
	    DEFAULT_BACKOFF, DEFAULT_BACKOFF);
	login_close(lc);
	lc = NULL;

	/*
	 * Try to authenticate the user until we succeed or time out.
	 */
	for (cnt = 0;; ask = 1) {
		if (ask) {
			fflag = 0;
			if (olduser != NULL)
				free(olduser);
			olduser = username;
			username = getloginname();
		}
		rootlogin = 0;

		/*
		 * Note if trying multiple user names; log failures for
		 * previous user name, but don't bother logging one failure
		 * for nonexistent name (mistyped username).
		 */
		if (failures && strcmp(olduser, username) != 0) {
			if (failures > (pwd ? 0 : 1))
				badlogin(olduser);
		}

		/*
		 * Load the PAM policy and set some variables
		 */
		pam_err = pam_start("login", username, &pamc, &pamh);
		if (pam_err != PAM_SUCCESS) {
			pam_syslog("pam_start()");
#ifdef USE_BSM_AUDIT
			au_login_fail("PAM Error", 1);
#endif
			bail(NO_SLEEP_EXIT, 1);
		}
		pam_err = pam_set_item(pamh, PAM_TTY, tty);
		if (pam_err != PAM_SUCCESS) {
			pam_syslog("pam_set_item(PAM_TTY)");
#ifdef USE_BSM_AUDIT
			au_login_fail("PAM Error", 1);
#endif
			bail(NO_SLEEP_EXIT, 1);
		}
		pam_err = pam_set_item(pamh, PAM_RHOST, hostname);
		if (pam_err != PAM_SUCCESS) {
			pam_syslog("pam_set_item(PAM_RHOST)");
#ifdef USE_BSM_AUDIT
			au_login_fail("PAM Error", 1);
#endif
			bail(NO_SLEEP_EXIT, 1);
		}

		pwd = getpwnam(username);
		if (pwd != NULL && pwd->pw_uid == 0)
			rootlogin = 1;

		/*
		 * If the -f option was specified and the caller is
		 * root or the caller isn't changing their uid, don't
		 * authenticate.
		 */
		if (pwd != NULL && fflag &&
		    (uid == (uid_t)0 || uid == (uid_t)pwd->pw_uid)) {
			/* already authenticated */
			rval = 0;
#ifdef USE_BSM_AUDIT
			auditsuccess = 0; /* opened a terminal window only */
#endif
		} else {
			fflag = 0;
			setpriority(PRIO_PROCESS, 0, -4);
			rval = auth_pam();
			setpriority(PRIO_PROCESS, 0, 0);
		}

		if (pwd && rval == 0)
			break;

		pam_cleanup();

		/*
		 * We are not exiting here, but this corresponds to a failed
		 * login event, so set exitstatus to 1.
		 */
#ifdef USE_BSM_AUDIT
		au_login_fail("Login incorrect", 1);
#endif

		printf("Login incorrect\n");
		failures++;

		pwd = NULL;

		/*
		 * Allow up to 'retry' (10) attempts, but start
		 * backing off after 'backoff' (3) attempts.
		 */
		if (++cnt > backoff) {
			if (cnt >= retries) {
				badlogin(username);
				bail(SLEEP_EXIT, 1);
			}
			sleep((u_int)((cnt - backoff) * 5));
		}
	}

	/* committed to login -- turn off timeout */
	alarm((u_int)0);
	signal(SIGHUP, SIG_DFL);

	endpwent();

#ifdef USE_BSM_AUDIT
	/* Audit successful login. */
	if (auditsuccess)
		au_login_success();
#endif

	/*
	 * Establish the login class.
	 */
	lc = login_getpwclass(pwd);
	lc_user = login_getuserclass(pwd);

	if (!(quietlog = login_getcapbool(lc_user, "hushlogin", 0)))
		quietlog = login_getcapbool(lc, "hushlogin", 0);

	/*
	 * Switching needed for NFS with root access disabled.
	 *
	 * XXX: This change fails to modify the additional groups for the
	 * process, and as such, may restrict rights normally granted
	 * through those groups.
	 */
	setegid(pwd->pw_gid);
	seteuid(rootlogin ? 0 : pwd->pw_uid);
	if (!*pwd->pw_dir || chdir(pwd->pw_dir) < 0) {
		if (login_getcapbool(lc, "requirehome", 0))
			refused("Home directory not available", "HOMEDIR", 1);
		if (chdir("/") < 0)
			refused("Cannot find root directory", "ROOTDIR", 1);
		if (!quietlog || *pwd->pw_dir)
			printf("No home directory.\nLogging in with home = \"/\".\n");
		pwd->pw_dir = strdup("/");
		if (pwd->pw_dir == NULL) {
			syslog(LOG_NOTICE, "strdup(): %m");
			bail(SLEEP_EXIT, 1);
		}
	}
	seteuid(euid);
	setegid(egid);
	if (!quietlog) {
		quietlog = access(_PATH_HUSHLOGIN, F_OK) == 0;
		if (!quietlog)
			pam_silent = 0;
	}

	shell = login_getcapstr(lc, "shell", pwd->pw_shell, pwd->pw_shell);
	if (*pwd->pw_shell == '\0')
		pwd->pw_shell = strdup(_PATH_BSHELL);
	if (pwd->pw_shell == NULL) {
		syslog(LOG_NOTICE, "strdup(): %m");
		bail(SLEEP_EXIT, 1);
	}
	if (*shell == '\0')   /* Not overridden */
		shell = pwd->pw_shell;
	if ((shell = strdup(shell)) == NULL) {
		syslog(LOG_NOTICE, "strdup(): %m");
		bail(SLEEP_EXIT, 1);
	}

	/*
	 * Set device protections, depending on what terminal the
	 * user is logged in. This feature is used on Suns to give
	 * console users better privacy.
	 */
	login_fbtab(tty, pwd->pw_uid, pwd->pw_gid);

	/*
	 * Clear flags of the tty.  None should be set, and when the
	 * user sets them otherwise, this can cause the chown to fail.
	 * Since it isn't clear that flags are useful on character
	 * devices, we just clear them.
	 *
	 * We don't log in the case of EOPNOTSUPP because dev might be
	 * on NFS, which doesn't support chflags.
	 *
	 * We don't log in the EROFS because that means that /dev is on
	 * a read only file system and we assume that the permissions there
	 * are sane.
	 */
	if (ttyn != tname && chflags(ttyn, 0))
		if (errno != EOPNOTSUPP && errno != EROFS)
			syslog(LOG_ERR, "chflags(%s): %m", ttyn);
	if (ttyn != tname && chown(ttyn, pwd->pw_uid,
	    (gr = getgrnam(TTYGRPNAME)) ? gr->gr_gid : pwd->pw_gid))
		if (errno != EROFS)
			syslog(LOG_ERR, "chown(%s): %m", ttyn);

	/*
	 * Exclude cons/vt/ptys only, assume dialup otherwise
	 * TODO: Make dialup tty determination a library call
	 * for consistency (finger etc.)
	 */
	if (hflag && isdialuptty(tty))
		syslog(LOG_INFO, "DIALUP %s, %s", tty, pwd->pw_name);

#ifdef LOGALL
	/*
	 * Syslog each successful login, so we don't have to watch
	 * hundreds of wtmp or lastlogin files.
	 */
	if (hflag)
		syslog(LOG_INFO, "login from %s on %s as %s",
		       hostname, tty, pwd->pw_name);
	else
		syslog(LOG_INFO, "login on %s as %s",
		       tty, pwd->pw_name);
#endif

	/*
	 * If fflag is on, assume caller/authenticator has logged root
	 * login.
	 */
	if (rootlogin && fflag == 0) {
		if (hflag)
			syslog(LOG_NOTICE, "ROOT LOGIN (%s) ON %s FROM %s",
			    username, tty, hostname);
		else
			syslog(LOG_NOTICE, "ROOT LOGIN (%s) ON %s",
			    username, tty);
	}

	/*
	 * Destroy environment unless user has requested its
	 * preservation - but preserve TERM in all cases
	 */
	term = getenv("TERM");
	if (!pflag)
		environ = envinit;
	if (term != NULL) {
		if (setenv("TERM", term, 0) == -1)
			err(1, "setenv: cannot set TERM=%s", term);
	}

	/*
	 * PAM modules might add supplementary groups during pam_setcred().
	 */
	if (setusercontext(lc, pwd, pwd->pw_uid, LOGIN_SETGROUP) != 0) {
		syslog(LOG_ERR, "setusercontext() failed - exiting");
		bail(NO_SLEEP_EXIT, 1);
	}

	pam_err = pam_setcred(pamh, pam_silent|PAM_ESTABLISH_CRED);
	if (pam_err != PAM_SUCCESS) {
		pam_syslog("pam_setcred()");
		bail(NO_SLEEP_EXIT, 1);
	}
	pam_cred_established = 1;

	pam_err = pam_open_session(pamh, pam_silent);
	if (pam_err != PAM_SUCCESS) {
		pam_syslog("pam_open_session()");
		bail(NO_SLEEP_EXIT, 1);
	}
	pam_session_established = 1;

	/*
	 * We must fork() before setuid() because we need to call
	 * pam_close_session() as root.
	 */
	pid = fork();
	if (pid < 0) {
		err(1, "fork");
	} else if (pid != 0) {
		/*
		 * Parent: wait for child to finish, then clean up
		 * session.
		 */
		int status;
		setproctitle("-%s [pam]", getprogname());
		waitpid(pid, &status, 0);
		bail(NO_SLEEP_EXIT, 0);
	}

	/*
	 * NOTICE: We are now in the child process!
	 */

	/*
	 * Add any environment variables the PAM modules may have set.
	 */
	export_pam_environment();

	/*
	 * We're done with PAM now; our parent will deal with the rest.
	 */
	pam_end(pamh, 0);
	pamh = NULL;

	/*
	 * We don't need to be root anymore, so set the login name and
	 * the UID.
	 */
	if (setlogin(username) != 0) {
		syslog(LOG_ERR, "setlogin(%s): %m - exiting", username);
		bail(NO_SLEEP_EXIT, 1);
	}
	if (setusercontext(lc, pwd, pwd->pw_uid,
	    LOGIN_SETALL & ~(LOGIN_SETLOGIN|LOGIN_SETGROUP)) != 0) {
		syslog(LOG_ERR, "setusercontext() failed - exiting");
		exit(1);
	}

	if (setenv("SHELL", pwd->pw_shell, 1) == -1)
		err(1, "setenv: cannot set SHELL=%s", pwd->pw_shell);
	if (setenv("HOME", pwd->pw_dir, 1) == -1)
		err(1, "setenv: cannot set HOME=%s", pwd->pw_dir);
	/* Overwrite "term" from login.conf(5) for any known TERM */
	if (term == NULL && (tp = stypeof(tty)) != NULL) {
		if (setenv("TERM", tp, 1) == -1)
			err(1, "setenv: cannot set TERM=%s", tp);
	} else {
		if (setenv("TERM", TERM_UNKNOWN, 0) == -1)
			err(1, "setenv: cannot set TERM=%s", TERM_UNKNOWN);
	}

	if (setenv("LOGNAME", username, 1) == -1)
		err(1, "setenv: cannot set LOGNAME=%s", username);
	if (setenv("USER", username, 1) == -1)
		err(1, "setenv: cannot set USER=%s", username);
	if (setenv("PATH",
	    rootlogin ? _PATH_STDPATH : _PATH_DEFPATH, 0) == -1) {
		err(1, "setenv: cannot set PATH=%s",
		    rootlogin ? _PATH_STDPATH : _PATH_DEFPATH);
	}

	if (!quietlog) {
		const char *cw;

		cw = login_getcapstr(lc, "copyright", NULL, NULL);
		if (cw == NULL || motd(cw) == -1)
			printf("%s", copyright);

		printf("\n");

		cw = login_getcapstr(lc, "welcome", NULL, NULL);
		if (cw != NULL && access(cw, F_OK) == 0)
			motd(cw);
		else
			motd(_PATH_MOTDFILE);

		if (login_getcapbool(lc_user, "nocheckmail", 0) == 0 &&
		    login_getcapbool(lc, "nocheckmail", 0) == 0) {
			char *cx;

			/* $MAIL may have been set by class. */
			cx = getenv("MAIL");
			if (cx == NULL) {
				asprintf(&cx, "%s/%s",
				    _PATH_MAILDIR, pwd->pw_name);
			}
			if (cx && stat(cx, &st) == 0 && st.st_size != 0)
				printf("You have %smail.\n",
				    (st.st_mtime > st.st_atime) ? "new " : "");
			if (getenv("MAIL") == NULL)
				free(cx);
		}
	}

	login_close(lc_user);
	login_close(lc);

	signal(SIGALRM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);

	/*
	 * Login shells have a leading '-' in front of argv[0]
	 */
	p = strrchr(pwd->pw_shell, '/');
	if (asprintf(&arg0, "-%s", p ? p + 1 : pwd->pw_shell) >= MAXPATHLEN) {
		syslog(LOG_ERR, "user: %s: shell exceeds maximum pathname size",
		    username);
		errx(1, "shell exceeds maximum pathname size");
	} else if (arg0 == NULL) {
		err(1, "asprintf()");
	}

	execlp(shell, arg0, NULL);
	err(1, "%s", shell);

	/*
	 * That's it, folks!
	 */
}