int
main(int argc, char *argv[])
{
	const char *filename;
	wchar_t *p, *t;
	FILE *fp;
	size_t len;
	int ch, rval;

	setlocale(LC_ALL, "");
	setprogname(argv[0]);

	while ((ch = getopt(argc, argv, "")) != -1)
		switch(ch) {
		case '?':
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	fp = stdin;
	filename = "stdin";
	rval = 0;
	do {
		if (*argv) {
			if ((fp = fopen(*argv, "r")) == NULL) {
				warn("%s", *argv);
				rval = 1;
				++argv;
				continue;
			}
			filename = *argv++;
		}
		while ((p = fgetwln(fp, &len)) != NULL) {
			if (p[len - 1] == L'\n')
				--len;
			t = p + len - 1;
			for (t = p + len - 1; t >= p; --t)
				putwchar(*t);
			putwchar(L'\n');
		}
		if (ferror(fp)) {
			warn("%s", filename);
			rval = 1;
		}
		(void)fclose(fp);
	} while(*argv);
	exit(rval);
}