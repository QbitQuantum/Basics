/*@ -compdestroy @*/
int main(int argc, char **argv)
{
    char buf[4096];
    bool timestamp = false;
    char *format = "%F %T";
    char tmstr[200];
    bool daemonize = false;
    bool binary = false;
    bool sleepy = false;
    bool new_line = true;
    bool raw = false;
    bool watch = false;
    bool profile = false;
    int option_u = 0;                   // option to show uSeconds
    long count = -1;
    int option;
    unsigned int vflag = 0, l = 0;
    FILE *fp;
    unsigned int flags;
    fd_set fds;

    struct fixsource_t source;
    char *serialport = NULL;
    char *outfile = NULL;

    /*@-branchstate@*/
    flags = WATCH_ENABLE;
    while ((option = getopt(argc, argv, "?dD:lhrRwStT:vVn:s:o:pPu2")) != -1) {
	switch (option) {
	case 'D':
	    debug = atoi(optarg);
#ifdef CLIENTDEBUG_ENABLE
	    gps_enable_debug(debug, stderr);
#endif /* CLIENTDEBUG_ENABLE */
	    break;
	case 'n':
	    count = strtol(optarg, 0, 0);
	    break;
	case 'r':
	    raw = true;
	    /*
	     * Yes, -r invokes NMEA mode rather than proper raw mode.
	     * This emulates the behavior under the old protocol.
	     */
	    flags |= WATCH_NMEA;
	    break;
	case 'R':
	    flags |= WATCH_RAW;
	    binary = true;
	    break;
	case 'd':
	    daemonize = true;
	    break;
	case 'l':
	    sleepy = true;
	    break;
	case 't':
	    timestamp = true;
	    break;
	case 'T':
	    timestamp = true;
	    format = optarg;
	    break;
	case 'u':
	    timestamp = true;
	    option_u++;
	    break;
	case 'v':
	    vflag++;
	    break;
	case 'w':
	    flags |= WATCH_JSON;
	    watch = true;
	    break;
	case 'S':
	    flags |= WATCH_SCALED;
	    break;
	case 'p':
	    profile = true;
	    break;
	case 'P':
	    flags |= WATCH_PPS;
	    break;
	case 'V':
	    (void)fprintf(stderr, "%s: %s (revision %s)\n",
			  argv[0], VERSION, REVISION);
	    exit(EXIT_SUCCESS);
	case 's':
	    serialport = optarg;
	    break;
	case 'o':
	    outfile = optarg;
	    break;
	case '2':
	    flags |= WATCH_SPLIT24;
	    break;
	case '?':
	case 'h':
	default:
	    usage();
	    exit(EXIT_FAILURE);
	}
    }
    /*@+branchstate@*/

    /* Grok the server, port, and device. */
    if (optind < argc) {
	gpsd_source_spec(argv[optind], &source);
    } else
	gpsd_source_spec(NULL, &source);

    if (serialport != NULL && !raw) {
	(void)fprintf(stderr, "gpspipe: use of '-s' requires '-r'.\n");
	exit(EXIT_FAILURE);
    }

    if (outfile == NULL && daemonize) {
	(void)fprintf(stderr, "gpspipe: use of '-d' requires '-o'.\n");
	exit(EXIT_FAILURE);
    }

    if (!raw && !watch && !binary) {
	(void)fprintf(stderr,
		      "gpspipe: one of '-R', '-r', or '-w' is required.\n");
	exit(EXIT_FAILURE);
    }

    /* Daemonize if the user requested it. */
    /*@ -unrecog @*/
    if (daemonize)
	if (daemon(0, 0) != 0)
	    (void)fprintf(stderr,
			  "gpspipe: demonization failed: %s\n",
			  strerror(errno));
    /*@ +unrecog @*/

    /* Sleep for ten seconds if the user requested it. */
    if (sleepy)
	(void)sleep(10);

    /* Open the output file if the user requested it.  If the user
     * requested '-R', we use the 'b' flag in fopen() to "do the right
     * thing" in non-linux/unix OSes. */
    if (outfile == NULL) {
	fp = stdout;
    } else {
	if (binary)
	    fp = fopen(outfile, "wb");
	else
	    fp = fopen(outfile, "w");

	if (fp == NULL) {
	    (void)fprintf(stderr,
			  "gpspipe: unable to open output file:  %s\n",
			  outfile);
	    exit(EXIT_FAILURE);
	}
    }

    /* Open the serial port and set it up. */
    if (serialport)
	open_serial(serialport);

    /*@ -nullpass -onlytrans @*/
    if (gps_open(source.server, source.port, &gpsdata) != 0) {
	(void)fprintf(stderr,
		      "gpspipe: could not connect to gpsd %s:%s, %s(%d)\n",
		      source.server, source.port, gps_errstr(errno), errno);
	exit(EXIT_FAILURE);
    }
    /*@ +nullpass +onlytrans @*/

    if (profile)
	flags |= WATCH_TIMING;
    if (source.device != NULL)
	flags |= WATCH_DEVICE;
    (void)gps_stream(&gpsdata, flags, source.device);

    if ((isatty(STDERR_FILENO) == 0) || daemonize)
	vflag = 0;

    for (;;) {
	int r = 0;
	struct timeval tv;

	tv.tv_sec = 0;
	tv.tv_usec = 100000;
	FD_ZERO(&fds);
	FD_SET(gpsdata.gps_fd, &fds);
	errno = 0;
	r = select(gpsdata.gps_fd+1, &fds, NULL, NULL, &tv);
	if (r == -1 && errno != EINTR) {
	    (void)fprintf(stderr, "gpspipe: select error %s(%d)\n",
			  strerror(errno), errno);
	    exit(EXIT_FAILURE);
	} else if (r == 0)
		continue;

	if (vflag)
	    spinner(vflag, l++);

	/* reading directly from the socket avoids decode overhead */
	errno = 0;
	r = (int)read(gpsdata.gps_fd, buf, sizeof(buf));
	if (r > 0) {
	    int i = 0;
	    int j = 0;
	    for (i = 0; i < r; i++) {
		char c = buf[i];
		if (j < (int)(sizeof(serbuf) - 1)) {
		    serbuf[j++] = buf[i];
		}
		if (new_line && timestamp) {
		    char tmstr_u[20];            // time with "usec" resolution
		    struct timeval now;
		    struct tm *tmp_now;

		    (void)gettimeofday( &now, NULL );
		    tmp_now = localtime((time_t *)&(now.tv_sec));
		    (void)strftime(tmstr, sizeof(tmstr), format, tmp_now);
		    new_line = 0;

		    switch( option_u ) {
		    case 2:
			(void)snprintf(tmstr_u, sizeof(tmstr_u), 
				       " %ld.%06ld", now.tv_sec, now.tv_usec);
			break;
		    case 1:
			(void)snprintf(tmstr_u, sizeof(tmstr_u), 
				       ".%06ld", now.tv_usec);
			break;
		    default:
			*tmstr_u = '\0';
			break;
		    }

		    if (fprintf(fp, "%.24s%s: ", tmstr, tmstr_u) <= 0) {
			(void)fprintf(stderr,
				      "gpspipe: write error, %s(%d)\n",
				      strerror(errno), errno);
			exit(EXIT_FAILURE);
		    }
		}
		if (fputc(c, fp) == EOF) {
		    fprintf(stderr, "gpspipe: Write Error, %s(%d)\n",
			    strerror(errno), errno);
		    exit(EXIT_FAILURE);
		}

		if (c == '\n') {
		    if (serialport != NULL) {
			if (write(fd_out, serbuf, (size_t) j) == -1) {
			    fprintf(stderr,
				    "gpspipe: Serial port write Error, %s(%d)\n",
				    strerror(errno), errno);
			    exit(EXIT_FAILURE);
			}
			j = 0;
		    }

		    new_line = true;
		    /* flush after every good line */
		    if (fflush(fp)) {
			(void)fprintf(stderr,
				      "gpspipe: fflush Error, %s(%d)\n",
				      strerror(errno), errno);
			exit(EXIT_FAILURE);
		    }
		    if (count > 0) {
			if (0 >= --count) {
			    /* completed count */
			    exit(EXIT_SUCCESS);
			}
		    }
		}
	    }
	} else {
	    if (r == -1) {
		if (errno == EAGAIN)
		    continue;
		else
		    (void)fprintf(stderr, "gpspipe: read error %s(%d)\n",
			      strerror(errno), errno);
		exit(EXIT_FAILURE);
	    } else {
		exit(EXIT_SUCCESS);
	    }
	}
    }

#ifdef __UNUSED__
    if (serialport != NULL) {
	/* Restore the old serial port settings. */
	if (tcsetattr(fd_out, TCSANOW, &oldtio) != 0) {
	    (void)fprintf(stderr, "Error restoring serial port settings\n");
	    exit(EXIT_FAILURE);
	}
    }
#endif /* __UNUSED__ */

    exit(EXIT_SUCCESS);
}