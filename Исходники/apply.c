int
main(int argc, char *argv[])
{
	int ch, debug, i, magic, n, nargs, rval;
	char buf[4], *cmd, *p;

	if (pledge("stdio proc exec", NULL) == -1)
		err(1, "pledge");

	debug = 0;
	magic = '%';		/* Default magic char is `%'. */
	nargs = -1;
	while ((ch = getopt(argc, argv, "a:d0123456789")) != -1)
		switch (ch) {
		case 'a':
			if (optarg[0] == '\0' || optarg[1] != '\0')
				errx(1,
				    "illegal magic character specification.");
			magic = optarg[0];
			break;
		case 'd':
			debug = 1;
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			if (nargs != -1)
				errx(1,
				    "only one -# argument may be specified.");
			nargs = ch - '0';
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc < 2)
		usage();

	/*
	 * The command to run is argv[0], and the args are argv[1..].
	 * Look for %digit references in the command, remembering the
	 * largest one.
	 */
	for (n = 0, p = argv[0]; *p != '\0'; ++p)
		if (ISMAGICNO(p)) {
			++p;
			if (p[0] - '0' > n)
				n = p[0] - '0';
		}

	/*
	 * If there were any %digit references, then use those, otherwise
	 * build a new command string with sufficient %digit references at
	 * the end to consume (nargs) arguments each time round the loop.
	 * Allocate enough space to hold the maximum command.
	 */
	strset(argv[0]);
	if (n == 0) {
		/* If nargs not set, default to a single argument. */
		if (nargs == -1)
			nargs = 1;

		for (i = 1; i <= nargs; i++) {
			snprintf(buf, sizeof(buf), " %c%d", magic, i);
			stradd(buf);
		}

		/*
		 * If nargs set to the special value 0, eat a single
		 * argument for each command execution.
		 */
		if (nargs == 0)
			nargs = 1;
	} else
		nargs = n;
	if ((cmd = strdup(str)) == NULL)
		err(1, "strdup");

	/*
	 * (argc) and (argv) are still offset by one to make it simpler to
	 * expand %digit references.  At the end of the loop check for (argc)
	 * equals 1 means that all the (argv) has been consumed.
	 */
	for (rval = 0; argc > nargs; argc -= nargs, argv += nargs) {
		strset("exec ");

		/* Expand command argv references. */
		for (p = cmd; *p != '\0'; ++p)
			if (ISMAGICNO(p))
				stradd(argv[*(++p) - '0']);
			else {
				strlcpy(buf, p, 2);
				stradd(buf);
			}

		/* Run the command. */
		if (debug)
			(void)printf("%s\n", str);
		else if (mysystem(str))
			rval = 1;
	}

	if (argc != 1)
		errx(1, "expecting additional argument%s after \"%s\"",
		    (nargs - argc) ? "s" : "", argv[argc - 1]);
	exit(rval);
}