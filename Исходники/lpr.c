int
main(int argc, char *argv[])
{
	struct passwd *pw;
	struct group *gptr;
	const char *arg, *cp, *printer;
	char *p;
	char buf[BUFSIZ];
	int c, i, f, errs;
	int	 ret, didlink;
	struct stat stb;
	struct stat statb1, statb2;
	struct printer myprinter, *pp = &myprinter;

	printer = NULL;
	euid = geteuid();
	uid = getuid();
	PRIV_END
	if (signal(SIGHUP, SIG_IGN) != SIG_IGN)
		signal(SIGHUP, cleanup);
	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		signal(SIGINT, cleanup);
	if (signal(SIGQUIT, SIG_IGN) != SIG_IGN)
		signal(SIGQUIT, cleanup);
	if (signal(SIGTERM, SIG_IGN) != SIG_IGN)
		signal(SIGTERM, cleanup);

	progname = argv[0];
	gethostname(local_host, sizeof(local_host));
	openlog("lpd", 0, LOG_LPR);

	errs = 0;
	while ((c = getopt(argc, argv,
			   ":#:1:2:3:4:C:J:L:P:T:U:Z:cdfghi:lnmprstvw:"))
	       != -1)
		switch (c) {
		case '#':		/* n copies */
			i = strtol(optarg, &p, 10);
			if (*p)
				errx(1, "Bad argument to -#, number expected");
			if (i > 0)
				ncopies = i;
			break;

		case '1':		/* troff fonts */
		case '2':
		case '3':
		case '4':
			fonts[optopt - '1'] = optarg;
			break;

		case 'C':		/* classification spec */
			hdr++;
			class = optarg;
			break;

		case 'J':		/* job name */
			hdr++;
			jobname = optarg;
			break;

		case 'P':		/* specifiy printer name */
			printer = optarg;
			break;

		case 'L':               /* pr's locale */
			locale = optarg;
			break;

		case 'T':		/* pr's title line */
			title = optarg;
			break;

		case 'U':		/* user name */
			hdr++;
			Uflag = optarg;
			break;

		case 'Z':
			Zflag = optarg;
			break;

		case 'c':		/* print cifplot output */
		case 'd':		/* print tex output (dvi files) */
		case 'g':		/* print graph(1G) output */
		case 'l':		/* literal output */
		case 'n':		/* print ditroff output */
		case 't':		/* print troff output (cat files) */
		case 'p':		/* print using ``pr'' */
		case 'v':		/* print vplot output */
			format = optopt;
			break;

		case 'f':		/* print fortran output */
			format = 'r';
			break;

		case 'h':		/* nulifiy header page */
			hdr = 0;
			break;

		case 'i':		/* indent output */
			iflag++;
			indent = strtol(optarg, &p, 10);
			if (*p)
				errx(1, "Bad argument to -i, number expected");
			break;

		case 'm':		/* send mail when done */
			mailflg++;
			break;

		case 'q':		/* just queue job */
			qflag++;
			break;

		case 'r':		/* remove file when done */
			rflag++;
			break;

		case 's':		/* try to link files */
			sflag++;
			break;

		case 'w':		/* versatec page width */
			width = optarg;
			break;

		case ':':		/* catch "missing argument" error */
			if (optopt == 'i') {
				iflag++; /* -i without args is valid */
				indent = 8;
			} else
				errs++;
			break;

		default:
			errs++;
		}
	argc -= optind;
	argv += optind;
	if (errs)
		usage();
	if (printer == NULL && (printer = getenv("PRINTER")) == NULL)
		printer = DEFLP;
	chkprinter(printer, pp);
	if (pp->no_copies && ncopies > 1)
		errx(1, "multiple copies are not allowed");
	if (pp->max_copies > 0 && ncopies > pp->max_copies)
		errx(1, "only %ld copies are allowed", pp->max_copies);
	/*
	 * Get the identity of the person doing the lpr using the same
	 * algorithm as lprm.  Actually, not quite -- lprm will override
	 * the login name with "root" if the user is running as root;
	 * the daemon actually checks for the string "root" in its
	 * permission checking.  Sigh.
	 */
	userid = getuid();
	if (Uflag) {
		if (userid != 0 && userid != pp->daemon_user)
			errx(1, "only privileged users may use the `-U' flag");
		lpr_username = Uflag;		/* -U person doing 'lpr' */
	} else {
		lpr_username = getlogin();	/* person doing 'lpr' */
		if (userid != pp->daemon_user || lpr_username == 0) {
			if ((pw = getpwuid(userid)) == NULL)
				errx(1, "Who are you?");
			lpr_username = pw->pw_name;
		}
	}

	/*
	 * Check for restricted group access.
	 */
	if (pp->restrict_grp != NULL && userid != pp->daemon_user) {
		if ((gptr = getgrnam(pp->restrict_grp)) == NULL)
			errx(1, "Restricted group specified incorrectly");
		if (gptr->gr_gid != getgid()) {
			while (*gptr->gr_mem != NULL) {
				if ((strcmp(lpr_username, *gptr->gr_mem)) == 0)
					break;
				gptr->gr_mem++;
			}
			if (*gptr->gr_mem == NULL)
				errx(1, "Not a member of the restricted group");
		}
	}
	/*
	 * Check to make sure queuing is enabled if userid is not root.
	 */
	lock_file_name(pp, buf, sizeof buf);
	if (userid && stat(buf, &stb) == 0 && (stb.st_mode & LFM_QUEUE_DIS))
		errx(1, "Printer queue is disabled");
	/*
	 * Initialize the control file.
	 */
	mktemps(pp);
	tfd = nfile(tfname);
	PRIV_START
	(void) fchown(tfd, pp->daemon_user, -1);
	/* owned by daemon for protection */
	PRIV_END
	card('H', local_host);
	card('P', lpr_username);
	card('C', class);
	if (hdr && !pp->no_header) {
		if (jobname == NULL) {
			if (argc == 0)
				jobname = "stdin";
			else
				jobname = ((arg = strrchr(argv[0], '/'))
					   ? arg + 1 : argv[0]);
		}
		card('J', jobname);
		card('L', lpr_username);
	}
	if (format != 'p' && Zflag != 0)
		card('Z', Zflag);
	if (iflag)
		card('I', itoa(indent));
	if (mailflg)
		card('M', lpr_username);
	if (format == 't' || format == 'n' || format == 'd')
		for (i = 0; i < 4; i++)
			if (fonts[i] != NULL)
				card('1'+i, fonts[i]);
	if (width != NULL)
		card('W', width);
	/*
	 * XXX
	 * Our use of `Z' here is incompatible with LPRng's
	 * use.  We assume that the only use of our existing
	 * `Z' card is as shown for `p' format (pr) files.
	 */
	if (format == 'p') {
		char *s;

		if (locale)
			card('Z', locale);
		else if ((s = setlocale(LC_TIME, "")) != NULL)
			card('Z', s);
	}

	/*
	 * Read the files and spool them.
	 */
	if (argc == 0)
		copy(pp, 0, " ");
	else while (argc--) {
		if (argv[0][0] == '-' && argv[0][1] == '\0') {
			/* use stdin */
			copy(pp, 0, " ");
			argv++;
			continue;
		}
		if ((f = test(arg = *argv++)) < 0)
			continue;	/* file unreasonable */

		if (sflag && (cp = linked(arg)) != NULL) {
			(void)snprintf(buf, sizeof(buf), "%ju %ju",
			    (uintmax_t)statb.st_dev, (uintmax_t)statb.st_ino);
			card('S', buf);
			if (format == 'p')
				card('T', title ? title : arg);
			for (i = 0; i < ncopies; i++)
				card(format, &dfname[inchar-2]);
			card('U', &dfname[inchar-2]);
			if (f)
				card('U', cp);
			card('N', arg);
			dfname[inchar]++;
			nact++;
			continue;
		}
		if (sflag)
			printf("%s: %s: not linked, copying instead\n",
			    progname, arg);

		if (f) {
			/*
			 * The user wants the file removed after it is copied
			 * to the spool area, so see if the file can be moved
			 * instead of copy/unlink'ed.  This is much faster and
			 * uses less spool space than copying the file.  This
			 * can be very significant when running services like
			 * samba, pcnfs, CAP, et al.
			 */
			PRIV_START
			didlink = 0;
			/*
			 * There are several things to check to avoid any
			 * security issues.  Some of these are redundant
			 * under BSD's, but are necessary when lpr is built
			 * under some other OS's (which I do do...)
			 */
			if (lstat(arg, &statb1) < 0)
				goto nohardlink;
			if (S_ISLNK(statb1.st_mode))
				goto nohardlink;
			if (link(arg, dfname) != 0)
				goto nohardlink;
			didlink = 1;
			/*
			 * Make sure the user hasn't tried to trick us via
			 * any race conditions
			 */
			if (lstat(dfname, &statb2) < 0)
				goto nohardlink;
			if (statb1.st_dev != statb2.st_dev)
				goto nohardlink;
			if (statb1.st_ino != statb2.st_ino)
				goto nohardlink;
			/*
			 * Skip if the file already had multiple hard links,
			 * because changing the owner and access-bits would
			 * change ALL versions of the file
			 */
			if (statb2.st_nlink > 2)
				goto nohardlink;
			/*
			 * If we can access and remove the original file
			 * without special setuid-ness then this method is
			 * safe.  Otherwise, abandon the move and fall back
			 * to the (usual) copy method.
			 */
			PRIV_END
			ret = access(dfname, R_OK);
			if (ret == 0)
				ret = unlink(arg);
			PRIV_START
			if (ret != 0)
				goto nohardlink;
			/*
			 * Unlink of user file was successful.  Change the
			 * owner and permissions, add entries to the control
			 * file, and skip the file copying step.
			 */
			chown(dfname, pp->daemon_user, getegid());
			chmod(dfname, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
			PRIV_END
			if (format == 'p')
				card('T', title ? title : arg);
			for (i = 0; i < ncopies; i++)
				card(format, &dfname[inchar-2]);
			card('U', &dfname[inchar-2]);
			card('N', arg);
			nact++;
			continue;
		nohardlink:
			if (didlink)
				unlink(dfname);
			PRIV_END           /* restore old uid */
		} /* end: if (f) */

		if ((i = open(arg, O_RDONLY)) < 0) {
			printf("%s: cannot open %s\n", progname, arg);
		} else {
			copy(pp, i, arg);
			(void) close(i);
			if (f && unlink(arg) < 0)
				printf("%s: %s: not removed\n", progname, arg);
		}
	}

	if (nact) {
		(void) close(tfd);
		tfname[inchar]--;
		/*
		 * Touch the control file to fix position in the queue.
		 */
		PRIV_START
		if ((tfd = open(tfname, O_RDWR)) >= 0) {
			char touch_c;

			if (read(tfd, &touch_c, 1) == 1 &&
			    lseek(tfd, (off_t)0, 0) == 0 &&
			    write(tfd, &touch_c, 1) != 1) {
				printf("%s: cannot touch %s\n", progname,
				    tfname);
				tfname[inchar]++;
				cleanup(0);
			}
			(void) close(tfd);
		}
		if (link(tfname, cfname) < 0) {
			printf("%s: cannot rename %s\n", progname, cfname);
			tfname[inchar]++;
			cleanup(0);
		}
		unlink(tfname);
		PRIV_END
		if (qflag)		/* just q things up */
			exit(0);
		if (!startdaemon(pp))
			printf("jobs queued, but cannot start daemon.\n");
		exit(0);
	}
	cleanup(0);
	return (1);
	/* NOTREACHED */
}