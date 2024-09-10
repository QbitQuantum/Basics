int
main(int argc, char **argv)
{
	DIR *procdir;
	char *p;
	char *sortk = "cpu";	/* default sort key */
	int opt;
	int timeout;
	struct pollfd pollset;
	char key;

	(void) setlocale(LC_ALL, "");
	(void) textdomain(TEXT_DOMAIN);
	Progname(argv[0]);
	lwpid_init();
	fd_init(Setrlimit());

	while ((opt = getopt(argc, argv, "vcmaRLtu:U:n:p:C:P:s:S:j:k:TJz:Z"))
	    != (int)EOF) {
		switch (opt) {
		case 'R':
			opts.o_outpmode |= OPT_REALTIME;
			break;
		case 'c':
			opts.o_outpmode &= ~OPT_TERMCAP;
			opts.o_outpmode &= ~OPT_FULLSCREEN;
			break;
		case 'm':
		case 'v':
			opts.o_outpmode &= ~OPT_PSINFO;
			opts.o_outpmode |=  OPT_MSACCT;
			break;
		case 't':
			opts.o_outpmode &= ~OPT_PSINFO;
			opts.o_outpmode |= OPT_USERS;
			break;
		case 'a':
			opts.o_outpmode |= OPT_SPLIT | OPT_USERS;
			break;
		case 'T':
			opts.o_outpmode |= OPT_SPLIT | OPT_TASKS;
			break;
		case 'J':
			opts.o_outpmode |= OPT_SPLIT | OPT_PROJECTS;
			break;
		case 'n':
			if ((p = strtok(optarg, ",")) == NULL)
				Die(gettext("invalid argument for -n\n"));
			opts.o_ntop = Atoi(p);
			if (p = strtok(NULL, ","))
				opts.o_nbottom = Atoi(p);
			opts.o_outpmode &= ~OPT_FULLSCREEN;
			break;
		case 's':
			opts.o_sortorder = -1;
			sortk = optarg;
			break;
		case 'S':
			opts.o_sortorder = 1;
			sortk = optarg;
			break;
		case 'u':
			if ((p = strtok(optarg, ", ")) == NULL)
				Die(gettext("invalid argument for -u\n"));
			add_uid(&euid_tbl, p);
			while (p = strtok(NULL, ", "))
				add_uid(&euid_tbl, p);
			break;
		case 'U':
			if ((p = strtok(optarg, ", ")) == NULL)
				Die(gettext("invalid argument for -U\n"));
			add_uid(&ruid_tbl, p);
			while (p = strtok(NULL, ", "))
				add_uid(&ruid_tbl, p);
			break;
		case 'p':
			fill_table(&pid_tbl, optarg, 'p');
			break;
		case 'C':
			fill_set_table(optarg);
			opts.o_outpmode |= OPT_PSETS;
			break;
		case 'P':
			fill_table(&cpu_tbl, optarg, 'P');
			break;
		case 'k':
			fill_table(&tsk_tbl, optarg, 'k');
			break;
		case 'j':
			fill_prj_table(optarg);
			break;
		case 'L':
			opts.o_outpmode |= OPT_LWPS;
			break;
		case 'z':
			if ((p = strtok(optarg, ", ")) == NULL)
				Die(gettext("invalid argument for -z\n"));
			add_zone(&zone_tbl, p);
			while (p = strtok(NULL, ", "))
				add_zone(&zone_tbl, p);
			break;
		case 'Z':
			opts.o_outpmode |= OPT_SPLIT | OPT_ZONES;
			break;
		default:
			Usage();
		}
	}

	(void) atexit(Exit);
	if ((opts.o_outpmode & OPT_USERS) &&
	    !(opts.o_outpmode & OPT_SPLIT))
		opts.o_nbottom = opts.o_ntop;
	if (opts.o_ntop == 0 || opts.o_nbottom == 0)
		Die(gettext("invalid argument for -n\n"));
	if (!(opts.o_outpmode & OPT_SPLIT) && (opts.o_outpmode & OPT_USERS) &&
	    ((opts.o_outpmode & (OPT_PSINFO | OPT_MSACCT))))
		Die(gettext("-t option cannot be used with -v or -m\n"));

	if ((opts.o_outpmode & OPT_SPLIT) && (opts.o_outpmode && OPT_USERS) &&
	    !((opts.o_outpmode & (OPT_PSINFO | OPT_MSACCT))))
		Die(gettext("-t option cannot be used with "
		    "-a, -J, -T or -Z\n"));

	if ((opts.o_outpmode & OPT_USERS) &&
	    (opts.o_outpmode & (OPT_TASKS | OPT_PROJECTS | OPT_ZONES)))
		Die(gettext("-a option cannot be used with "
		    "-t, -J, -T or -Z\n"));

	if (((opts.o_outpmode & OPT_TASKS) &&
	    (opts.o_outpmode & (OPT_PROJECTS|OPT_ZONES))) ||
	    ((opts.o_outpmode & OPT_PROJECTS) &&
	    (opts.o_outpmode & (OPT_TASKS|OPT_ZONES)))) {
		Die(gettext("-J, -T and -Z options are mutually exclusive\n"));
	}

	if (argc > optind)
		opts.o_interval = Atoi(argv[optind++]);
	if (argc > optind)
		opts.o_count = Atoi(argv[optind++]);
	if (opts.o_count == 0)
		Die(gettext("invalid counter value\n"));
	if (argc > optind)
		Usage();
	if (opts.o_outpmode & OPT_REALTIME)
		Priocntl("RT");
	if (isatty(STDOUT_FILENO) == 1 && isatty(STDIN_FILENO))
		opts.o_outpmode |= OPT_TTY;	/* interactive */
	if (!(opts.o_outpmode & OPT_TTY)) {
		opts.o_outpmode &= ~OPT_TERMCAP; /* no termcap for pipes */
		opts.o_outpmode &= ~OPT_FULLSCREEN;
	}
	if (opts.o_outpmode & OPT_TERMCAP)
		ldtermcap();		/* can turn OPT_TERMCAP off */
	if (opts.o_outpmode & OPT_TERMCAP)
		(void) setsize();
	list_alloc(&lwps, opts.o_ntop);
	list_alloc(&users, opts.o_nbottom);
	list_alloc(&tasks, opts.o_nbottom);
	list_alloc(&projects, opts.o_nbottom);
	list_alloc(&zones, opts.o_nbottom);
	list_setkeyfunc(sortk, &opts, &lwps, LT_LWPS);
	list_setkeyfunc(NULL, &opts, &users, LT_USERS);
	list_setkeyfunc(NULL, &opts, &tasks, LT_TASKS);
	list_setkeyfunc(NULL, &opts, &projects, LT_PROJECTS);
	list_setkeyfunc(NULL, &opts, &zones, LT_ZONES);
	if (opts.o_outpmode & OPT_TERMCAP)
		curses_on();
	if ((procdir = opendir("/proc")) == NULL)
		Die(gettext("cannot open /proc directory\n"));
	if (opts.o_outpmode & OPT_TTY) {
		(void) printf(gettext("Please wait...\r"));
		(void) fflush(stdout);
	}
	set_signals();
	pollset.fd = STDIN_FILENO;
	pollset.events = POLLIN;
	timeout = opts.o_interval * MILLISEC;

	/*
	 * main program loop
	 */
	do {
		if (sigterm == 1)
			break;
		if (sigtstp == 1) {
			curses_off();
			(void) signal(SIGTSTP, SIG_DFL);
			(void) kill(0, SIGTSTP);
			/*
			 * prstat stops here until it receives SIGCONT signal.
			 */
			sigtstp = 0;
			(void) signal(SIGTSTP, sig_handler);
			curses_on();
			print_movecur = FALSE;
			if (opts.o_outpmode & OPT_FULLSCREEN)
				sigwinch = 1;
		}
		if (sigwinch == 1) {
			if (setsize() == 1) {
				list_free(&lwps);
				list_free(&users);
				list_free(&tasks);
				list_free(&projects);
				list_free(&zones);
				list_alloc(&lwps, opts.o_ntop);
				list_alloc(&users, opts.o_nbottom);
				list_alloc(&tasks, opts.o_nbottom);
				list_alloc(&projects, opts.o_nbottom);
				list_alloc(&zones, opts.o_nbottom);
			}
			sigwinch = 0;
			(void) signal(SIGWINCH, sig_handler);
		}
		prstat_scandir(procdir);
		list_refresh(&lwps);
		if (print_movecur)
			(void) putp(movecur);
		print_movecur = TRUE;
		if ((opts.o_outpmode & OPT_PSINFO) ||
		    (opts.o_outpmode & OPT_MSACCT)) {
			list_sort(&lwps);
			list_print(&lwps);
		}
		if (opts.o_outpmode & OPT_USERS) {
			list_sort(&users);
			list_print(&users);
			list_clear(&users);
		}
		if (opts.o_outpmode & OPT_TASKS) {
			list_sort(&tasks);
			list_print(&tasks);
			list_clear(&tasks);
		}
		if (opts.o_outpmode & OPT_PROJECTS) {
			list_sort(&projects);
			list_print(&projects);
			list_clear(&projects);
		}
		if (opts.o_outpmode & OPT_ZONES) {
			list_sort(&zones);
			list_print(&zones);
			list_clear(&zones);
		}
		if (opts.o_count == 1)
			break;
		/*
		 * If poll() returns -1 and sets errno to EINTR here because
		 * the process received a signal, it is Ok to abort this
		 * timeout and loop around because we check the signals at the
		 * top of the loop.
		 */
		if (opts.o_outpmode & OPT_TTY) {
			if (poll(&pollset, (nfds_t)1, timeout) > 0) {
				if (read(STDIN_FILENO, &key, 1) == 1) {
					if (tolower(key) == 'q')
						break;
				}
			}
		} else {
			(void) sleep(opts.o_interval);
		}
	} while (opts.o_count == (-1) || --opts.o_count);

	if (opts.o_outpmode & OPT_TTY)
		(void) putchar('\r');
	return (0);
}