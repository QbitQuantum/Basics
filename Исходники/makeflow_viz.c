int main(int argc, char *argv[])
{
	int c;
	random_init();
	set_makeflow_exe(argv[0]);
	debug_config(get_makeflow_exe());
	int display_mode = 0;

	cctools_version_debug(D_DEBUG, get_makeflow_exe());
	const char *dagfile;

	int condense_display = 0;
	int change_size = 0;
	int export_as_dax = 0;
	int ppm_mode = 0;
	char *ppm_option = NULL;

	struct option long_options_viz[] = {
		{"display-mode", required_argument, 0, 'D'},
		{"help", no_argument, 0, 'h'},
		{"dot-merge-similar", no_argument, 0,  LONG_OPT_DOT_CONDENSE},
		{"dot-proportional",  no_argument, 0,  LONG_OPT_DOT_PROPORTIONAL},
		{"ppm-highlight-row", required_argument, 0, LONG_OPT_PPM_ROW},
		{"ppm-highlight-exe", required_argument, 0, LONG_OPT_PPM_EXE},
		{"ppm-highlight-file", required_argument, 0, LONG_OPT_PPM_FILE},
		{"ppm-show-levels", no_argument, 0, LONG_OPT_PPM_LEVELS},
		{"export-as-dax", no_argument, 0, 'e'},
		{"version", no_argument, 0, 'v'},
		{0, 0, 0, 0}
	};
	const char *option_string_viz = "b:D:ehv";

	while((c = getopt_long(argc, argv, option_string_viz, long_options_viz, NULL)) >= 0) {
		switch (c) {
			case 'D':
				if(strcasecmp(optarg, "dot") == 0)
					display_mode = SHOW_DAG_DOT;
				else if (strcasecmp(optarg, "ppm") == 0)
					display_mode = SHOW_DAG_PPM;
				else
					fatal("Unknown display option: %s\n", optarg);
				break;
			case LONG_OPT_DOT_CONDENSE:
				display_mode = SHOW_DAG_DOT;
				condense_display = 1;
				break;
			case LONG_OPT_DOT_PROPORTIONAL:
				display_mode = SHOW_DAG_DOT;
				change_size = 1;
				break;
			case LONG_OPT_PPM_EXE:
				display_mode = SHOW_DAG_PPM;
				ppm_option = optarg;
				ppm_mode = 2;
				break;
			case LONG_OPT_PPM_FILE:
				display_mode = SHOW_DAG_PPM;
				ppm_option = optarg;
				ppm_mode = 3;
				break;
			case LONG_OPT_PPM_ROW:
				display_mode = SHOW_DAG_PPM;
				ppm_option = optarg;
				ppm_mode = 4;
				break;
			case LONG_OPT_PPM_LEVELS:
				display_mode = SHOW_DAG_PPM;
				ppm_mode = 5;
				break;
			case 'e':
				export_as_dax = 1;
				break;
			case 'h':
				show_help_viz(get_makeflow_exe());
				return 0;
			case 'v':
				cctools_version_print(stdout, get_makeflow_exe());
				return 0;
			default:
				show_help_viz(get_makeflow_exe());
				return 1;
		}
	}

	if((argc - optind) != 1) {
		int rv = access("./Makeflow", R_OK);
		if(rv < 0) {
			fprintf(stderr, "makeflow: No makeflow specified and file \"./Makeflow\" could not be found.\n");
			fprintf(stderr, "makeflow: Run \"%s -h\" for help with options.\n", get_makeflow_exe());
			return 1;
		}

		dagfile = "./Makeflow";
	} else {
		dagfile = argv[optind];
	}

	struct dag *d = dag_from_file(dagfile);
	if(!d) {
		fatal("makeflow: couldn't load %s: %s\n", dagfile, strerror(errno));
	}

	if(export_as_dax) {
		dag_to_dax(d, path_basename(dagfile));
		return 0;
	}

	if(display_mode)
	{
		switch(display_mode)
		{
			case SHOW_DAG_DOT:
				dag_to_dot(d, condense_display, change_size);
				break;

			case SHOW_DAG_PPM:
				dag_to_ppm(d, ppm_mode, ppm_option);
				break;

			default:
				fatal("Unknown display option.");
				break;
		}
		exit(0);
	}

	return 0;
}