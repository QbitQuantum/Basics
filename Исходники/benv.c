int
main(int argc, char **argv)
{
	int c;
	int updates = 0;
	char *usage = "Usage: %s [-v] [-f prom-device]"
	    " [variable[=value] ...]";
	eplist_t *elist;
	benv_des_t *bd;
	char *file = NULL;

	setpname(argv[0]);

	while ((c = getopt(argc, argv, "f:Itv")) != -1)
		switch (c) {
		case 'v':
			verbose++;
			break;
		case 'f':
			file = optarg;
			break;
		case 't':
			test++;
			break;
		default:
			exit(_error(NO_PERROR, usage, argv[0]));
		}

	(void) uname(&uts_buf);
	bd = new_bd();
	init_benv(bd, file);

	map_benv(bd);
	if (bd->len) {
		parse_benv(bd);
		unmap_benv(bd);
	}

	elist = bd->elist;

	if (optind >= argc) {
		print_vars(elist);
		return (0);
	} else
		while (optind < argc) {
			/*
			 * If "-" specified, read variables from stdin;
			 * otherwise, process each argument as a variable
			 * print or set request.
			 */
			if (strcmp(argv[optind], "-") == 0) {
				char *line;

				while ((line = get_line()) != NULL)
					updates += proc_var(line, elist);
				clearerr(stdin);
			} else
				updates += proc_var(argv[optind], elist);

			optind++;
		}

	/*
	 * don't write benv if we are processing delayed writes since
	 * it is likely that the delayed writes changes bootenv.rc anyway...
	 */
	if (updates)
		write_benv(bd);
	close_kbenv();

	return (0);
}