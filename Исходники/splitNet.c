/* process command line arguments */
static void parse_args(int argc, char **argv) {
	extern char *optarg;
	extern int optopt;
	int c;

	while((c = getopt(argc, argv, ":hi:o:")) != -1) {
		switch(c) {
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		case 'i':
			opt.in_file = Strdup((const char *) optarg);
			break;
		case 'o':
			opt.out_dir = Strdup((const char *) optarg);
			opt.out_dir_len = (int) strlen(opt.out_dir);
			break;
		case ':':
			fprintf(stderr, "%s: Missing argument for -%c.\n", prog, (char) optopt);
			usage(EXIT_FAILURE);
			break;
		case '?':
			fprintf(stderr, "%s: Unrecognized option -%c.\n", prog, (char) optopt);
			usage(EXIT_FAILURE);
		}
	}

	if (opt.out_dir == NULL) {
		fprintf(stderr, "%s: -o argument required\n", prog);
		usage(EXIT_FAILURE);
	}
}