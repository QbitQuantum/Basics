int main(int argc, char * argv[])
{
	FILE            *input_fh = stdin;
	Dictionary      dict;
	const char     *language = NULL;
	int             num_linkages;
	Label           label = NO_LABEL;
	Command_Options *copts;
	Parse_Options   opts;
	bool batch_in_progress = false;

	isatty_stdin = isatty(fileno(stdin));
	isatty_stdout = isatty(fileno(stdout));

#ifdef _WIN32
	/* If compiled with MSVC/MinGW, we still support running under Cygwin.
	 * This is done by checking running_under_cygwin to resolve
	 * incompatibilities. */
	const char *ostype = getenv("OSTYPE");
	if ((NULL != ostype) && (0 == strcmp(ostype, "cygwin")))
		running_under_cygwin = true;

	/* argv encoding is in the current locale. */
	argv = argv2utf8(argc);
	if (NULL == argv)
	{
		prt_error("Fatal error: Unable to parse command line\n");
		exit(-1);
	}

#ifdef _MSC_VER
	_set_printf_count_output(1); /* enable %n support for display_1line_help()*/
#endif /* _MSC_VER */

	win32_set_utf8_output();
#endif /* _WIN32 */

#if LATER
	/* Try to catch the SIGWINCH ... except this is not working. */
	struct sigaction winch_act;
	winch_act.sa_handler = winch_handler;
	winch_act.sa_sigaction = NULL;
	sigemptyset (&winch_act.sa_mask);
	winch_act.sa_flags = 0;
	sigaction (SIGWINCH, &winch_act, NULL);
#endif

	copts = command_options_create();
	if (copts == NULL || copts->panic_opts == NULL)
	{
		prt_error("Fatal error: unable to create parse options\n");
		exit(-1);
	}
	opts = copts->popts;

	setup_panic_parse_options(copts->panic_opts);
	copts->panic_mode = true;

	parse_options_set_max_parse_time(opts, 30);
	parse_options_set_linkage_limit(opts, 1000);
	parse_options_set_min_null_count(opts, 0);
	parse_options_set_max_null_count(opts, 0);
	parse_options_set_short_length(opts, 16);
	parse_options_set_islands_ok(opts, false);
	parse_options_set_display_morphology(opts, false);

	save_default_opts(copts); /* Options so far are the defaults */

	if ((argc > 1) && (argv[1][0] != '-')) {
		/* The dictionary is the first argument if it doesn't begin with "-" */
		language = argv[1];
	}

	for (int i = 1; i < argc; i++)
	{
		if (strcmp("--help", argv[i]) == 0)
		{
			print_usage(stdout, argv[0], copts, 0);
		}

		if (strcmp("--version", argv[i]) == 0)
		{
			printf("Version: %s\n", linkgrammar_get_version());
			printf("%s\n", linkgrammar_get_configuration());
			exit(0);
		}
	}

	/* Process command line variable-setting commands (only). */
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			const char *var = argv[i] + ((argv[i][1] != '-') ? 1 : 2);
			if ((var[0] != '!') && (0 > issue_special_command(var, copts, NULL)))
				print_usage(stderr, argv[0], copts, -1);
		}
		else if (i != 1)
		{
			prt_error("Fatal error: Unknown argument '%s'.\n", argv[i]);
			print_usage(stderr, argv[0], copts, -1);
		}
	}

	if (language && *language)
	{
		dict = dictionary_create_lang(language);
		if (dict == NULL)
		{
			prt_error("Fatal error: Unable to open dictionary.\n");
			exit(-1);
		}
	}
	else
	{
		dict = dictionary_create_default_lang();
		if (dict == NULL)
		{
			prt_error("Fatal error: Unable to open default dictionary.\n");
			exit(-1);
		}
	}

	/* Process the command line '!' commands */
	for (int i = 1; i < argc; i++)
	{
		if ((argv[i][0] == '-') && (argv[i][1] == '!'))
		{
			if (0 > issue_special_command(argv[i]+1, copts, dict))
				print_usage(stderr, argv[0], copts, -1);
		}
	}

	check_winsize(copts);

	prt_error("Info: Dictionary version %s, locale %s\n",
		linkgrammar_get_dict_version(dict),
		linkgrammar_get_dict_locale(dict));
	prt_error("Info: Library version %s. Enter \"!help\" for help.\n",
		linkgrammar_get_version());

	/* Main input loop */
	while (true)
	{
		char *input_string;
		Sentence sent = NULL;

		/* Make sure stderr is shown even when MSVC binary runs under
		 * Cygwin/MSYS pty (in that case it is fully buffered(!)). */
		fflush(stderr);

		verbosity = parse_options_get_verbosity(opts);
		debug = parse_options_get_debug(opts);
		test = parse_options_get_test(opts);

		input_string = fget_input_string(input_fh, stdout, /*check_return*/false);
		check_winsize(copts);

		if (NULL == input_string)
		{
			if (ferror(input_fh))
				prt_error("Error: Read: %s\n", strerror(errno));

			if (input_fh == stdin) break;
			fclose (input_fh);
			input_fh = stdin;
			continue;
		}

		/* Discard whitespace characters from end of string. */
		for (char *p = &input_string[strlen(input_string)-1];
		     (p > input_string) && strchr(WHITESPACE, *p) ; p--)
		{
			*p = '\0';
		}

		/* If the input string is just whitespace, then ignore it. */
		if (strspn(input_string, WHITESPACE) == strlen(input_string))
			continue;

		char command = special_command(input_string, copts, dict);
		if ('e' == command) break;    /* It was an exit command */
		if ('c' == command) continue; /* It was another command */
		if (-1 == command) continue;  /* It was a bad command */

		/* We have to handle the !file command inline; it's too hairy
		 * otherwise ... */
		if ('f' == command)
		{
			char * filename = &input_string[strcspn(input_string, WHITESPACE)] + 1;
			int fnlen = strlen(filename);

			if (0 == fnlen)
			{
				prt_error("Error: Missing file name argument\n");
				continue;
			}

			if ('\n' == filename[fnlen-1]) filename[fnlen-1] = '\0';

			struct stat statbuf;
			if ((0 == stat(filename, &statbuf)) && statbuf.st_mode & S_IFDIR)
			{
				prt_error("Error: Cannot open %s: %s\n",
				        filename, strerror(EISDIR));
				continue;
			}

			input_fh = fopen(filename, "r");

			if (NULL == input_fh)
			{
				prt_error("Error: Cannot open %s: %s\n", filename, strerror(errno));
				input_fh = stdin;
				continue;
			}
			continue;
		}


		if (!copts->batch_mode) batch_in_progress = false;
		if ('\0' != test[0])
		{
			/* In batch mode warn only once.
			 * In auto-next-linkage mode don't warn at all. */
			if (!batch_in_progress && !auto_next_linkage_test(test))
			{
				fflush(stdout);
				/* Remind the developer this is a test mode. */
				prt_error("Warning: Tests enabled: %s\n", test);
				if (copts->batch_mode) batch_in_progress = true;
			}
		}

		if (copts->echo_on)
		{
			printf("%s\n", input_string);
		}

		if (copts->batch_mode || auto_next_linkage_test(test))
		{
			label = strip_off_label(input_string);
		}

		// Post-processing-based pruning will clip away connectors
		// that we might otherwise want to examine. So disable PP
		// pruning in this situation.
		if (copts->display_bad)
			parse_options_set_perform_pp_prune(opts, false);
		else
			parse_options_set_perform_pp_prune(opts, true);

		sent = sentence_create(input_string, dict);

		if (sentence_split(sent, opts) < 0)
		{
			sentence_delete(sent);
			sent = NULL;
			continue;
		}

		if (0 != copts->display_wordgraph)
		{
			const char *wg_display_flags = ""; /* default flags */
			switch (copts->display_wordgraph)
			{
				case 1:     /* default flags */
					break;
				case 2:     /* subgraphs with a legend */
					wg_display_flags = "sl";
					break;
				case 3:
					{
						/* Use esoteric flags from the test user variable. */
						const char *s = test_enabled(test, "wg");
						if ((NULL != s) && (':' == s[0])) wg_display_flags = s;
					}
					break;
				default:
					prt_error("Warning: wordgraph=%d: Unknown value, using 1\n",
								 copts->display_wordgraph);
					copts->display_wordgraph = 1;
			}
			sentence_display_wordgraph(sent, wg_display_flags);
		}

		/* First parse with the default disjunct_cost as set by the library
		 * (currently 2.7). Usually parse here with no null links.
		 * However, if "-test=one-step-parse" is used and we are said to
		 * parse with null links, allow parsing here with null links too. */
		bool one_step_parse = !copts->batch_mode && copts->allow_null &&
		                    test_enabled(test, "one-step-parse");
		int max_null_count = one_step_parse ? sentence_length(sent) : 0;

		parse_options_set_min_null_count(opts, 0);
		parse_options_set_max_null_count(opts, max_null_count);
		parse_options_reset_resources(opts);

		num_linkages = sentence_parse(sent, opts);

		/* num_linkages is negative only on a hard-error;
		 * typically, due to a zero-length sentence.  */
		if (num_linkages < 0)
		{
			sentence_delete(sent);
			sent = NULL;
			continue;
		}

#if 0
		/* Try again, this time omitting the requirement for
		 * definite articles, etc. This should allow for the parsing
		 * of newspaper headlines and other clipped speech.
		 *
		 * XXX Unfortunately, this also allows for the parsing of
		 * all sorts of ungrammatical sentences which should not
		 * parse, and leads to bad parses of many other unparsable
		 * but otherwise grammatical sentences.  Thus, this trick
		 * pretty much fails; we leave it here to document the
		 * experiment.
		 */
		if (num_linkages == 0)
		{
			parse_options_set_disjunct_cost(opts, 4.5);
			num_linkages = sentence_parse(sent, opts);
			if (num_linkages < 0) continue;
		}
#endif /* 0 */

		/* Try using a larger list of disjuncts */
		/* XXX FIXME: the lg_expand_disjunct_list() routine is not
		 * currently a part of the public API; it should be made so,
		 * or this expansion idea should be abandoned... not sure which.
		 */
		if ((num_linkages == 0) && parse_options_get_use_cluster_disjuncts(opts))
		{
			int expanded;
			if (verbosity > 0) fprintf(stdout, "No standard linkages, expanding disjunct set.\n");
			parse_options_set_disjunct_cost(opts, 3.9);
			expanded = lg_expand_disjunct_list(sent);
			if (expanded)
			{
				num_linkages = sentence_parse(sent, opts);
			}
			if (0 < num_linkages) printf("Got One !!!!!!!!!!!!!!!!!\n");
		}

		/* If asked to show bad linkages, then show them. */
		if ((num_linkages == 0) && (!copts->batch_mode))
		{
			if (copts->display_bad)
			{
				num_linkages = sentence_num_linkages_found(sent);
			}
		}

		/* Now parse with null links */
		if (!one_step_parse && num_linkages == 0 && !copts->batch_mode)
		{
			if (verbosity > 0) fprintf(stdout, "No complete linkages found.\n");

			if (copts->allow_null)
			{
				/* XXX should use expanded disjunct list here too */
				parse_options_set_min_null_count(opts, 1);
				parse_options_set_max_null_count(opts, sentence_length(sent));
				num_linkages = sentence_parse(sent, opts);
			}
		}

		if (verbosity > 0)
		{
			if (parse_options_timer_expired(opts))
				fprintf(stdout, "Timer is expired!\n");

			if (parse_options_memory_exhausted(opts))
				fprintf(stdout, "Memory is exhausted!\n");
		}

		if ((num_linkages == 0) &&
			copts->panic_mode &&
			parse_options_resources_exhausted(opts))
		{
			/* print_total_time(opts); */
			batch_errors++;
			if (verbosity > 0) fprintf(stdout, "Entering \"panic\" mode...\n");
			/* If the parser used was the SAT solver, set the panic parser to
			 * it too.
			 * FIXME? Currently, the SAT solver code is not too useful in
			 * panic mode since it doesn't handle parsing with null words, so
			 * using the regular parser in that case could be beneficial.
			 * However, this currently causes a crash due to a memory
			 * management mess. */
			parse_options_set_use_sat_parser(copts->panic_opts,
				parse_options_get_use_sat_parser(opts));
			parse_options_reset_resources(copts->panic_opts);
			parse_options_set_verbosity(copts->panic_opts, verbosity);
			(void)sentence_parse(sent, copts->panic_opts);
			if (verbosity > 0)
			{
				if (parse_options_timer_expired(copts->panic_opts))
					fprintf(stdout, "Panic timer is expired!\n");
			}
		}

		if (verbosity > 1) parse_options_print_total_time(opts);

		const char *rc = "";
		if (copts->batch_mode)
		{
			batch_process_some_linkages(label, sent, copts);
		}
		else
		{
			rc = process_some_linkages(input_fh, sent, copts);
		}

		fflush(stdout);
		sentence_delete(sent);
		sent = NULL;

		if ((NULL == rc) && (input_fh == stdin)) break;
	}

	if (copts->batch_mode)
	{
		/* print_time(opts, "Total"); */
		fprintf(stderr,
				"%d error%s.\n", batch_errors, (batch_errors==1) ? "" : "s");
	}

	/* Free stuff, so that mem-leak detectors don't complain. */
	command_options_delete(copts);
	dictionary_delete(dict);

	printf ("Bye.\n");
	return 0;
}