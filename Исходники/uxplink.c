int main(int argc, char **argv)
{
    bool sending;
    int *fdlist;
    int fd;
    int i, fdstate;
    size_t fdsize;
    int exitcode;
    bool errors;
    enum TriState sanitise_stdout = AUTO, sanitise_stderr = AUTO;
    bool use_subsystem = false;
    bool just_test_share_exists = false;
    unsigned long now;
    struct winsize size;
    const struct BackendVtable *backvt;

    fdlist = NULL;
    fdsize = 0;
    /*
     * Initialise port and protocol to sensible defaults. (These
     * will be overridden by more or less anything.)
     */
    default_protocol = PROT_SSH;
    default_port = 22;

    bufchain_init(&stdout_data);
    bufchain_init(&stderr_data);
    bufchain_sink_init(&stdout_bcs, &stdout_data);
    bufchain_sink_init(&stderr_bcs, &stderr_data);
    stdout_bs = BinarySink_UPCAST(&stdout_bcs);
    stderr_bs = BinarySink_UPCAST(&stderr_bcs);
    outgoingeof = EOF_NO;

    flags = FLAG_STDERR_TTY;
    cmdline_tooltype |=
        (TOOLTYPE_HOST_ARG |
         TOOLTYPE_HOST_ARG_CAN_BE_SESSION |
         TOOLTYPE_HOST_ARG_PROTOCOL_PREFIX |
         TOOLTYPE_HOST_ARG_FROM_LAUNCHABLE_LOAD);

    stderr_tty_init();
    /*
     * Process the command line.
     */
    conf = conf_new();
    do_defaults(NULL, conf);
    loaded_session = false;
    default_protocol = conf_get_int(conf, CONF_protocol);
    default_port = conf_get_int(conf, CONF_port);
    errors = false;
    {
	/*
	 * Override the default protocol if PLINK_PROTOCOL is set.
	 */
	char *p = getenv("PLINK_PROTOCOL");
	if (p) {
            const struct BackendVtable *vt = backend_vt_from_name(p);
            if (vt) {
                default_protocol = vt->protocol;
                default_port = vt->default_port;
		conf_set_int(conf, CONF_protocol, default_protocol);
		conf_set_int(conf, CONF_port, default_port);
	    }
	}
    }
    while (--argc) {
	char *p = *++argv;
        int ret = cmdline_process_param(p, (argc > 1 ? argv[1] : NULL),
                                        1, conf);
        if (ret == -2) {
            fprintf(stderr,
                    "plink: option \"%s\" requires an argument\n", p);
            errors = true;
        } else if (ret == 2) {
            --argc, ++argv;
        } else if (ret == 1) {
            continue;
        } else if (!strcmp(p, "-batch")) {
            console_batch_mode = true;
        } else if (!strcmp(p, "-s")) {
            /* Save status to write to conf later. */
            use_subsystem = true;
        } else if (!strcmp(p, "-V") || !strcmp(p, "--version")) {
            version();
        } else if (!strcmp(p, "--help")) {
            usage();
            exit(0);
        } else if (!strcmp(p, "-pgpfp")) {
            pgp_fingerprints();
            exit(1);
        } else if (!strcmp(p, "-o")) {
            if (argc <= 1) {
                fprintf(stderr,
                        "plink: option \"-o\" requires an argument\n");
                errors = true;
            } else {
                --argc;
                /* Explicitly pass "plink" in place of appname for
                 * error reporting purposes. appname will have been
                 * set by be_foo.c to something more generic, probably
                 * "PuTTY". */
                provide_xrm_string(*++argv, "plink");
            }
        } else if (!strcmp(p, "-shareexists")) {
            just_test_share_exists = true;
        } else if (!strcmp(p, "-fuzznet")) {
            conf_set_int(conf, CONF_proxy_type, PROXY_FUZZ);
            conf_set_str(conf, CONF_proxy_telnet_command, "%host");
        } else if (!strcmp(p, "-sanitise-stdout") ||
                   !strcmp(p, "-sanitize-stdout")) {
            sanitise_stdout = FORCE_ON;
        } else if (!strcmp(p, "-no-sanitise-stdout") ||
                   !strcmp(p, "-no-sanitize-stdout")) {
            sanitise_stdout = FORCE_OFF;
        } else if (!strcmp(p, "-sanitise-stderr") ||
                   !strcmp(p, "-sanitize-stderr")) {
            sanitise_stderr = FORCE_ON;
        } else if (!strcmp(p, "-no-sanitise-stderr") ||
                   !strcmp(p, "-no-sanitize-stderr")) {
            sanitise_stderr = FORCE_OFF;
        } else if (!strcmp(p, "-no-antispoof")) {
            console_antispoof_prompt = false;
	} else if (*p != '-') {
            strbuf *cmdbuf = strbuf_new();

            while (argc > 0) {
                if (cmdbuf->len > 0)
                    put_byte(cmdbuf, ' '); /* add space separator */
                put_datapl(cmdbuf, ptrlen_from_asciz(p));
                if (--argc > 0)
                    p = *++argv;
            }

            conf_set_str(conf, CONF_remote_cmd, cmdbuf->s);
            conf_set_str(conf, CONF_remote_cmd2, "");
            conf_set_bool(conf, CONF_nopty, true);  /* command => no tty */

            strbuf_free(cmdbuf);
            break;		       /* done with cmdline */
        } else {
            fprintf(stderr, "plink: unknown option \"%s\"\n", p);
            errors = true;
	}
    }

    if (errors)
	return 1;

    if (!cmdline_host_ok(conf)) {
	usage();
    }

    prepare_session(conf);

    /*
     * Perform command-line overrides on session configuration.
     */
    cmdline_run_saved(conf);

    /*
     * If we have no better ideas for the remote username, use the local
     * one, as 'ssh' does.
     */
    if (conf_get_str(conf, CONF_username)[0] == '\0') {
	char *user = get_username();
	if (user) {
	    conf_set_str(conf, CONF_username, user);
	    sfree(user);
	}
    }

    /*
     * Apply subsystem status.
     */
    if (use_subsystem)
        conf_set_bool(conf, CONF_ssh_subsys, true);

    if (!*conf_get_str(conf, CONF_remote_cmd) &&
	!*conf_get_str(conf, CONF_remote_cmd2) &&
	!*conf_get_str(conf, CONF_ssh_nc_host))
	flags |= FLAG_INTERACTIVE;

    /*
     * Select protocol. This is farmed out into a table in a
     * separate file to enable an ssh-free variant.
     */
    backvt = backend_vt_from_proto(conf_get_int(conf, CONF_protocol));
    if (!backvt) {
	fprintf(stderr,
		"Internal fault: Unsupported protocol found\n");
	return 1;
    }

    /*
     * Block SIGPIPE, so that we'll get EPIPE individually on
     * particular network connections that go wrong.
     */
    putty_signal(SIGPIPE, SIG_IGN);

    /*
     * Set up the pipe we'll use to tell us about SIGWINCH.
     */
    if (pipe(signalpipe) < 0) {
	perror("pipe");
	exit(1);
    }
    /* We don't want the signal handler to block if the pipe's full. */
    nonblock(signalpipe[0]);
    nonblock(signalpipe[1]);
    cloexec(signalpipe[0]);
    cloexec(signalpipe[1]);
    putty_signal(SIGWINCH, sigwinch);

    /*
     * Now that we've got the SIGWINCH handler installed, try to find
     * out the initial terminal size.
     */
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) >= 0) {
	conf_set_int(conf, CONF_width, size.ws_col);
	conf_set_int(conf, CONF_height, size.ws_row);
    }

    /*
     * Decide whether to sanitise control sequences out of standard
     * output and standard error.
     *
     * If we weren't given a command-line override, we do this if (a)
     * the fd in question is pointing at a terminal, and (b) we aren't
     * trying to allocate a terminal as part of the session.
     *
     * (Rationale: the risk of control sequences is that they cause
     * confusion when sent to a local terminal, so if there isn't one,
     * no problem. Also, if we allocate a remote terminal, then we
     * sent a terminal type, i.e. we told it what kind of escape
     * sequences we _like_, i.e. we were expecting to receive some.)
     */
    if (sanitise_stdout == FORCE_ON ||
        (sanitise_stdout == AUTO && isatty(STDOUT_FILENO) &&
         conf_get_bool(conf, CONF_nopty))) {
        stdout_scc = stripctrl_new(stdout_bs, true, L'\0');
        stdout_bs = BinarySink_UPCAST(stdout_scc);
    }
    if (sanitise_stderr == FORCE_ON ||
        (sanitise_stderr == AUTO && isatty(STDERR_FILENO) &&
         conf_get_bool(conf, CONF_nopty))) {
        stderr_scc = stripctrl_new(stderr_bs, true, L'\0');
        stderr_bs = BinarySink_UPCAST(stderr_scc);
    }

    sk_init();
    uxsel_init();

    /*
     * Plink doesn't provide any way to add forwardings after the
     * connection is set up, so if there are none now, we can safely set
     * the "simple" flag.
     */
    if (conf_get_int(conf, CONF_protocol) == PROT_SSH &&
	!conf_get_bool(conf, CONF_x11_forward) &&
	!conf_get_bool(conf, CONF_agentfwd) &&
	!conf_get_str_nthstrkey(conf, CONF_portfwd, 0))
	conf_set_bool(conf, CONF_ssh_simple, true);

    if (just_test_share_exists) {
        if (!backvt->test_for_upstream) {
            fprintf(stderr, "Connection sharing not supported for connection "
                    "type '%s'\n", backvt->name);
            return 1;
        }
        if (backvt->test_for_upstream(conf_get_str(conf, CONF_host),
                                      conf_get_int(conf, CONF_port), conf))
            return 0;
        else
            return 1;
    }

    /*
     * Start up the connection.
     */
    logctx = log_init(default_logpolicy, conf);
    {
	const char *error;
	char *realhost;
	/* nodelay is only useful if stdin is a terminal device */
	bool nodelay = conf_get_bool(conf, CONF_tcp_nodelay) && isatty(0);

	/* This is a good place for a fuzzer to fork us. */
#ifdef __AFL_HAVE_MANUAL_CONTROL
	__AFL_INIT();
#endif

        error = backend_init(backvt, plink_seat, &backend, logctx, conf,
                             conf_get_str(conf, CONF_host),
                             conf_get_int(conf, CONF_port),
                             &realhost, nodelay,
                             conf_get_bool(conf, CONF_tcp_keepalives));
	if (error) {
	    fprintf(stderr, "Unable to open connection:\n%s\n", error);
	    return 1;
	}
        ldisc_create(conf, NULL, backend, plink_seat);
	sfree(realhost);
    }

    /*
     * Set up the initial console mode. We don't care if this call
     * fails, because we know we aren't necessarily running in a
     * console.
     */
    local_tty = (tcgetattr(STDIN_FILENO, &orig_termios) == 0);
    atexit(cleanup_termios);
    seat_echoedit_update(plink_seat, 1, 1);
    sending = false;
    now = GETTICKCOUNT();

    pollwrapper *pw = pollwrap_new();

    while (1) {
	int rwx;
	int ret;
        unsigned long next;

        pollwrap_clear(pw);

	pollwrap_add_fd_rwx(pw, signalpipe[0], SELECT_R);

	if (!sending &&
            backend_connected(backend) &&
            backend_sendok(backend) &&
            backend_sendbuffer(backend) < MAX_STDIN_BACKLOG) {
	    /* If we're OK to send, then try to read from stdin. */
            pollwrap_add_fd_rwx(pw, STDIN_FILENO, SELECT_R);
	}

	if (bufchain_size(&stdout_data) > 0) {
	    /* If we have data for stdout, try to write to stdout. */
            pollwrap_add_fd_rwx(pw, STDOUT_FILENO, SELECT_W);
	}

	if (bufchain_size(&stderr_data) > 0) {
	    /* If we have data for stderr, try to write to stderr. */
            pollwrap_add_fd_rwx(pw, STDERR_FILENO, SELECT_W);
	}

	/* Count the currently active fds. */
	i = 0;
	for (fd = first_fd(&fdstate, &rwx); fd >= 0;
	     fd = next_fd(&fdstate, &rwx)) i++;

	/* Expand the fdlist buffer if necessary. */
        sgrowarray(fdlist, fdsize, i);

	/*
	 * Add all currently open fds to pw, and store them in fdlist
	 * as well.
	 */
	int fdcount = 0;
	for (fd = first_fd(&fdstate, &rwx); fd >= 0;
	     fd = next_fd(&fdstate, &rwx)) {
	    fdlist[fdcount++] = fd;
            pollwrap_add_fd_rwx(pw, fd, rwx);
	}

        if (toplevel_callback_pending()) {
            ret = pollwrap_poll_instant(pw);
        } else if (run_timers(now, &next)) {
            do {
                unsigned long then;
                long ticks;

		then = now;
		now = GETTICKCOUNT();
		if (now - then > next - then)
		    ticks = 0;
		else
		    ticks = next - now;

                bool overflow = false;
                if (ticks > INT_MAX) {
                    ticks = INT_MAX;
                    overflow = true;
                }

                ret = pollwrap_poll_timeout(pw, ticks);
                if (ret == 0 && !overflow)
                    now = next;
                else
                    now = GETTICKCOUNT();
            } while (ret < 0 && errno == EINTR);
        } else {
            ret = pollwrap_poll_endless(pw);
        }

        if (ret < 0 && errno == EINTR)
            continue;

	if (ret < 0) {
	    perror("poll");
	    exit(1);
	}

	for (i = 0; i < fdcount; i++) {
	    fd = fdlist[i];
            int rwx = pollwrap_get_fd_rwx(pw, fd);
            /*
             * We must process exceptional notifications before
             * ordinary readability ones, or we may go straight
             * past the urgent marker.
             */
	    if (rwx & SELECT_X)
		select_result(fd, SELECT_X);
	    if (rwx & SELECT_R)
		select_result(fd, SELECT_R);
	    if (rwx & SELECT_W)
		select_result(fd, SELECT_W);
	}

	if (pollwrap_check_fd_rwx(pw, signalpipe[0], SELECT_R)) {
	    char c[1];
	    struct winsize size;
	    if (read(signalpipe[0], c, 1) <= 0)
		/* ignore error */;
	    /* ignore its value; it'll be `x' */
	    if (ioctl(STDIN_FILENO, TIOCGWINSZ, (void *)&size) >= 0)
                backend_size(backend, size.ws_col, size.ws_row);
	}

	if (pollwrap_check_fd_rwx(pw, STDIN_FILENO, SELECT_R)) {
	    char buf[4096];
	    int ret;

            if (backend_connected(backend)) {
		ret = read(STDIN_FILENO, buf, sizeof(buf));
                noise_ultralight(NOISE_SOURCE_IOLEN, ret);
		if (ret < 0) {
		    perror("stdin: read");
		    exit(1);
		} else if (ret == 0) {
                    backend_special(backend, SS_EOF, 0);
		    sending = false;   /* send nothing further after this */
		} else {
		    if (local_tty)
			from_tty(buf, ret);
		    else
                        backend_send(backend, buf, ret);
		}
	    }
	}

	if (pollwrap_check_fd_rwx(pw, STDOUT_FILENO, SELECT_W)) {
            backend_unthrottle(backend, try_output(false));
	}

	if (pollwrap_check_fd_rwx(pw, STDERR_FILENO, SELECT_W)) {
            backend_unthrottle(backend, try_output(true));
	}

        run_toplevel_callbacks();

        if (!backend_connected(backend) &&
	    bufchain_size(&stdout_data) == 0 &&
	    bufchain_size(&stderr_data) == 0)
	    break;		       /* we closed the connection */
    }
    exitcode = backend_exitcode(backend);
    if (exitcode < 0) {
	fprintf(stderr, "Remote process exit code unavailable\n");
	exitcode = 1;		       /* this is an error condition */
    }
    cleanup_exit(exitcode);
    return exitcode;		       /* shouldn't happen, but placates gcc */
}