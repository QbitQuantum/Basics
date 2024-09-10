int
main(int argc, char *argv[])
{
	int c;

	while ((c = getopt(argc, argv, "-cvl:")) != -1)
		switch (c) {
		case '-':
			readstd++;
			break;
		case 'c':
			cflg++;
			break;
		case 'v':
			vflg++;
			break;
		case 'l':
			array = optarg;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (array == 0)
		array = "xstr";

	if (signal(SIGINT, SIG_IGN) == SIG_DFL)
		(void)signal(SIGINT, onintr);
	if (cflg || (argc == 0 && !readstd))
		inithash();
	else {
		int	fd;

		snprintf(stringtmpfile, sizeof(stringtmpfile),
		    "%s%s.XXXXXX", _PATH_TMP, "xstr");
		strings = stringtmpfile;
		fd = mkstemp(stringtmpfile);
		if (fd == -1)
			err(1, "mkstemp failed");
		close(fd);
	}
	while (readstd || argc > 0) {
		if (freopen("x.c", "w", stdout) == NULL)
			err(1, "Cannot open `%s'", "x.c");
		if (!readstd && freopen(argv[0], "r", stdin) == NULL)
			err(1, "Cannot open `%s'", argv[0]);
		process("x.c");
		if (readstd == 0)
			argc--, argv++;
		else
			readstd = 0;
	};
	flushsh();
	if (cflg == 0)
		xsdotc();
	if (strings[0] == '/')
		(void)unlink(strings);
	exit(0);
}