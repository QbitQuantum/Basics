int
main(int argc, char **argv)
{
	char *cp, **ap;
	int ch, disc;
	FILE *wfd = NULL;
	char *dialerstring = 0, buf[BUFSIZ];
	int unitnum, keepal = 0, outfill = 0;
	char unitname[32];
	char *password;
	char *upscript = NULL, *downscript = NULL;
	int first = 1, tries = 0;
	time_t fintimeout;
	long lpid;
	pid_t pid;
	struct termios t;
	int result;

	while ((ch = getopt(argc, argv, "dhlb:s:t:w:A:U:D:W:K:O:S:L")) != -1)
		switch (ch) {
		case 'd':
			debug = 1;
			break;
		case 'b':
			speed = atoi(optarg);
			break;
		case 's':
			if (diali >= MAXDIALS)
				errx(1, "max dial strings number (%d) exceeded", MAXDIALS);
			dials[diali++] = strdup(optarg);
			break;
		case 't':
			script_timeout = atoi(optarg);
			break;
		case 'w':
			wait_time = atoi(optarg);
			break;
		case 'W':
			MAXTRIES = atoi(optarg);
			break;
		case 'A':
			annex = strdup(optarg);
			break;
		case 'U':
			upscript = strdup(optarg);
			break;
		case 'D':
			downscript = strdup(optarg);
			break;
		case 'L':
			uucp_lock = 1;
			break;
		case 'l':
			modem_control = 0;
			break;
		case 'h':
			flowcontrol = FC_HW;
			break;
		case 'K':
			keepal = atoi(optarg);
			break;
		case 'O':
			outfill = atoi(optarg);
			break;
		case 'S':
			sl_unit = atoi(optarg);
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 3)
		usage();

	/*
	 * Copy these so they exist after we clobber them.
	 */
	devicename = strdup(argv[0]);
	username = strdup(argv[1]);
	password = strdup(argv[2]);

	/*
	 * Security hack.  Do not want private information such as the
	 * password and possible phone number to be left around.
	 * So we clobber the arguments.
	 */
	for (ap = argv - optind + 1; ap < argv + 3; ap++)
		for (cp = *ap; *cp != 0; cp++)
			*cp = '\0';

	openlog("startslip", LOG_PID|LOG_PERROR, LOG_DAEMON);

	if (debug)
		setbuf(stdout, NULL);

	signal(SIGTERM, sigterm);
	if ((dvname = strrchr(devicename, '/')) == NULL)
		dvname = devicename;
	else
		dvname++;

	result = snprintf(my_pidfile, sizeof(my_pidfile),
			  PIDFILE, _PATH_VARRUN, dvname);
	if (result < 0 || (unsigned int)result >= sizeof(my_pidfile))
		usage();

	if ((pfd = fopen(my_pidfile, "r")) != NULL) {
		if (fscanf(pfd, "%ld\n", &lpid) == 1) {
			pid = lpid;
			if (pid == lpid && pid > 0)
				kill(pid, SIGTERM);
		}
		fclose(pfd);
		pfd = NULL;     /* not remove pidfile yet */
		sleep(5);       /* allow down script to be completed */
	} else
restart:
	signal(SIGHUP, SIG_IGN);
	signal(SIGURG, SIG_IGN);
	hup = 0;
	if (wfd) {
		printd("fclose, ");
		fclose(wfd);
		conn_time = time(NULL) - start_time;
		if (uucp_lock)
			uu_unlock(dvname);
		locked = 0;
		wfd = NULL;
		fd = -1;
		sleep(5);
	} else if (fd >= 0) {
		printd("close, ");
		close(fd);
		conn_time = time(NULL) - start_time;
		if (uucp_lock)
			uu_unlock(dvname);
		locked = 0;
		fd = -1;
		sleep(5);
	}
	if (logged_in) {
		syslog(LOG_INFO, "%s: connection time elapsed: %ld secs",
		    username, (long)conn_time);
		sprintf(buf, "LINE=%d %s %s down",
		diali ? (dialc - 1) % diali : 0,
		downscript ? downscript : "/sbin/ifconfig" , unitname);
		system(buf);
		logged_in = 0;
	}
	if (terminate)
		down(0);
	tries++;
	if (MAXTRIES > 0 && tries > MAXTRIES) {
		syslog(LOG_ERR, "%s: exiting login after %d tries", username, tries);
		/* ???
		if (first)
		*/
			down(3);
	}
	if (tries > 1) {
		syslog(LOG_INFO, "%s: sleeping %d seconds (%d tries)",
			username, wait_time * (tries - 1), tries);
		sleep(wait_time * (tries - 1));
		if (terminate)
			goto restart;
	}

	if (daemon(1, debug) < 0) {
		syslog(LOG_ERR, "%s: daemon: %m", username);
		down(2);
	}

	pid = getpid();
	printd("restart: pid %ld: ", (long)pid);
	if ((pfd = fopen(my_pidfile, "w")) != NULL) {
		fprintf(pfd, "%ld\n", (long)pid);
		fclose(pfd);
	}
	printd("open");
	if (uucp_lock) {
		int res;
		if ((res = uu_lock(dvname)) != UU_LOCK_OK) {
			if (res != UU_LOCK_INUSE)
				syslog(LOG_ERR, "uu_lock: %s", uu_lockerr(res));
			syslog(LOG_ERR, "%s: can't lock %s", username, devicename);
			goto restart;
		}
		locked = 1;
	}
	if ((fd = open(devicename, O_RDWR | O_NONBLOCK)) < 0) {
		syslog(LOG_ERR, "%s: open %s: %m", username, devicename);
		if (first)
			down(1);
		else {
			if (uucp_lock)
				uu_unlock(dvname);
			locked = 0;
			goto restart;
		}
	}
	printd(" %d", fd);
	signal(SIGHUP, sighup);
	if (ioctl(fd, TIOCSCTTY, 0) < 0) {
		syslog(LOG_ERR, "%s: ioctl (TIOCSCTTY): %m", username);
		down(2);
	}
	if (tcsetpgrp(fd, getpid()) < 0) {
		syslog(LOG_ERR, "%s: tcsetpgrp failed: %m", username);
		down(2);
	}
	printd(", ioctl\n");
	if (tcgetattr(fd, &t) < 0) {
		syslog(LOG_ERR, "%s: tcgetattr(%s): %m", username, devicename);
		down(2);
	}
	cfmakeraw(&t);
	switch (flowcontrol) {
	case FC_HW:
		t.c_cflag |= (CRTS_IFLOW|CCTS_OFLOW);
		break;
	case FC_NONE:
		t.c_cflag &= ~(CRTS_IFLOW|CCTS_OFLOW);
		break;
	}
	if (modem_control)
		t.c_cflag |= HUPCL;
	else
		t.c_cflag &= ~(HUPCL);
	t.c_cflag |= CLOCAL;    /* until modem commands passes */
	cfsetispeed(&t, speed);
	cfsetospeed(&t, speed);
	if (tcsetattr(fd, TCSAFLUSH, &t) < 0) {
		syslog(LOG_ERR, "%s: tcsetattr(%s): %m", username, devicename);
		down(2);
	}
	sleep(2);		/* wait for flakey line to settle */
	if (hup || terminate)
		goto restart;

	wfd = fdopen(fd, "w+");
	if (wfd == NULL) {
		syslog(LOG_ERR, "%s: can't fdopen %s: %m", username, devicename);
		down(2);
	}
	setbuf(wfd, NULL);

	if (diali > 0)
		dialerstring = dials[dialc++ % diali];
	if (dialerstring) {
		syslog(LOG_INFO, "%s: dialer string: %s\\r", username, dialerstring);
		fprintf(wfd, "%s\r", dialerstring);
	}
	printd("\n");

	fintimeout = time(NULL) + script_timeout;
	if (modem_control) {
		printd("waiting for carrier\n");
		while (time(NULL) < fintimeout && !carrier()) {
			sleep(1);
			if (hup || terminate)
				goto restart;
		}
		if (!carrier())
			goto restart;
		t.c_cflag &= ~(CLOCAL);
		if (tcsetattr(fd, TCSANOW, &t) < 0) {
			syslog(LOG_ERR, "%s: tcsetattr(%s): %m", username, devicename);
			down(2);
		}
		/* Only now we able to receive HUP on carrier drop! */
	}

	/*
	 * Log in
	 */
	printd("look for login: "******"slip\r");
				printd("Sent \"slip\"\n");
				continue;
			}
			if (bcmp(&buf[1], "sername:", 8) == 0) {
				fprintf(wfd, "%s\r", username);
				printd("Sent login: %s\n", username);
				continue;
			}
			if (bcmp(&buf[1], "assword:", 8) == 0) {
				fprintf(wfd, "%s\r", password);
				printd("Sent password: %s\n", password);
				break;
			}
		} else {
			if (strstr(&buf[1], "ogin:") != NULL) {
				fprintf(wfd, "%s\r", username);
				printd("Sent login: %s\n", username);
				continue;
			}
			if (strstr(&buf[1], "assword:") != NULL) {
				fprintf(wfd, "%s\r", password);
				printd("Sent password: %s\n", password);
				break;
			}
		}
	}

	sleep(5);       /* Wait until login completed */
	if (hup || terminate)
		goto restart;
	start_time = time(NULL);
	/*
	 * Attach
	 */
	printd("setd");
	disc = SLIPDISC;
	if (ioctl(fd, TIOCSETD, &disc) < 0) {
		syslog(LOG_ERR, "%s: ioctl (%s, TIOCSETD): %m",
		    username, devicename);
		down(2);
	}
	if (sl_unit >= 0 && ioctl(fd, SLIOCSUNIT, &sl_unit) < 0) {
		syslog(LOG_ERR, "%s: ioctl(SLIOCSUNIT): %m", username);
		down(2);
	}
	if (ioctl(fd, SLIOCGUNIT, &unitnum) < 0) {
		syslog(LOG_ERR, "%s: ioctl(SLIOCGUNIT): %m", username);
		down(2);
	}
	sprintf(unitname, "sl%d", unitnum);

	if (keepal > 0) {
		signal(SIGURG, sigurg);
		if (ioctl(fd, SLIOCSKEEPAL, &keepal) < 0) {
			syslog(LOG_ERR, "%s: ioctl(SLIOCSKEEPAL): %m", username);
			down(2);
		}
	}
	if (outfill > 0 && ioctl(fd, SLIOCSOUTFILL, &outfill) < 0) {
		syslog(LOG_ERR, "%s: ioctl(SLIOCSOUTFILL): %m", username);
		down(2);
	}

	sprintf(buf, "LINE=%d %s %s up",
		diali ? (dialc - 1) % diali : 0,
		upscript ? upscript : "/sbin/ifconfig" , unitname);
	system(buf);

	printd(", ready\n");
	if (!first)
		syslog(LOG_INFO, "%s: reconnected on %s (%d tries)", username, unitname, tries);
	else
		syslog(LOG_INFO, "%s: connected on %s", username, unitname);
	first = 0;
	tries = 0;
	logged_in = 1;
	while (hup == 0 && terminate == 0) {
		sigpause(0L);
		printd("sigpause return\n");
	}
	goto restart;
	return(0); /* not reached */
}