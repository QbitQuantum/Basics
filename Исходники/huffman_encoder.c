int main(int argc, char **argv)
{
	char command = 'n';
	char help_flag = 0;
	char non_option_flag = 0;
	unsigned int length = 1;
	char *input_file_name = NULL;
	char *output_file_name = NULL;
	int i, c;

	opterr = 0;

	while ((c = getopt (argc, argv, "edhl:i:o:")) != -1) {
		switch (c) {
		case 'e':
			command = 'e';
			break;
		case 'd':
			command = 'd';
			break;
		case 'h':
			help_flag = 1;
			break;
		case 'l':
			length = *optarg - 48;
			printf("Length = %i\n",length);
			break;
		case 'i':
			input_file_name = optarg;
			break;
		case 'o':
			output_file_name = optarg;
			break;
		case '?':
			if (optopt == 'c')
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
			return 1;
		default:
			abort();
		}
	}

	for (i = optind; i < argc; i++) {
		if (!non_option_flag)
			non_option_flag = 1;
		printf("Non-option argument: %s\n", argv[i]);
	}

	if (non_option_flag)
		return 1;

	else if (help_flag || (argc == 1))
		show_help(argv[0]);

	else if (command != 'n') {

		if (!input_file_name)
			printf("You need to specify an input file\n");

		else if (!output_file_name)
			printf("You need to specify an output file\n");

		else if (length < 1)
			printf("You need to specify a positive length\n");

		else
			process_command(command, input_file_name, output_file_name, length);

	}
	return 0;
}