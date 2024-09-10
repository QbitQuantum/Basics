int
main(int argc, char **argv)
{
	struct wipe_desc *wp0 = NULL, *wp;
	int c, all = 0, force = 0, has_offset = 0, noact = 0, quiet = 0;
	int mode = WP_MODE_PRETTY;

	static const struct option longopts[] = {
	    { "all",       0, 0, 'a' },
	    { "force",     0, 0, 'f' },
	    { "help",      0, 0, 'h' },
	    { "no-act",    0, 0, 'n' },
	    { "offset",    1, 0, 'o' },
	    { "parsable",  0, 0, 'p' },
	    { "quiet",     0, 0, 'q' },
	    { "types",     1, 0, 't' },
	    { "version",   0, 0, 'V' },
	    { NULL,        0, 0, 0 }
	};

	static const ul_excl_t excl[] = {       /* rows and cols in in ASCII order */
		{ 'a','o' },
		{ 0 }
	};
	int excl_st[ARRAY_SIZE(excl)] = UL_EXCL_STATUS_INIT;

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);
	atexit(close_stdout);

	while ((c = getopt_long(argc, argv, "ahno:pqt:V", longopts, NULL)) != -1) {

		err_exclusive_options(c, longopts, excl, excl_st);

		switch(c) {
		case 'a':
			all++;
			break;
		case 'f':
			force++;
			break;
		case 'h':
			usage(stdout);
			break;
		case 'n':
			noact++;
			break;
		case 'o':
			wp0 = add_offset(wp0, strtosize_or_err(optarg,
					 _("invalid offset argument")), 1);
			has_offset++;
			break;
		case 'p':
			mode = WP_MODE_PARSABLE;
			break;
		case 'q':
			quiet++;
			break;
		case 't':
			type_pattern = optarg;
			break;
		case 'V':
			printf(UTIL_LINUX_VERSION);
			return EXIT_SUCCESS;
		default:
			usage(stderr);
			break;
		}
	}

	if (optind == argc)
		usage(stderr);

	if (!all && !has_offset) {
		/*
		 * Print only
		 */
		while (optind < argc) {
			wp0 = read_offsets(NULL, argv[optind++]);
			if (wp0)
				print_all(wp0, mode);
			free_wipe(wp0);
		}
	} else {
		/*
		 * Erase
		 */
		while (optind < argc) {
			wp = clone_offset(wp0);
			wp = do_wipe(wp, argv[optind++], noact, all, quiet,
				     force);
			free_wipe(wp);
		}
	}

	return EXIT_SUCCESS;
}