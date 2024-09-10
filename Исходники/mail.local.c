int
main(int argc, char *argv[])
{
	struct passwd *pw;
	int ch, fd, eval, lockfile=1, holdme=0;
	uid_t uid;
	char *from;

	openlog("mail.local", LOG_PERROR, LOG_MAIL);

	from = NULL;
	while ((ch = getopt(argc, argv, "lLdf:r:H")) != -1)
		switch (ch) {
		case 'd':		/* backward compatible */
			break;
		case 'f':
		case 'r':		/* backward compatible */
			if (from)
				merr(FATAL, "multiple -f options");
			from = optarg;
			break;
		case 'l':
			lockfile=1;
			break;
		case 'L':
			lockfile=0;
			break;
		case 'H':
			holdme=1;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	/* Support -H flag for backwards compat */
	if (holdme) {
		execl(_PATH_LOCKSPOOL, "lockspool", (char *)NULL);
		merr(FATAL, "execl: lockspool: %s", strerror(errno));
	} else {
		if (!*argv)
			usage();
		if (geteuid() != 0)
			merr(FATAL, "may only be run by the superuser");
	}

	/*
	 * If from not specified, use the name from getlogin() if the
	 * uid matches, otherwise, use the name from the password file
	 * corresponding to the uid.
	 */
	uid = getuid();
	if (!from && (!(from = getlogin()) ||
	    !(pw = getpwnam(from)) || pw->pw_uid != uid))
		from = (pw = getpwuid(uid)) ? pw->pw_name : "???";

	fd = storemail(from);
	for (eval = 0; *argv; ++argv)
		eval |= deliver(fd, *argv, lockfile);
	exit(eval);
}