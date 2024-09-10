/* process command-line arguments */
static int
process_arguments (int argc, char **argv)
{
	int c;
	int escape = 0;
	char *temp;

	int option = 0;
	static struct option longopts[] = {
		{"hostname", required_argument, 0, 'H'},
		{"critical", required_argument, 0, 'c'},
		{"warning", required_argument, 0, 'w'},
		{"critical-codes", required_argument, 0, 'C'},
		{"warning-codes", required_argument, 0, 'W'},
		{"timeout", required_argument, 0, 't'},
		{"protocol", required_argument, 0, 'P'}, /* FIXME: Unhandled */
		{"port", required_argument, 0, 'p'},
		{"escape", no_argument, 0, 'E'},
		{"all", no_argument, 0, 'A'},
		{"send", required_argument, 0, 's'},
		{"expect", required_argument, 0, 'e'},
		{"maxbytes", required_argument, 0, 'm'},
		{"quit", required_argument, 0, 'q'},
		{"jail", no_argument, 0, 'j'},
		{"delay", required_argument, 0, 'd'},
		{"refuse", required_argument, 0, 'r'},
		{"mismatch", required_argument, 0, 'M'},
		{"use-ipv4", no_argument, 0, '4'},
		{"use-ipv6", no_argument, 0, '6'},
		{"verbose", no_argument, 0, 'v'},
		{"version", no_argument, 0, 'V'},
		{"help", no_argument, 0, 'h'},
		{"ssl", no_argument, 0, 'S'},
		{"certificate", required_argument, 0, 'D'},
		{0, 0, 0, 0}
	};

	if (argc < 2)
		usage4 (_("No arguments found"));

	/* backwards compatibility */
	for (c = 1; c < argc; c++) {
		if (strcmp ("-to", argv[c]) == 0)
			strcpy (argv[c], "-t");
		else if (strcmp ("-wt", argv[c]) == 0)
			strcpy (argv[c], "-w");
		else if (strcmp ("-ct", argv[c]) == 0)
			strcpy (argv[c], "-c");
	}

	if (!is_option (argv[1])) {
		server_address = argv[1];
		argv[1] = argv[0];
		argv = &argv[1];
		argc--;
	}

	while (1) {
		c = getopt_long (argc, argv, "+hVv46EAH:s:e:q:m:c:w:t:p:C:W:d:Sr:jD:M:",
		                 longopts, &option);

		if (c == -1 || c == EOF || c == 1)
			break;

		switch (c) {
		case '?':                 /* print short usage statement if args not parsable */
			usage5 ();
		case 'h':                 /* help */
			print_help ();
			exit (STATE_OK);
		case 'V':                 /* version */
			print_revision (progname, NP_VERSION);
			exit (STATE_OK);
		case 'v':                 /* verbose mode */
			flags |= FLAG_VERBOSE;
			break;
		case '4':
			address_family = AF_INET;
			break;
		case '6':
#ifdef USE_IPV6
			address_family = AF_INET6;
#else
			usage4 (_("IPv6 support not available"));
#endif
			break;
		case 'H':                 /* hostname */
			server_address = optarg;
			break;
		case 'c':                 /* critical */
			critical_time = strtod (optarg, NULL);
			flags |= FLAG_TIME_CRIT;
			break;
		case 'j':		  /* hide output */
			flags |= FLAG_HIDE_OUTPUT;
			break;
		case 'w':                 /* warning */
			warning_time = strtod (optarg, NULL);
			flags |= FLAG_TIME_WARN;
			break;
		case 'C':
			crit_codes = realloc (crit_codes, ++crit_codes_count);
			crit_codes[crit_codes_count - 1] = optarg;
			break;
		case 'W':
			warn_codes = realloc (warn_codes, ++warn_codes_count);
			warn_codes[warn_codes_count - 1] = optarg;
			break;
		case 't':                 /* timeout */
			if (!is_intpos (optarg))
				usage4 (_("Timeout interval must be a positive integer"));
			else
				socket_timeout = atoi (optarg);
			break;
		case 'p':                 /* port */
			if (!is_intpos (optarg))
				usage4 (_("Port must be a positive integer"));
			else
				server_port = atoi (optarg);
			break;
		case 'E':
			escape = 1;
			break;
		case 's':
			if (escape)
				server_send = np_escaped_string(optarg);
			else
				xasprintf(&server_send, "%s", optarg);
			break;
		case 'e': /* expect string (may be repeated) */
			flags &= ~FLAG_EXACT_MATCH;
			if (server_expect_count == 0)
				server_expect = malloc (sizeof (char *) * (++server_expect_count));
			else
				server_expect = realloc (server_expect, sizeof (char *) * (++server_expect_count));
			server_expect[server_expect_count - 1] = optarg;
			break;
		case 'm':
			if (!is_intpos (optarg))
				usage4 (_("Maxbytes must be a positive integer"));
			else
				maxbytes = strtol (optarg, NULL, 0);
			break;
		case 'q':
			if (escape)
				server_quit = np_escaped_string(optarg);
			else
				xasprintf(&server_quit, "%s\r\n", optarg);
			break;
		case 'r':
			if (!strncmp(optarg,"ok",2))
				econn_refuse_state = STATE_OK;
			else if (!strncmp(optarg,"warn",4))
				econn_refuse_state = STATE_WARNING;
			else if (!strncmp(optarg,"crit",4))
				econn_refuse_state = STATE_CRITICAL;
			else
				usage4 (_("Refuse must be one of ok, warn, crit"));
			break;
		case 'M':
			if (!strncmp(optarg,"ok",2))
				expect_mismatch_state = STATE_OK;
			else if (!strncmp(optarg,"warn",4))
				expect_mismatch_state = STATE_WARNING;
			else if (!strncmp(optarg,"crit",4))
				expect_mismatch_state = STATE_CRITICAL;
			else
				usage4 (_("Mismatch must be one of ok, warn, crit"));
			break;
		case 'd':
			if (is_intpos (optarg))
				delay = atoi (optarg);
			else
				usage4 (_("Delay must be a positive integer"));
			break;
		case 'D': /* Check SSL cert validity - days 'til certificate expiration */
#ifdef HAVE_SSL
#  ifdef USE_OPENSSL /* XXX */
			if ((temp=strchr(optarg,','))!=NULL) {
			    *temp='\0';
			    if (!is_intnonneg (optarg))
                               usage2 (_("Invalid certificate expiration period"), optarg);				 days_till_exp_warn = atoi(optarg);
			    *temp=',';
			    temp++;
			    if (!is_intnonneg (temp))
				usage2 (_("Invalid certificate expiration period"), temp);
			    days_till_exp_crit = atoi (temp);
			}
			else {
			    days_till_exp_crit=0;
			    if (!is_intnonneg (optarg))
				usage2 (_("Invalid certificate expiration period"), optarg);
			    days_till_exp_warn = atoi (optarg);
			}
			check_cert = TRUE;
			flags |= FLAG_SSL;
			break;
#  endif /* USE_OPENSSL */
#endif
			/* fallthrough if we don't have ssl */
		case 'S':
#ifdef HAVE_SSL
			flags |= FLAG_SSL;
#else
			die (STATE_UNKNOWN, _("Invalid option - SSL is not available"));
#endif
			break;
		case 'A':
			flags |= FLAG_MATCH_ALL;
			break;
		}
	}

	if (server_address == NULL)
		usage4 (_("You must provide a server address"));
	else if (server_address[0] != '/' && is_host (server_address) == FALSE)
		die (STATE_CRITICAL, "%s %s - %s: %s\n", SERVICE, state_text(STATE_CRITICAL), _("Invalid hostname, address or socket"), server_address);

	return TRUE;
}