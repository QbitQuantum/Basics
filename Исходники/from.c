int
main(int argc, char *argv[])
{
	struct passwd *pwd;
	int ch, newline;
	char *file, *sender, *p;
#if MAXPATHLEN > BUFSIZ
	char buf[MAXPATHLEN];
#else
	char buf[BUFSIZ];
#endif

	file = sender = NULL;
	while ((ch = getopt(argc, argv, "f:s:")) != -1)
		switch((char)ch) {
		case 'f':
			file = optarg;
			break;
		case 's':
			sender = optarg;
			for (p = sender; *p; ++p)
				if (isupper(*p))
					*p = tolower(*p);
			break;
		case '?':
		default:
			fprintf(stderr,
			    "usage: from [-f file] [-s sender] [user]\n");
			exit(1);
		}
	argv += optind;

	/*
	 * We find the mailbox by:
	 *	1 -f flag
	 *	2 user
	 *	2 MAIL environment variable
	 *	3 _PATH_MAILDIR/file
	 */
	if (!file) {
		if (!(file = *argv)) {
			if (!(file = getenv("MAIL"))) {
				if (!(pwd = getpwuid(getuid())))
					errx(1, "no password file entry for you");
				if ((file = getenv("USER"))) {
					(void)snprintf(buf, sizeof(buf),
					    "%s/%s", _PATH_MAILDIR, file);
					file = buf;
				} else
					(void)snprintf(file = buf, sizeof(buf),
					    "%s/%s", _PATH_MAILDIR,
					    pwd->pw_name);
			}
		} else {
			(void)snprintf(buf, sizeof(buf), "%s/%s",
			    _PATH_MAILDIR, file);
			file = buf;
		}
	}
	if (!freopen(file, "r", stdin))
		err(1, "%s", file);
	for (newline = 1; fgets(buf, sizeof(buf), stdin);) {
		if (*buf == '\n') {
			newline = 1;
			continue;
		}
		if (newline && !strncmp(buf, "From ", 5) &&
		    (!sender || match(buf + 5, sender)))
			printf("%s", buf);
		newline = 0;
	}
	exit(0);
}