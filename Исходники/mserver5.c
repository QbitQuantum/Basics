int
main(int argc, char **av)
{
	char *prog = *av;
	opt *set = NULL;
	int i, grpdebug = 0, debug = 0, setlen = 0, listing = 0;
	str err = MAL_SUCCEED;
	char prmodpath[FILENAME_MAX];
	const char *modpath = NULL;
	char *binpath = NULL;
	str *monet_script;
	char *dbpath = NULL;
	char *dbextra = NULL;
	int verbosity = 0;
	static struct option long_options[] = {
		{ "config", required_argument, NULL, 'c' },
		{ "dbpath", required_argument, NULL, 0 },
		{ "dbextra", required_argument, NULL, 0 },
		{ "daemon", required_argument, NULL, 0 },
		{ "debug", optional_argument, NULL, 'd' },
		{ "help", no_argument, NULL, '?' },
		{ "version", no_argument, NULL, 0 },
		{ "verbose", optional_argument, NULL, 'v' },
		{ "readonly", no_argument, NULL, 'r' },
		{ "single-user", no_argument, NULL, 0 },
		{ "set", required_argument, NULL, 's' },
		{ "threads", no_argument, NULL, 0 },
		{ "memory", no_argument, NULL, 0 },
		{ "properties", no_argument, NULL, 0 },
		{ "io", no_argument, NULL, 0 },
		{ "transactions", no_argument, NULL, 0 },
		{ "trace", optional_argument, NULL, 't' },
		{ "modules", no_argument, NULL, 0 },
		{ "algorithms", no_argument, NULL, 0 },
		{ "optimizers", no_argument, NULL, 0 },
		{ "performance", no_argument, NULL, 0 },
		{ "forcemito", no_argument, NULL, 0 },
		{ "heaps", no_argument, NULL, 0 },
		{ NULL, 0, NULL, 0 }
	};

#if defined(_MSC_VER) && defined(__cplusplus)
	set_terminate(mserver_abort);
#endif
#ifdef _MSC_VER
	_CrtSetReportMode(_CRT_ERROR, 0);
	_CrtSetReportMode(_CRT_ASSERT, 0);
	_set_invalid_parameter_handler(mserver_invalid_parameter_handler);
#ifdef _TWO_DIGIT_EXPONENT
	_set_output_format(_TWO_DIGIT_EXPONENT);
#endif
#endif
	if (setlocale(LC_CTYPE, "") == NULL) {
		fprintf(stderr, "cannot set locale\n");
		exit(1);
	}

	if (getcwd(monet_cwd, FILENAME_MAX - 1) == NULL) {
		perror("pwd");
		fprintf(stderr,"monet_init: could not determine current directory\n");
		exit(-1);
	}

	/* retrieve binpath early (before monet_init) because some
	 * implementations require the working directory when the binary was
	 * called */
	binpath = get_bin_path();

	if (!(setlen = mo_builtin_settings(&set)))
		usage(prog, -1);

	for (;;) {
		int option_index = 0;

		int c = getopt_long(argc, av, "c:d::rs:t::v::?",
				long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {
		case 0:
			if (strcmp(long_options[option_index].name, "dbpath") == 0) {
				size_t optarglen = strlen(optarg);
				/* remove trailing directory separator */
				while (optarglen > 0 &&
				       (optarg[optarglen - 1] == '/' ||
					optarg[optarglen - 1] == '\\'))
					optarg[--optarglen] = '\0';
				dbpath = absolute_path(optarg);
				if( dbpath == NULL)
					fprintf(stderr, "#error: can not allocate memory for dbpath\n");
				else
					setlen = mo_add_option(&set, setlen, opt_cmdline, "gdk_dbpath", dbpath);
				break;
			}
			if (strcmp(long_options[option_index].name, "dbextra") == 0) {
				if (dbextra)
					fprintf(stderr, "#warning: ignoring multiple --dbextra arguments\n");
				else
					dbextra = optarg;
				break;
			}
#ifdef HAVE_CONSOLE
			if (strcmp(long_options[option_index].name, "daemon") == 0) {
				setlen = mo_add_option(&set, setlen, opt_cmdline, "monet_daemon", optarg);
				break;
			}
#endif
			if (strcmp(long_options[option_index].name, "single-user") == 0) {
				setlen = mo_add_option(&set, setlen, opt_cmdline, "gdk_single_user", "yes");
				break;
			}
			if (strcmp(long_options[option_index].name, "version") == 0) {
				monet_version();
				exit(0);
			}
			/* debugging options */
			if (strcmp(long_options[option_index].name, "properties") == 0) {
				grpdebug |= GRPproperties;
				break;
			}
			if (strcmp(long_options[option_index].name, "algorithms") == 0) {
				grpdebug |= GRPalgorithms;
				break;
			}
			if (strcmp(long_options[option_index].name, "optimizers") == 0) {
				grpdebug |= GRPoptimizers;
				break;
			}
			if (strcmp(long_options[option_index].name, "forcemito") == 0) {
				grpdebug |= GRPforcemito;
				break;
			}
			if (strcmp(long_options[option_index].name, "performance") == 0) {
				grpdebug |= GRPperformance;
				break;
			}
			if (strcmp(long_options[option_index].name, "io") == 0) {
				grpdebug |= GRPio;
				break;
			}
			if (strcmp(long_options[option_index].name, "memory") == 0) {
				grpdebug |= GRPmemory;
				break;
			}
			if (strcmp(long_options[option_index].name, "modules") == 0) {
				grpdebug |= GRPmodules;
				break;
			}
			if (strcmp(long_options[option_index].name, "transactions") == 0) {
				grpdebug |= GRPtransactions;
				break;
			}
			if (strcmp(long_options[option_index].name, "threads") == 0) {
				grpdebug |= GRPthreads;
				break;
			}
			if (strcmp(long_options[option_index].name, "trace") == 0) {
				mal_trace = 1;
				break;
			}
			if (strcmp(long_options[option_index].name, "heaps") == 0) {
				grpdebug |= GRPheaps;
				break;
			}
			usage(prog, -1);
			/* not reached */
		case 'c':
			/* coverity[var_deref_model] */
			setlen = mo_add_option(&set, setlen, opt_cmdline, "config", optarg);
			break;
		case 'd':
			if (optarg) {
				char *endarg;
				debug |= strtol(optarg, &endarg, 10);
				if (*endarg != '\0') {
					fprintf(stderr, "ERROR: wrong format for --debug=%s\n",
							optarg);
					usage(prog, -1);
				}
			} else {
				debug |= 1;
			}
			break;
		case 'r':
			setlen = mo_add_option(&set, setlen, opt_cmdline, "gdk_readonly", "yes");
			break;
		case 's': {
			/* should add option to a list */
			/* coverity[var_deref_model] */
			char *tmp = strchr(optarg, '=');

			if (tmp) {
				*tmp = '\0';
				setlen = mo_add_option(&set, setlen, opt_cmdline, optarg, tmp + 1);
			} else
				fprintf(stderr, "ERROR: wrong format %s\n", optarg);
			}
			break;
		case 't':
			mal_trace = 1;
			break;
		case 'v':
			if (optarg) {
				char *endarg;
				verbosity = (int) strtol(optarg, &endarg, 10);
				if (*endarg != '\0') {
					fprintf(stderr, "ERROR: wrong format for --verbose=%s\n",
							optarg);
					usage(prog, -1);
				}
			} else {
				verbosity++;
			}
			break;
		case '?':
			/* a bit of a hack: look at the option that the
			   current `c' is based on and see if we recognize
			   it: if -? or --help, exit with 0, else with -1 */
			usage(prog, strcmp(av[optind - 1], "-?") == 0 || strcmp(av[optind - 1], "--help") == 0 ? 0 : -1);
		default:
			fprintf(stderr, "ERROR: getopt returned character "
				"code '%c' 0%o\n", c, (uint8_t) c);
			usage(prog, -1);
		}
	}

	if (!(setlen = mo_system_config(&set, setlen)))
		usage(prog, -1);

	GDKsetdebug(debug | grpdebug);  /* add the algorithm tracers */
	if (debug)
		mo_print_options(set, setlen);
	GDKsetverbose(verbosity);

	monet_script = (str *) malloc(sizeof(str) * (argc + 1));
	if (monet_script == NULL) {
		fprintf(stderr, "!ERROR: cannot allocate memory for script \n");
		exit(1);
	}
	i = 0;
	while (optind < argc) {
		monet_script[i] = absolute_path(av[optind]);
		if (monet_script[i] == NULL) {
			fprintf(stderr, "!ERROR: cannot allocate memory for script \n");
			exit(1);
		}
		i++;
		optind++;
	}
	monet_script[i] = NULL;
	if (!dbpath) {
		dbpath = absolute_path(mo_find_option(set, setlen, "gdk_dbpath"));
		if (!dbpath) {
			fprintf(stderr, "!ERROR: cannot allocate memory for database directory \n");
			exit(1);
		}
	}
	if (BBPaddfarm(dbpath, 1 << PERSISTENT) != GDK_SUCCEED ||
	    BBPaddfarm(dbextra ? dbextra : dbpath, 1 << TRANSIENT) != GDK_SUCCEED) {
		fprintf(stderr, "!ERROR: cannot add farm\n");
		exit(1);
	}
	if (GDKcreatedir(dbpath) != GDK_SUCCEED) {
		fprintf(stderr, "!ERROR: cannot create directory for %s\n", dbpath);
		exit(1);
	}
	GDKfree(dbpath);
	if (monet_init(set, setlen) == 0) {
		mo_free_options(set, setlen);
		if (GDKerrbuf && *GDKerrbuf)
			fprintf(stderr, "%s\n", GDKerrbuf);
		exit(1);
	}
	mo_free_options(set, setlen);

	if (GDKsetenv("monet_version", GDKversion()) != GDK_SUCCEED ||
	    GDKsetenv("monet_release",
#ifdef MONETDB_RELEASE
		      MONETDB_RELEASE
#else
		      "unreleased"
#endif
		    ) != GDK_SUCCEED) {
		fprintf(stderr, "!ERROR: GDKsetenv failed\n");
		exit(1);
	}

	if ((modpath = GDKgetenv("monet_mod_path")) == NULL) {
		/* start probing based on some heuristics given the binary
		 * location:
		 * bin/mserver5 -> ../
		 * libX/monetdb5/lib/
		 * probe libX = lib, lib32, lib64, lib/64 */
		size_t pref;
		/* "remove" common prefix of configured BIN and LIB
		 * directories from LIBDIR */
		for (pref = 0; LIBDIR[pref] != 0 && BINDIR[pref] == LIBDIR[pref]; pref++)
			;
		const char *libdirs[] = {
			&LIBDIR[pref],
			"lib",
			"lib64",
			"lib/64",
			"lib32",
			NULL,
		};
		struct stat sb;
		if (binpath != NULL) {
			char *p = strrchr(binpath, DIR_SEP);
			if (p != NULL)
				*p = '\0';
			p = strrchr(binpath, DIR_SEP);
			if (p != NULL) {
				*p = '\0';
				for (i = 0; libdirs[i] != NULL; i++) {
					int len = snprintf(prmodpath, sizeof(prmodpath), "%s%c%s%cmonetdb5",
									   binpath, DIR_SEP, libdirs[i], DIR_SEP);
					if (len == -1 || len >= FILENAME_MAX)
						continue;
					if (stat(prmodpath, &sb) == 0) {
						modpath = prmodpath;
						break;
					}
				}
			} else {
				printf("#warning: unusable binary location, "
					   "please use --set monet_mod_path=/path/to/... to "
					   "allow finding modules\n");
				fflush(NULL);
			}
		} else {
			printf("#warning: unable to determine binary location, "
				   "please use --set monet_mod_path=/path/to/... to "
				   "allow finding modules\n");
			fflush(NULL);
		}
		if (modpath != NULL &&
		    GDKsetenv("monet_mod_path", modpath) != GDK_SUCCEED) {
			fprintf(stderr, "!ERROR: GDKsetenv failed\n");
			exit(1);
		}
	}

	/* configure sabaoth to use the right dbpath and active database */
	msab_dbpathinit(GDKgetenv("gdk_dbpath"));
	/* wipe out all cruft, if left over */
	if ((err = msab_wildRetreat()) != NULL) {
		/* just swallow the error */
		free(err);
	}
	/* From this point, the server should exit cleanly.  Discussion:
	 * even earlier?  Sabaoth here registers the server is starting up. */
	if ((err = msab_registerStarting()) != NULL) {
		/* throw the error at the user, but don't die */
		fprintf(stderr, "!%s\n", err);
		free(err);
	}

#ifdef HAVE_SIGACTION
	{
		struct sigaction sa;

		(void) sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sa.sa_handler = handler;
		if (sigaction(SIGINT, &sa, NULL) == -1 ||
		    sigaction(SIGQUIT, &sa, NULL) == -1 ||
		    sigaction(SIGTERM, &sa, NULL) == -1) {
			fprintf(stderr, "!unable to create signal handlers\n");
		}
	}
#else
#ifdef _MSC_VER
	if (!SetConsoleCtrlHandler(winhandler, TRUE))
		fprintf(stderr, "!unable to create console control handler\n");
#else
	if(signal(SIGINT, handler) == SIG_ERR)
		fprintf(stderr, "!unable to create signal handlers\n");
#ifdef SIGQUIT
	if(signal(SIGQUIT, handler) == SIG_ERR)
		fprintf(stderr, "!unable to create signal handlers\n");
#endif
	if(signal(SIGTERM, handler) == SIG_ERR)
		fprintf(stderr, "!unable to create signal handlers\n");
#endif
#endif

	{
		str lang = "mal";
		/* we inited mal before, so publish its existence */
		if ((err = msab_marchScenario(lang)) != NULL) {
			/* throw the error at the user, but don't die */
			fprintf(stderr, "!%s\n", err);
			free(err);
		}
	}

	{
		/* unlock the vault, first see if we can find the file which
		 * holds the secret */
		char secret[1024];
		char *secretp = secret;
		FILE *secretf;
		size_t len;

		if (GDKgetenv("monet_vault_key") == NULL) {
			/* use a default (hard coded, non safe) key */
			snprintf(secret, sizeof(secret), "%s", "Xas632jsi2whjds8");
		} else {
			if ((secretf = fopen(GDKgetenv("monet_vault_key"), "r")) == NULL) {
				fprintf(stderr,
					"unable to open vault_key_file %s: %s\n",
					GDKgetenv("monet_vault_key"), strerror(errno));
				/* don't show this as a crash */
				msab_registerStop();
				exit(1);
			}
			len = fread(secret, 1, sizeof(secret), secretf);
			secret[len] = '\0';
			len = strlen(secret); /* secret can contain null-bytes */
			if (len == 0) {
				fprintf(stderr, "vault key has zero-length!\n");
				/* don't show this as a crash */
				msab_registerStop();
				exit(1);
			} else if (len < 5) {
				fprintf(stderr, "#warning: your vault key is too short "
								"(%zu), enlarge your vault key!\n", len);
			}
			fclose(secretf);
		}
		if ((err = AUTHunlockVault(secretp)) != MAL_SUCCEED) {
			/* don't show this as a crash */
			msab_registerStop();
			fprintf(stderr, "%s\n", err);
			freeException(err);
			exit(1);
		}
	}
	/* make sure the authorisation BATs are loaded */
	if ((err = AUTHinitTables(NULL)) != MAL_SUCCEED) {
		/* don't show this as a crash */
		msab_registerStop();
		fprintf(stderr, "%s\n", err);
		freeException(err);
		exit(1);
	}
	if (mal_init()) {
		/* don't show this as a crash */
		msab_registerStop();
		return 0;
	}

	if((err = MSinitClientPrg(mal_clients, "user", "main")) != MAL_SUCCEED) {
		msab_registerStop();
		fprintf(stderr, "%s\n", err);
		freeException(err);
		exit(1);
	}

	emergencyBreakpoint();
	for (i = 0; monet_script[i]; i++) {
		str msg = evalFile(monet_script[i], listing);
		/* check for internal exception message to terminate */
		if (msg) {
			if (strcmp(msg, "MALException:client.quit:Server stopped.") == 0)
				mal_exit(0);
			fprintf(stderr, "#%s: %s\n", monet_script[i], msg);
			freeException(msg);
		}
		GDKfree(monet_script[i]);
		monet_script[i] = 0;
	}
	free(monet_script);

	if ((err = msab_registerStarted()) != NULL) {
		/* throw the error at the user, but don't die */
		fprintf(stderr, "!%s\n", err);
		free(err);
	}

#ifdef HAVE_CONSOLE
	if (!monet_daemon) {
		MSserveClient(mal_clients);
	} else
#endif
	while (!interrupted && !GDKexiting()) {
		MT_sleep_ms(100);
	}

	/* mal_exit calls exit, so statements after this call will
	 * never get reached */
	mal_exit(0);

	return 0;
}