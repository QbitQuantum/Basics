int
main(int argc, char *argv[])
{
	int i;
	int c;
	int vflag;
	char *cutarg;
	long cutloyear = ZDUMP_LO_YEAR;
	long cuthiyear = ZDUMP_HI_YEAR;
	time_t cutlotime;
	time_t cuthitime;
	char **fakeenv;
	time_t now;
	time_t t;
	time_t newt;
	struct tm tm;
	struct tm newtm;
	struct tm *tmp;
	struct tm *newtmp;

	INITIALIZE(cutlotime);
	INITIALIZE(cuthitime);
	vflag = 0;
	cutarg = NULL;
	while ((c = getopt(argc, argv, "c:v")) == 'c' || c == 'v')
		if (c == 'v')
			vflag = 1;
		else	cutarg = optarg;
	if ((c != EOF && c != -1) ||
		(optind == argc - 1 && strcmp(argv[optind], "=") == 0)) {
			usage();
	}
	if (vflag) {
		if (cutarg != NULL) {
			long	lo;
			long	hi;
			char	dummy;

			if (sscanf(cutarg, "%ld%c", &hi, &dummy) == 1) {
				cuthiyear = hi;
			} else if (sscanf(cutarg, "%ld,%ld%c",
				&lo, &hi, &dummy) == 2) {
					cutloyear = lo;
					cuthiyear = hi;
			} else {
				errx(EXIT_FAILURE,
					_("wild -c argument %s\n"),
					cutarg);
			}
		}
		setabsolutes();
		cutlotime = yeartot(cutloyear);
		cuthitime = yeartot(cuthiyear);
	}
	time(&now);
	longest = 0;
	for (i = optind; i < argc; ++i)
		if (strlen(argv[i]) > longest)
			longest = strlen(argv[i]);
	{
		int from;
		int to;

		for (i = 0; environ[i] != NULL;  ++i)
			continue;
		fakeenv = (char **) malloc((size_t) ((i + 2) *
			sizeof *fakeenv));
		if (fakeenv == NULL ||
			(fakeenv[0] = (char *) malloc((size_t) (longest +
				4))) == NULL)
					errx(EXIT_FAILURE,
					     _("malloc() failed"));
		to = 0;
		strcpy(fakeenv[to++], "TZ=");
		for (from = 0; environ[from] != NULL; ++from)
			if (strncmp(environ[from], "TZ=", 3) != 0)
				fakeenv[to++] = environ[from];
		fakeenv[to] = NULL;
		environ = fakeenv;
	}
	for (i = optind; i < argc; ++i) {
		static char	buf[MAX_STRING_LENGTH];

		strcpy(&fakeenv[0][3], argv[i]);
		if (!vflag) {
			show(argv[i], now, FALSE);
			continue;
		}
		warned = FALSE;
		t = absolute_min_time;
		show(argv[i], t, TRUE);
		t += SECSPERHOUR * HOURSPERDAY;
		show(argv[i], t, TRUE);
		if (t < cutlotime)
			t = cutlotime;
		tmp = my_localtime(&t);
		if (tmp != NULL) {
			tm = *tmp;
			strncpy(buf, abbr(&tm), (sizeof buf) - 1);
		}
		for ( ; ; ) {
			if (t >= cuthitime || t >= cuthitime - SECSPERHOUR * 12)
				break;
			newt = t + SECSPERHOUR * 12;
			newtmp = localtime(&newt);
			if (newtmp != NULL)
				newtm = *newtmp;
			if ((tmp == NULL || newtmp == NULL) ? (tmp != newtmp) :
				(delta(&newtm, &tm) != (newt - t) ||
				newtm.tm_isdst != tm.tm_isdst ||
				strcmp(abbr(&newtm), buf) != 0)) {
					newt = hunt(argv[i], t, newt);
					newtmp = localtime(&newt);
					if (newtmp != NULL) {
						newtm = *newtmp;
						strncpy(buf,
							abbr(&newtm),
							(sizeof buf) - 1);
					}
			}
			t = newt;
			tm = newtm;
			tmp = newtmp;
		}
		t = absolute_max_time;
		t -= SECSPERHOUR * HOURSPERDAY;
		show(argv[i], t, TRUE);
		t += SECSPERHOUR * HOURSPERDAY;
		show(argv[i], t, TRUE);
	}
	if (fflush(stdout) || ferror(stdout))
		errx(EXIT_FAILURE, _("error writing standard output"));
	exit(EXIT_SUCCESS);
	/* If exit fails to exit... */
	return EXIT_FAILURE;
}