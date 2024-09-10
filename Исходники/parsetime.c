time_t
parsetime(int argc, char **argv)
{
	/*
	 * Do the argument parsing, die if necessary, and return the
	 * time the job should be run.
	 */
	time_t nowtimer, runtimer;
	struct tm nowtime, runtime;
	int hr = 0; /* this MUST be initialized to zero for
	               midnight/noon/teatime */

	nowtimer = time(NULL);
	nowtime = *localtime(&nowtimer);

	runtime = nowtime;
	runtime.tm_sec = 0;

	if (argc <= optind)
		usage();

	init_scanner(argc - optind, argv + optind);

	switch (token()) {
	case NOW:
		if (scc < 1)
			return nowtimer;

		/* now is optional prefix for PLUS tree */
		expect(PLUS);
		/*FALLTHROUGH*/
	case PLUS:
		plus(&runtime);
		break;

	case NUMBER:
		tod(&runtime);
		month(&runtime);
		break;

		/*
		 * evil coding for TEATIME|NOON|MIDNIGHT - we've initialised
		 * hr to zero up above, then fall into this case in such a
		 * way so we add +12 +4 hours to it for teatime, +12 hours
		 * to it for noon, and nothing at all for midnight, then
		 * set our runtime to that hour before leaping into the
		 * month scanner
		 */
	case TEATIME:
		hr += 4;
		/*FALLTHROUGH*/
	case NOON:
		hr += 12;
		/*FALLTHROUGH*/
	case MIDNIGHT:
		if (runtime.tm_hour >= hr) {
			runtime.tm_mday++;
			runtime.tm_wday++;
		}
		runtime.tm_hour = hr;
		runtime.tm_min = 0;
		(void)token();
		/*FALLTHROUGH*/	/* fall through to month setting */
	default:
		month(&runtime);
		break;
	}
	expect(TOKEOF);

	/*
	 * adjust for daylight savings time
	 */
	runtime.tm_isdst = -1;
	runtimer = mktime(&runtime);

	if (runtimer == (time_t)-1)
		panic("Invalid time");

	if (nowtimer > runtimer)
		panic("Trying to travel back in time");

	return runtimer;
}