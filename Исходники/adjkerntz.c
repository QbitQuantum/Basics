int
main(int argc, char *argv[])
{
	struct tm local;
	struct timeval tv, *stv;
	struct timezone tz, *stz;
	int kern_offset, wall_clock, disrtcset;
	size_t len;
	/* Avoid time_t here, can be unsigned long or worse */
	long offset, localsec, diff;
	time_t initial_sec, final_sec;
	int ch;
	int initial_isdst = -1, final_isdst;
	int need_restore = False, sleep_mode = False, looping,
	    init = Unknown;
	sigset_t mask, emask;

	while ((ch = getopt(argc, argv, "ais")) != -1)
		switch((char)ch) {
		case 'i':               /* initial call, save offset */
			if (init != Unknown)
				usage();
			init = True;
			break;
		case 'a':               /* adjustment call, use saved offset */
			if (init != Unknown)
				usage();
			init = False;
			break;
		case 's':
			sleep_mode = True;
			break;
		default:
			usage();
		}
	if (init == Unknown)
		usage();

	if (access(_PATH_CLOCK, F_OK) != 0)
		return 0;

	if (init)
		sleep_mode = True;

	sigemptyset(&mask);
	sigemptyset(&emask);
	sigaddset(&mask, SIGTERM);

	openlog("adjkerntz", LOG_PID|LOG_PERROR, LOG_DAEMON);

	(void) signal(SIGHUP, SIG_IGN);

	if (init && daemon(0,
#ifdef DEBUG
	    1
#else
	    0
#endif
	    )) {
		syslog(LOG_ERR, "daemon: %m");
		return 1;
	}

again:
	(void) sigprocmask(SIG_BLOCK, &mask, NULL);
	(void) signal(SIGTERM, fake);

	diff = 0;
	stv = NULL;
	stz = NULL;
	looping = False;

	wall_clock = (access(_PATH_CLOCK, F_OK) == 0);
	if (init && !sleep_mode) {
		init = False;
		if (!wall_clock)
			return 0;
	}

	tzset();

	len = sizeof(kern_offset);
	if (sysctlbyname("machdep.adjkerntz", &kern_offset, &len, NULL, 0) == -1) {
		syslog(LOG_ERR, "sysctl(\"machdep.adjkerntz\"): %m");
		return 1;
	}

/****** Critical section, do all things as fast as possible ******/

	/* get local CMOS clock and possible kernel offset */
	if (gettimeofday(&tv, &tz)) {
		syslog(LOG_ERR, "gettimeofday: %m");
		return 1;
	}

	/* get the actual local timezone difference */
	initial_sec = tv.tv_sec;

recalculate:
	local = *localtime(&initial_sec);
	if (diff == 0)
		initial_isdst = local.tm_isdst;
	local.tm_isdst = initial_isdst;

	/* calculate local CMOS diff from GMT */

	localsec = mktime(&local);
	if (localsec == -1) {
		/*
		 * XXX user can only control local time, and it is
		 * unacceptable to fail here for init.  2:30 am in the
		 * middle of the nonexistent hour means 3:30 am.
		 */
		if (!sleep_mode) {
			syslog(LOG_WARNING,
			"Warning: nonexistent local time, try to run later.");
			syslog(LOG_WARNING, "Giving up.");
			return 1;
		}
		syslog(LOG_WARNING,
			"Warning: nonexistent local time.");
		syslog(LOG_WARNING, "Will retry after %d minutes.",
			REPORT_PERIOD / 60);
		(void) signal(SIGTERM, SIG_DFL);
		(void) sigprocmask(SIG_UNBLOCK, &mask, NULL);
		(void) sleep(REPORT_PERIOD);
		goto again;
	}
	offset = -local.tm_gmtoff;
#ifdef DEBUG
	fprintf(stderr, "Initial offset: %ld secs\n", offset);
#endif

	/* correct the kerneltime for this diffs */
	/* subtract kernel offset, if present, old offset too */

	diff = offset - tz.tz_minuteswest * 60 - kern_offset;

	if (diff != 0) {
#ifdef DEBUG
		fprintf(stderr, "Initial diff: %ld secs\n", diff);
#endif
		/* Yet one step for final time */

		final_sec = initial_sec + diff;

		/* get the actual local timezone difference */
		local = *localtime(&final_sec);
		final_isdst = diff < 0 ? initial_isdst : local.tm_isdst;
		if (diff > 0 && initial_isdst != final_isdst) {
			if (looping)
				goto bad_final;
			looping = True;
			initial_isdst = final_isdst;
			goto recalculate;
		}
		local.tm_isdst =  final_isdst;

		localsec = mktime(&local);
		if (localsec == -1) {
		bad_final:
			/*
			 * XXX as above.  The user has even less control,
			 * but perhaps we never get here.
			 */
			if (!sleep_mode) {
				syslog(LOG_WARNING,
					"Warning: nonexistent final local time, try to run later.");
				syslog(LOG_WARNING, "Giving up.");
				return 1;
			}
			syslog(LOG_WARNING,
				"Warning: nonexistent final local time.");
			syslog(LOG_WARNING, "Will retry after %d minutes.",
				REPORT_PERIOD / 60);
			(void) signal(SIGTERM, SIG_DFL);
			(void) sigprocmask(SIG_UNBLOCK, &mask, NULL);
			(void) sleep(REPORT_PERIOD);
			goto again;
		}
		offset = -local.tm_gmtoff;
#ifdef DEBUG
		fprintf(stderr, "Final offset: %ld secs\n", offset);
#endif

		/* correct the kerneltime for this diffs */
		/* subtract kernel offset, if present, old offset too */

		diff = offset - tz.tz_minuteswest * 60 - kern_offset;

		if (diff != 0) {
#ifdef DEBUG
			fprintf(stderr, "Final diff: %ld secs\n", diff);
#endif
			/*
			 * stv is abused as a flag.  The important value
			 * is in `diff'.
			 */
			stv = &tv;
		}
	}

	if (tz.tz_dsttime != 0 || tz.tz_minuteswest != 0) {
		tz.tz_dsttime = tz.tz_minuteswest = 0;  /* zone info is garbage */
		stz = &tz;
	}
	if (!wall_clock && stz == NULL)
		stv = NULL;

	/* if init or UTC clock and offset/date will be changed, */
	/* disable RTC modification for a while.                      */

	if (   (init && stv != NULL)
	    || ((init || !wall_clock) && kern_offset != offset)
	   ) {
		len = sizeof(disrtcset);
		if (sysctlbyname("machdep.disable_rtc_set", &disrtcset, &len, NULL, 0) == -1) {
			syslog(LOG_ERR, "sysctl(get: \"machdep.disable_rtc_set\"): %m");
			return 1;
		}
		if (disrtcset == 0) {
			disrtcset = 1;
			need_restore = True;
			if (sysctlbyname("machdep.disable_rtc_set", NULL, NULL, &disrtcset, len) == -1) {
				syslog(LOG_ERR, "sysctl(set: \"machdep.disable_rtc_set\"): %m");
				return 1;
			}
		}
	}

	if (   (init && (stv != NULL || stz != NULL))
	    || (stz != NULL && stv == NULL)
	   ) {
		if (stv != NULL) {
			/*
			 * Get the time again, as close as possible to
			 * adjusting it, to minimise drift.
			 * XXX we'd better not fail between here and
			 * restoring disrtcset, since we don't clean up
			 * anything.
			 */
			if (gettimeofday(&tv, (struct timezone *)NULL)) {
				syslog(LOG_ERR, "gettimeofday: %m");
				return 1;
			}
			tv.tv_sec += diff;
			stv = &tv;
		}
		if (settimeofday(stv, stz)) {
			syslog(LOG_ERR, "settimeofday: %m");
			return 1;
		}
	}

	/* setting machdep.adjkerntz have a side effect: resettodr(), which */
	/* can be disabled by machdep.disable_rtc_set, so if init or UTC clock    */
	/* -- don't write RTC, else write RTC.                          */

	if (kern_offset != offset) {
		kern_offset = offset;
		len = sizeof(kern_offset);
		if (sysctlbyname("machdep.adjkerntz", NULL, NULL, &kern_offset, len) == -1) {
			syslog(LOG_ERR, "sysctl(set: \"machdep.adjkerntz\"): %m");
			return 1;
		}
	}

	len = sizeof(wall_clock);
	if (sysctlbyname("machdep.wall_cmos_clock",  NULL, NULL, &wall_clock, len) == -1) {
		syslog(LOG_ERR, "sysctl(set: \"machdep.wall_cmos_clock\"): %m");
		return 1;
	}

	if (need_restore) {
		need_restore = False;
		disrtcset = 0;
		len = sizeof(disrtcset);
		if (sysctlbyname("machdep.disable_rtc_set", NULL, NULL, &disrtcset, len) == -1) {
			syslog(LOG_ERR, "sysctl(set: \"machdep.disable_rtc_set\"): %m");
			return 1;
		}
	}

/****** End of critical section ******/

	if (init && wall_clock) {
		sleep_mode = False;
		/* wait for signals and acts like -a */
		(void) sigsuspend(&emask);
		goto again;
	}

	return 0;
}