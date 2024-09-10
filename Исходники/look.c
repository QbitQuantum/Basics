int
main(int argc, char *argv[])
{
	struct stat sb;
	int ch, fd, match;
	wchar_t termchar;
	unsigned char *back, *front;
	unsigned const char *file;
	wchar_t *key;

	(void) setlocale(LC_CTYPE, "");

	file = _path_words;
	termchar = L'\0';
	while ((ch = getopt(argc, argv, "dft:")) != -1)
		switch(ch) {
		case 'd':
			dflag = 1;
			break;
		case 'f':
			fflag = 1;
			break;
		case 't':
			if (mbrtowc(&termchar, optarg, MB_LEN_MAX, NULL) !=
			    strlen(optarg))
				errx(2, "invalid termination character");
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc == 0)
		usage();
	if (argc == 1) 			/* But set -df by default. */
		dflag = fflag = 1;
	key = prepkey(*argv++, termchar);
	if (argc >= 2)
		file = *argv++;

	match = 1;

	do {
		if ((fd = open(file, O_RDONLY, 0)) < 0 || fstat(fd, &sb))
			err(2, "%s", file);
		if ((uintmax_t)sb.st_size > (uintmax_t)SIZE_T_MAX)
			errx(2, "%s: %s", file, strerror(EFBIG));
		if (sb.st_size == 0) {
			close(fd);
			continue;
		}
		if ((front = mmap(NULL, (size_t)sb.st_size, PROT_READ, MAP_SHARED, fd, (off_t)0)) == MAP_FAILED)
			err(2, "%s", file);
		back = front + sb.st_size;
		match *= (look(key, front, back));
		close(fd);
	} while (argc-- > 2 && (file = *argv++));

	exit(match);
}