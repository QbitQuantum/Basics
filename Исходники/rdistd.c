/*
 * The Beginning
 */
int
main(int argc, char **argv, char **envp)
{
	extern char *__progname;
	char *cp;
	int c;

	progname = __progname;

	if (init(argc, argv, envp) < 0)
		exit(1);

	while ((c = getopt(argc, argv, "SDV")) != -1)
		switch (c) {
		case 'S':
			isserver++;
			break;

		case 'D':
			debug++;
			break;

		case 'V':
			printf("%s\n", getversion());
			exit(0);

		case '?':
		default:
			error("Bad command line option.");
			usage();
		}

	if (!isserver) {
		error("Use the -S option to run this program in server mode.");
		exit(1);
	}

	/* Use stdin and stdout for remote descriptors */
	rem_r = fileno(stdin);
	rem_w = fileno(stdout);

	/* Set logging */
	if ((cp = msgparseopts(localmsglist, TRUE)) != NULL)
		fatalerr("Bad message logging option (%s): %s", 
			 localmsglist, cp);

	/*
	 * Main processing function
	 */
	server();

	exit(nerrs != 0);
}