int
main(int argc, char **argv)
{
	int c, i;
	int tflag = 0, hflag = 0, cflag = 0, wflag = 0, nflag = 0;
	int count = 0, waittime = 0;
	char *memf = NULL, *nlistf = NULL;
	struct devstat_match *matches;
	struct itimerval alarmspec;
	int num_matches = 0;
	char errbuf[_POSIX2_LINE_MAX];
	kvm_t *kd = NULL;
	long generation;
	int num_devices_specified;
	int num_selected, num_selections;
	long select_generation;
	char **specified_devices;
	devstat_select_mode select_mode;
	float f;
	int havelast = 0;

	matches = NULL;
	maxshowdevs = 3;

	while ((c = getopt(argc, argv, "c:CdhIKM:n:N:ot:Tw:xz?")) != -1) {
		switch(c) {
			case 'c':
				cflag++;
				count = atoi(optarg);
				if (count < 1)
					errx(1, "count %d is < 1", count);
				break;
			case 'C':
				Cflag++;
				break;
			case 'd':
				dflag++;
				break;
			case 'h':
				hflag++;
				break;
			case 'I':
				Iflag++;
				break;
			case 'K':
				Kflag++;
				break;
			case 'M':
				memf = optarg;
				break;
			case 'n':
				nflag++;
				maxshowdevs = atoi(optarg);
				if (maxshowdevs < 0)
					errx(1, "number of devices %d is < 0",
					     maxshowdevs);
				break;
			case 'N':
				nlistf = optarg;
				break;
			case 'o':
				oflag++;
				break;
			case 't':
				tflag++;
				if (devstat_buildmatch(optarg, &matches,
						       &num_matches) != 0)
					errx(1, "%s", devstat_errbuf);
				break;
			case 'T':
				Tflag++;
				break;
			case 'w':
				wflag++;
				f = atof(optarg);
				waittime = f * 1000;
				if (waittime < 1)
					errx(1, "wait time is < 1ms");
				break;
			case 'x':
				xflag++;
				break;
			case 'z':
				zflag++;
				break;
			default:
				usage();
				exit(1);
				break;
		}
	}

	argc -= optind;
	argv += optind;

	if (nlistf != NULL || memf != NULL) {
		kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, errbuf);

		if (kd == NULL)
			errx(1, "kvm_openfiles: %s", errbuf);

		if (kvm_nlist(kd, namelist) == -1)
			errx(1, "kvm_nlist: %s", kvm_geterr(kd));
	}

	/*
	 * Make sure that the userland devstat version matches the kernel
	 * devstat version.  If not, exit and print a message informing
	 * the user of his mistake.
	 */
	if (devstat_checkversion(kd) < 0)
		errx(1, "%s", devstat_errbuf);

	/*
	 * Make sure Tflag and/or Cflag are set if dflag == 0.  If dflag is
	 * greater than 0, they may be 0 or non-zero.
	 */
	if (dflag == 0 && xflag == 0) {
		Cflag = 1;
		Tflag = 1;
	}

	/* find out how many devices we have */
	if ((num_devices = devstat_getnumdevs(kd)) < 0)
		err(1, "can't get number of devices");

	/*
	 * Figure out how many devices we should display.
	 */
	if (nflag == 0) {
		if (xflag > 0)
			maxshowdevs = num_devices;
		else if (oflag > 0) {
			if ((dflag > 0) && (Cflag == 0) && (Tflag == 0))
				maxshowdevs = 5;
			else if ((dflag > 0) && (Tflag > 0) && (Cflag == 0))
				maxshowdevs = 5;
			else
				maxshowdevs = 4;
		} else {
			if ((dflag > 0) && (Cflag == 0))
				maxshowdevs = 4;
			else
				maxshowdevs = 3;
		}
	}

	cur.dinfo = (struct devinfo *)calloc(1, sizeof(struct devinfo));
	if (cur.dinfo == NULL)
		err(1, "calloc failed");

	last.dinfo = (struct devinfo *)calloc(1, sizeof(struct devinfo));
	if (last.dinfo == NULL)
		err(1, "calloc failed");

	/*
	 * Grab all the devices.  We don't look to see if the list has
	 * changed here, since it almost certainly has.  We only look for
	 * errors.
	 */
	if (devstat_getdevs(kd, &cur) == -1)
		errx(1, "%s", devstat_errbuf);

	num_devices = cur.dinfo->numdevs;
	generation = cur.dinfo->generation;

	/*
	 * If the user specified any devices on the command line, see if
	 * they are in the list of devices we have now.
	 */
	specified_devices = (char **)malloc(sizeof(char *));
	if (specified_devices == NULL)
		err(1, "malloc failed");

	for (num_devices_specified = 0; *argv; ++argv) {
		if (isdigit(**argv))
			break;
		num_devices_specified++;
		specified_devices = (char **)realloc(specified_devices,
						     sizeof(char *) *
						     num_devices_specified);
		if (specified_devices == NULL)
			err(1, "realloc failed");

		specified_devices[num_devices_specified - 1] = *argv;

	}
	if (nflag == 0 && maxshowdevs < num_devices_specified)
		maxshowdevs = num_devices_specified;

	dev_select = NULL;

	if ((num_devices_specified == 0) && (num_matches == 0))
		select_mode = DS_SELECT_ADD;
	else
		select_mode = DS_SELECT_ONLY;

	/*
	 * At this point, selectdevs will almost surely indicate that the
	 * device list has changed, so we don't look for return values of 0
	 * or 1.  If we get back -1, though, there is an error.
	 */
	if (devstat_selectdevs(&dev_select, &num_selected,
			       &num_selections, &select_generation, generation,
			       cur.dinfo->devices, num_devices, matches,
			       num_matches, specified_devices,
			       num_devices_specified, select_mode, maxshowdevs,
			       hflag) == -1)
		errx(1, "%s", devstat_errbuf);

	/*
	 * Look for the traditional wait time and count arguments.
	 */
	if (*argv) {
		f = atof(*argv);
		waittime = f * 1000;

		/* Let the user know he goofed, but keep going anyway */
		if (wflag != 0)
			warnx("discarding previous wait interval, using"
			      " %g instead", waittime / 1000.0);
		wflag++;

		if (*++argv) {
			count = atoi(*argv);
			if (cflag != 0)
				warnx("discarding previous count, using %d"
				      " instead", count);
			cflag++;
		} else
			count = -1;
	}

	/*
	 * If the user specified a count, but not an interval, we default
	 * to an interval of 1 second.
	 */
	if ((wflag == 0) && (cflag > 0))
		waittime = 1 * 1000;

	/*
	 * If the user specified a wait time, but not a count, we want to
	 * go on ad infinitum.  This can be redundant if the user uses the
	 * traditional method of specifying the wait, since in that case we
	 * already set count = -1 above.  Oh well.
	 */
	if ((wflag > 0) && (cflag == 0))
		count = -1;

	bzero(cur.cp_time, sizeof(cur.cp_time));
	cur.tk_nout = 0;
	cur.tk_nin = 0;

	/*
	 * Set the snap time to the system boot time (ie: zero), so the
	 * stats are calculated since system boot.
	 */
	cur.snap_time = 0;

	/*
	 * If the user stops the program (control-Z) and then resumes it,
	 * print out the header again.
	 */
	(void)signal(SIGCONT, needhdr);

	/*
	 * If our standard output is a tty, then install a SIGWINCH handler
	 * and set wresized so that our first iteration through the main
	 * iostat loop will peek at the terminal's current rows to find out
	 * how many lines can fit in a screenful of output.
	 */
	if (isatty(fileno(stdout)) != 0) {
		wresized = 1;
		(void)signal(SIGWINCH, needresize);
	} else {
		wresized = 0;
		wrows = IOSTAT_DEFAULT_ROWS;
	}

	/*
	 * Register a SIGINT handler so that we can print out final statistics
	 * when we get that signal
	 */
	(void)signal(SIGINT, needreturn);

	/*
	 * Register a SIGALRM handler to implement sleeps if the user uses the
	 * -c or -w options
	 */
	(void)signal(SIGALRM, alarm_clock);
	alarmspec.it_interval.tv_sec = waittime / 1000;
	alarmspec.it_interval.tv_usec = 1000 * (waittime % 1000);
	alarmspec.it_value.tv_sec = waittime / 1000;
	alarmspec.it_value.tv_usec = 1000 * (waittime % 1000);
	setitimer(ITIMER_REAL, &alarmspec, NULL);

	for (headercount = 1;;) {
		struct devinfo *tmp_dinfo;
		long tmp;
		long double etime;
		sigset_t sigmask, oldsigmask;

		if (Tflag > 0) {
			if ((readvar(kd, "kern.tty_nin", X_TTY_NIN, &cur.tk_nin,
			     sizeof(cur.tk_nin)) != 0)
			 || (readvar(kd, "kern.tty_nout", X_TTY_NOUT,
			     &cur.tk_nout, sizeof(cur.tk_nout))!= 0)) {
				Tflag = 0;
				warnx("disabling TTY statistics");
			}
		 }

		if (Cflag > 0) {
			if (kd == NULL) {
				if (readvar(kd, "kern.cp_time", 0,
				    &cur.cp_time, sizeof(cur.cp_time)) != 0)
					Cflag = 0;
			} else {
				if (kvm_getcptime(kd, cur.cp_time) < 0) {
					warnx("kvm_getcptime: %s",
					    kvm_geterr(kd));
					Cflag = 0;
				}
			}
			if (Cflag == 0)
				warnx("disabling CPU time statistics");
		}

		if (!--headercount) {
			phdr();
			if (wresized != 0)
				doresize();
			headercount = wrows;
		}

		tmp_dinfo = last.dinfo;
		last.dinfo = cur.dinfo;
		cur.dinfo = tmp_dinfo;

		last.snap_time = cur.snap_time;

		/*
		 * Here what we want to do is refresh our device stats.
		 * devstat_getdevs() returns 1 when the device list has changed.
		 * If the device list has changed, we want to go through
		 * the selection process again, in case a device that we
		 * were previously displaying has gone away.
		 */
		switch (devstat_getdevs(kd, &cur)) {
		case -1:
			errx(1, "%s", devstat_errbuf);
			break;
		case 1: {
			int retval;

			num_devices = cur.dinfo->numdevs;
			generation = cur.dinfo->generation;
			retval = devstat_selectdevs(&dev_select, &num_selected,
						    &num_selections,
						    &select_generation,
						    generation,
						    cur.dinfo->devices,
						    num_devices, matches,
						    num_matches,
						    specified_devices,
						    num_devices_specified,
						    select_mode, maxshowdevs,
						    hflag);
			switch(retval) {
			case -1:
				errx(1, "%s", devstat_errbuf);
				break;
			case 1:
				phdr();
				if (wresized != 0)
					doresize();
				headercount = wrows;
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}

		/*
		 * We only want to re-select devices if we're in 'top'
		 * mode.  This is the only mode where the devices selected
		 * could actually change.
		 */
		if (hflag > 0) {
			int retval;
			retval = devstat_selectdevs(&dev_select, &num_selected,
						    &num_selections,
						    &select_generation,
						    generation,
						    cur.dinfo->devices,
						    num_devices, matches,
						    num_matches,
						    specified_devices,
						    num_devices_specified,
						    select_mode, maxshowdevs,
						    hflag);
			switch(retval) {
			case -1:
				errx(1,"%s", devstat_errbuf);
				break;
			case 1:
				phdr();
				if (wresized != 0)
					doresize();
				headercount = wrows;
				break;
			default:
				break;
			}
		}

		if (Tflag > 0) {
			tmp = cur.tk_nin;
			cur.tk_nin -= last.tk_nin;
			last.tk_nin = tmp;
			tmp = cur.tk_nout;
			cur.tk_nout -= last.tk_nout;
			last.tk_nout = tmp;
		}

		etime = cur.snap_time - last.snap_time;

		if (etime == 0.0)
			etime = 1.0;

		for (i = 0; i < CPUSTATES; i++) {
			tmp = cur.cp_time[i];
			cur.cp_time[i] -= last.cp_time[i];
			last.cp_time[i] = tmp;
		}

		if (xflag == 0 && Tflag > 0)
			printf("%4.0Lf %5.0Lf", cur.tk_nin / etime,
			    cur.tk_nout / etime);

		devstats(hflag, etime, havelast);

		if (xflag == 0) {
			if (Cflag > 0)
				cpustats();

			printf("\n");
		}
		fflush(stdout);

		if ((count >= 0 && --count <= 0) || return_requested)
			break;

		/*
		 * Use sigsuspend to safely sleep until either signal is
		 * received
		 */
		alarm_rang = 0;
		sigemptyset(&sigmask);
		sigaddset(&sigmask, SIGINT);
		sigaddset(&sigmask, SIGALRM);
		sigprocmask(SIG_BLOCK, &sigmask, &oldsigmask);
		while (! (alarm_rang || return_requested) ) {
			sigsuspend(&oldsigmask);
		}
		sigprocmask(SIG_UNBLOCK, &sigmask, NULL);

		havelast = 1;
	}

	exit(0);
}