int
main(int argc, char *argv[])
{
	char	   *pghost = NULL;
	char	   *pgport = NULL;
	char	   *pguser = NULL;
	bool		force_password = false;
	bool		data_only = false;
	bool		globals_only = false;
	bool		schema_only = false;
	PGconn	   *conn;
	int			c,
				ret;

	static struct option long_options[] = {
		{"data-only", no_argument, NULL, 'a'},
		{"clean", no_argument, NULL, 'c'},
		{"inserts", no_argument, NULL, 'd'},
		{"attribute-inserts", no_argument, NULL, 'D'},
		{"column-inserts", no_argument, NULL, 'D'},
		{"globals-only", no_argument, NULL, 'g'},
		{"host", required_argument, NULL, 'h'},
		{"ignore-version", no_argument, NULL, 'i'},
		{"oids", no_argument, NULL, 'o'},
		{"no-owner", no_argument, NULL, 'O'},
		{"port", required_argument, NULL, 'p'},
		{"password", no_argument, NULL, 'W'},
		{"schema-only", no_argument, NULL, 's'},
		{"superuser", required_argument, NULL, 'S'},
		{"username", required_argument, NULL, 'U'},
		{"verbose", no_argument, NULL, 'v'},
		{"no-privileges", no_argument, NULL, 'x'},
		{"no-acl", no_argument, NULL, 'x'},

		/*
		 * the following options don't have an equivalent short option letter,
		 * but are available as '-X long-name'
		 */
		{"disable-dollar-quoting", no_argument, &disable_dollar_quoting, 1},
		{"disable-triggers", no_argument, &disable_triggers, 1},
		{"use-set-session-authorization", no_argument, &use_setsessauth, 1},

		{NULL, 0, NULL, 0}
	};

	int			optindex;

	set_pglocale_pgservice(argv[0], "pg_dump");

	progname = get_progname(argv[0]);

	if (argc > 1)
	{
		if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-?") == 0)
		{
			help();
			exit(0);
		}
		if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-V") == 0)
		{
			puts("pg_dumpall (PostgreSQL) " PG_VERSION);
			exit(0);
		}
	}

	if ((ret = find_other_exec(argv[0], "pg_dump", PG_VERSIONSTR,
							   pg_dump_bin)) < 0)
	{
		char		full_path[MAXPGPATH];

		if (find_my_exec(argv[0], full_path) < 0)
			StrNCpy(full_path, progname, MAXPGPATH);

		if (ret == -1)
			fprintf(stderr,
					_("The program \"pg_dump\" is needed by %s "
					  "but was not found in the\n"
					  "same directory as \"%s\".\n"
					  "Check your installation.\n"),
					progname, full_path);
		else
			fprintf(stderr,
					_("The program \"pg_dump\" was found by \"%s\"\n"
					  "but was not the same version as %s.\n"
					  "Check your installation.\n"),
					full_path, progname);
		exit(1);
	}

	pgdumpopts = createPQExpBuffer();

	while ((c = getopt_long(argc, argv, "acdDgh:ioOp:sS:U:vWxX:", long_options, &optindex)) != -1)
	{
		switch (c)
		{
			case 'a':
				data_only = true;
				appendPQExpBuffer(pgdumpopts, " -a");
				break;

			case 'c':
				output_clean = true;
				break;

			case 'd':
			case 'D':
				appendPQExpBuffer(pgdumpopts, " -%c", c);
				break;

			case 'g':
				globals_only = true;
				break;

			case 'h':
				pghost = optarg;
#ifndef WIN32
				appendPQExpBuffer(pgdumpopts, " -h '%s'", pghost);
#else
				appendPQExpBuffer(pgdumpopts, " -h \"%s\"", pghost);
#endif

				break;

			case 'i':
				ignoreVersion = true;
				appendPQExpBuffer(pgdumpopts, " -i");
				break;

			case 'o':
				appendPQExpBuffer(pgdumpopts, " -o");
				break;

			case 'O':
				appendPQExpBuffer(pgdumpopts, " -O");
				break;

			case 'p':
				pgport = optarg;
#ifndef WIN32
				appendPQExpBuffer(pgdumpopts, " -p '%s'", pgport);
#else
				appendPQExpBuffer(pgdumpopts, " -p \"%s\"", pgport);
#endif
				break;

			case 's':
				schema_only = true;
				appendPQExpBuffer(pgdumpopts, " -s");
				break;

			case 'S':
#ifndef WIN32
				appendPQExpBuffer(pgdumpopts, " -S '%s'", optarg);
#else
				appendPQExpBuffer(pgdumpopts, " -S \"%s\"", optarg);
#endif
				break;

			case 'U':
				pguser = optarg;
#ifndef WIN32
				appendPQExpBuffer(pgdumpopts, " -U '%s'", pguser);
#else
				appendPQExpBuffer(pgdumpopts, " -U \"%s\"", pguser);
#endif
				break;

			case 'v':
				verbose = true;
				appendPQExpBuffer(pgdumpopts, " -v");
				break;

			case 'W':
				force_password = true;
				appendPQExpBuffer(pgdumpopts, " -W");
				break;

			case 'x':
				skip_acls = true;
				appendPQExpBuffer(pgdumpopts, " -x");
				break;

			case 'X':
				if (strcmp(optarg, "disable-dollar-quoting") == 0)
					appendPQExpBuffer(pgdumpopts, " -X disable-dollar-quoting");
				else if (strcmp(optarg, "disable-triggers") == 0)
					appendPQExpBuffer(pgdumpopts, " -X disable-triggers");
				else if (strcmp(optarg, "use-set-session-authorization") == 0)
					 /* no-op, still allowed for compatibility */ ;
				else
				{
					fprintf(stderr,
							_("%s: invalid -X option -- %s\n"),
							progname, optarg);
					fprintf(stderr, _("Try \"%s --help\" for more information.\n"), progname);
					exit(1);
				}
				break;

			case 0:
				break;

			default:
				fprintf(stderr, _("Try \"%s --help\" for more information.\n"), progname);
				exit(1);
		}
	}

	/* Add long options to the pg_dump argument list */
	if (disable_dollar_quoting)
		appendPQExpBuffer(pgdumpopts, " -X disable-dollar-quoting");
	if (disable_triggers)
		appendPQExpBuffer(pgdumpopts, " -X disable-triggers");
	if (use_setsessauth)
		appendPQExpBuffer(pgdumpopts, " -X use-set-session-authorization");

	if (optind < argc)
	{
		fprintf(stderr, _("%s: too many command-line arguments (first is \"%s\")\n"),
				progname, argv[optind]);
		fprintf(stderr, _("Try \"%s --help\" for more information.\n"),
				progname);
		exit(1);
	}

	/*
	 * First try to connect to database "postgres", and failing that
	 * "template1".  "postgres" is the preferred choice for 8.1 and later
	 * servers, but it usually will not exist on older ones.
	 */
	conn = connectDatabase("postgres", pghost, pgport, pguser,
						   force_password, false);
	if (!conn)
		conn = connectDatabase("template1", pghost, pgport, pguser,
							   force_password, true);

	printf("--\n-- PostgreSQL database cluster dump\n--\n\n");
	if (verbose)
		dumpTimestamp("Started on");

	printf("\\connect postgres\n\n");

	if (!data_only)
	{
		/* Dump roles (users) */
		dumpRoles(conn);

		/* Dump role memberships --- need different method for pre-8.1 */
		if (server_version >= 80100)
			dumpRoleMembership(conn);
		else
			dumpGroups(conn);

		/* Dump tablespaces */
		if (server_version >= 80000)
			dumpTablespaces(conn);

		/* Dump CREATE DATABASE commands */
		if (!globals_only)
			dumpCreateDB(conn);
	}

	if (!globals_only)
		dumpDatabases(conn);

	PQfinish(conn);

	if (verbose)
		dumpTimestamp("Completed on");
	printf("--\n-- PostgreSQL database cluster dump complete\n--\n\n");

	exit(0);
}