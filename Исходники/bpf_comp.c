void
parse_args(int argc, char *argv[])
{
	char c;
	char *progname = argv[0];
	int i;
	size_t len;

	while((c = getopt(argc, argv, "hl:s:o:")) != -1)
	{
		switch(c)
		{
		case 'h':
			usage(stdout, progname);
			exit(EX_OK);
			break;
		case 'l':
			if ((dlt = strtol(optarg, NULL, 0)) == 0 && errno != 0)
			{
				fprintf(stderr, "Failed to parse %s: %s\n", optarg, strerror(errno));
				exit(EX_USAGE);
			}
			break;
		case 's':
			if ((dlt = strtol(optarg, NULL, 0)) == 0 && errno != 0)
			{
				fprintf(stderr, "Failed to parse %s: %s\n", optarg, strerror(errno));
				exit(EX_USAGE);
			}
			break;
		case 'o':
			switch(optarg[0])
			{
			case 'r':
				format = RAW;
				break;
			case 'h':
				format = HEXSTRING;
				break;
			case 'n':
				format = NG_BPF;
				break;
			default:
				fprintf(stderr, "Unknown format: %c\n", optarg[0]);
				usage(stderr, progname);
				exit(EX_USAGE);
				break;
			}
			break;
		default:
			usage(stderr, progname);
			exit(EX_USAGE);
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (argc == 0)
	{
		fprintf(stderr, "Expression expected\n");
		usage(stderr, progname);
		exit(EX_USAGE);
	}

	len = argc;
	for(i = 0; i < argc; i++)
		len += strlen(argv[i]);

	expr = malloc(len);
	if (expr == NULL)
		exit(EX_SOFTWARE);
	expr[0] = '\0';
	strcat(expr, argv[0]);
	for(i = 1; i < argc; i++)
	{
		strcat(expr, " ");
		strcat(expr, argv[i]);
	}
}