int
main(int argc, char *argv[])
{
	int ch, rval, seq;
	wchar_t *warg;
	const char *arg;
	size_t len;

	setlocale(LC_CTYPE, "");

	seq = 0;
	while ((ch = getopt(argc, argv, "d:s")) != -1)
		switch(ch) {
		case 'd':
			arg = optarg;
			len = mbsrtowcs(NULL, &arg, 0, NULL);
			if (len == (size_t)-1)
				err(1, "delimiters");
			warg = malloc((len + 1) * sizeof(*warg));
			if (warg == NULL)
				err(1, NULL);
			arg = optarg;
			len = mbsrtowcs(warg, &arg, len + 1, NULL);
			if (len == (size_t)-1)
				err(1, "delimiters");
			delimcnt = tr(delim = warg);
			break;
		case 's':
			seq = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (*argv == NULL)
		usage();
	if (!delim) {
		delimcnt = 1;
		delim = tab;
	}

	if (seq)
		rval = sequential(argv);
	else
		rval = parallel(argv);
	exit(rval);
}