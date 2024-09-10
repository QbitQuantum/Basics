int
main(int argc, char *argv[])
{
	u_int flags;
	int ch;
	struct utsname uts;

	flags = 0;
	while ((ch = getopt(argc, argv, "amnrsv")) != EOF) {
		switch(ch) {
		case 'a':
			flags |= (MFLAG | NFLAG | RFLAG | SFLAG | VFLAG);
			break;
		case 'm':
			flags |= MFLAG;
			break;
		case 'n':
			flags |= NFLAG;
			break;
		case 'r':
			flags |= RFLAG;
			break;
		case 's':
			flags |= SFLAG;
			break;
		case 'v':
			flags |= VFLAG;
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc)
		usage();

	if (!flags)
		flags |= SFLAG;

	uname(&uts);

	if (flags & SFLAG)
		printf("%s ", uts.sysname);

	if (flags & RFLAG)
		printf("%s ", uts.release);

	if (flags & VFLAG)
		printf("%s ", uts.version);

	if (flags & MFLAG)
		printf("%s ", uts.machine);

	if (flags & NFLAG)
		printf("%s", uts.nodename);

	putchar('\n');
	exit(0);
}