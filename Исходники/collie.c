int main(int argc, char **argv)
{
	int ch, longindex, ret;
	unsigned long flags;
	struct option *long_options;
	const struct command *commands;
	const char *short_options;
	char *p;
	const struct sd_option *sd_opts;

	init_commands(&commands);

	if (argc < 3)
		usage(commands, 0);

	flags = setup_commands(commands, argv[1], argv[2]);

	optind = 3;

	sd_opts = build_sd_options(command_opts);
	long_options = build_long_options(sd_opts);
	short_options = build_short_options(sd_opts);

	while ((ch = getopt_long(argc, argv, short_options, long_options,
				&longindex)) >= 0) {

		switch (ch) {
		case 'a':
			sdhost = optarg;
			break;
		case 'p':
			sdport = strtol(optarg, &p, 10);
			if (optarg == p || sdport < 1 || sdport > UINT16_MAX) {
				fprintf(stderr, "Invalid port number '%s'\n", optarg);
				exit(EXIT_USAGE);
			}
			break;
		case 'r':
			raw_output = true;
			break;
		case 'h':
			subcommand_usage(argv[1], argv[2], EXIT_SUCCESS);
			break;
		case '?':
			usage(commands, EXIT_USAGE);
			break;
		default:
			if (command_parser)
				command_parser(ch, optarg);
			else
				usage(commands, EXIT_USAGE);
			break;
		}
	}

	if (!isatty(STDOUT_FILENO) || raw_output)
		highlight = false;

	if (flags & SUBCMD_FLAG_NEED_NODELIST) {
		ret = update_node_list(SD_MAX_NODES, 0);
		if (ret < 0) {
			fprintf(stderr, "Failed to get node list\n");
			exit(EXIT_SYSFAIL);
		}
	}

	if (flags & SUBCMD_FLAG_NEED_THIRD_ARG && argc == optind)
		subcommand_usage(argv[1], argv[2], EXIT_USAGE);

	return command_fn(argc, argv);
}