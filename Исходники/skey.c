int
main(int argc, char *argv[])
{
	int     n, i, cnt = 1, pass = 0, hexmode = 0;
	char    passwd[SKEY_MAX_PW_LEN+1], key[SKEY_BINKEY_SIZE];
	char	buf[33], *seed, *slash;

	/* If we were called as otp-METHOD, set algorithm based on that */
	if ((slash = strrchr(argv[0], '/')))
		slash++;
	else
		slash = argv[0];
	if (strncmp(slash, "otp-", 4) == 0) {
		slash += 4;
		if (skey_set_algorithm(slash) == NULL)
			errx(1, "Unknown hash algorithm %s", slash);
	}

	for (i = 1; i < argc && argv[i][0] == '-' && strcmp(argv[i], "--");) {
		if (argv[i][2] == '\0') {
			/* Single character switch */
			switch (argv[i][1]) {
			case 'n':
				if (++i == argc)
					usage(argv[0]);
				cnt = atoi(argv[i]);
				break;
			case 'p':
				if (++i == argc)
					usage(argv[0]);
				if (strlcpy(passwd, argv[i], sizeof(passwd)) >=
				    sizeof(passwd))
					errx(1, "Password too long");
				pass = 1;
				break;
			case 'x':
				hexmode = 1;
				break;
			default:
				usage(argv[0]);
			}
		} else {
			/* Multi character switches are hash types */
			if (skey_set_algorithm(&argv[i][1]) == NULL) {
				warnx("Unknown hash algorithm %s", &argv[i][1]);
				usage(argv[0]);
			}
		}
		i++;
	}

	if (argc > i + 2)
		usage(argv[0]);

	/* Could be in the form <number>/<seed> */
	if (argc <= i + 1) {
		/* look for / in it */
		if (argc <= i)
			usage(argv[0]);
		slash = strchr(argv[i], '/');
		if (slash == NULL)
			usage(argv[0]);
		*slash++ = '\0';
		seed = slash;

		if ((n = atoi(argv[i])) < 0) {
			warnx("%d not positive", n);
			usage(argv[0]);
		} else if (n > SKEY_MAX_SEQ) {
			warnx("%d is larger than max (%d)", n, SKEY_MAX_SEQ);
			usage(argv[0]);
		}
	} else {
		if ((n = atoi(argv[i])) < 0) {
			warnx("%d not positive", n);
			usage(argv[0]);
		} else if (n > SKEY_MAX_SEQ) {
			warnx("%d is larger than max (%d)", n, SKEY_MAX_SEQ);
			usage(argv[0]);
		}
		seed = argv[++i];
	}

	/* Get user's secret passphrase */
	if (!pass) {
		fputs("Reminder - Do not use this program while"
		    " logged in via telnet.\n", stderr);
		(void)fputs("Enter secret passphrase: ", stderr);
		readpass(passwd, sizeof(passwd));
		if (passwd[0] == '\0')
			exit(1);
	}

	/* Crunch seed and passphrase into starting key */
	if (keycrunch(key, seed, passwd) != 0)
		errx(1, "key crunch failed");

	if (cnt == 1) {
		while (n-- != 0)
			f(key);
		(void)puts(hexmode ? put8(buf, key) : btoe(buf, key));
	} else {
		for (i = 0; i <= n - cnt; i++)
			f(key);
		for (; i <= n; i++) {
			if (hexmode)
				(void)printf("%d: %s\n", i, put8(buf, key));
			else
				(void)printf("%d: %-29s\n", i, btoe(buf, key));
			f(key);
		}
	}
	exit(0);
}