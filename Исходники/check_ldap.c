int
main (int argc, char *argv[])
{

	LDAP *ld;
	LDAPMessage *result;

	/* should be 	int result = STATE_UNKNOWN; */

	int status = STATE_UNKNOWN;
	long microsec;
	double elapsed_time;

	/* for ldap tls */

	int tls;
	int version=3;

	/* for entry counting */

	LDAPMessage *next_entry;
	int status_entries = STATE_OK;
	int num_entries = 0;

	setlocale (LC_ALL, "");
	bindtextdomain (PACKAGE, LOCALEDIR);
	textdomain (PACKAGE);

	if (strstr(argv[0],"check_ldaps")) {
		xasprintf (&progname, "check_ldaps");
 	}

	/* Parse extra opts if any */
	argv=np_extra_opts (&argc, argv, progname);

	if (process_arguments (argc, argv) == ERROR)
		usage4 (_("Could not parse arguments"));

	if (strstr(argv[0],"check_ldaps") && ! starttls && ! ssl_on_connect)
		starttls = TRUE;

	/* initialize alarm signal handling */
	signal (SIGALRM, socket_timeout_alarm_handler);

	/* set socket timeout */
	alarm (timeout_interval);

	/* get the start time */
	gettimeofday (&tv, NULL);

	/* initialize ldap */
	if (ld_uri != NULL)
	{
#ifdef HAVE_LDAP_INITIALIZE
		int result = ldap_initialize(&ld, ld_uri);
		if (result != LDAP_SUCCESS)
		{
			printf ("Failed to connect to LDAP server at %s: %s\n",
				ld_uri, ldap_err2string(result));
			return STATE_CRITICAL;
		}
#else
		printf ("Sorry, this version of %s was compiled without URI support!\n",
			argv[0]);
		return STATE_CRITICAL;
#endif
	}
#ifdef HAVE_LDAP_INIT
	else if (!(ld = ldap_init (ld_host, ld_port))) {
		printf ("Could not connect to the server at port %i\n", ld_port);
		return STATE_CRITICAL;
	}
#else
	else if (!(ld = ldap_open (ld_host, ld_port))) {
		if (verbose)
			ldap_perror(ld, "ldap_open");
		printf (_("Could not connect to the server at port %i\n"), ld_port);
		return STATE_CRITICAL;
	}
#endif /* HAVE_LDAP_INIT */

#ifdef HAVE_LDAP_SET_OPTION
	/* set ldap options */
	if (ldap_set_option (ld, LDAP_OPT_PROTOCOL_VERSION, &ld_protocol) !=
			LDAP_OPT_SUCCESS ) {
		printf(_("Could not set protocol version %d\n"), ld_protocol);
		return STATE_CRITICAL;
	}
#endif

	if (ld_port == LDAPS_PORT || ssl_on_connect) {
		xasprintf (&SERVICE, "LDAPS");
#if defined(HAVE_LDAP_SET_OPTION) && defined(LDAP_OPT_X_TLS)
		/* ldaps: set option tls */
		tls = LDAP_OPT_X_TLS_HARD;

		if (ldap_set_option (ld, LDAP_OPT_X_TLS, &tls) != LDAP_SUCCESS)
		{
			if (verbose)
				ldap_perror(ld, "ldaps_option");
			printf (_("Could not init TLS at port %i!\n"), ld_port);
			return STATE_CRITICAL;
		}
#else
		printf (_("TLS not supported by the libraries!\n"));
		return STATE_CRITICAL;
#endif /* LDAP_OPT_X_TLS */
	} else if (starttls) {
		xasprintf (&SERVICE, "LDAP-TLS");
#if defined(HAVE_LDAP_SET_OPTION) && defined(HAVE_LDAP_START_TLS_S)
		/* ldap with startTLS: set option version */
		if (ldap_get_option(ld,LDAP_OPT_PROTOCOL_VERSION, &version) == LDAP_OPT_SUCCESS )
		{
			if (version < LDAP_VERSION3)
			{
				version = LDAP_VERSION3;
				ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);
			}
		}
		/* call start_tls */
		if (ldap_start_tls_s(ld, NULL, NULL) != LDAP_SUCCESS)
		{
			if (verbose)
				ldap_perror(ld, "ldap_start_tls");
			printf (_("Could not init startTLS at port %i!\n"), ld_port);
			return STATE_CRITICAL;
		}
#else
		printf (_("startTLS not supported by the library, needs LDAPv3!\n"));
		return STATE_CRITICAL;
#endif /* HAVE_LDAP_START_TLS_S */
	}

	/* bind to the ldap server */
	if (ldap_bind_s (ld, ld_binddn, ld_passwd, LDAP_AUTH_SIMPLE) !=
			LDAP_SUCCESS) {
		if (verbose)
			ldap_perror(ld, "ldap_bind");
		printf (_("Could not bind to the LDAP server\n"));
		return STATE_CRITICAL;
	}

	/* do a search of all objectclasses in the base dn */
	if (ldap_search_s (ld, ld_base, (crit_entries!=NULL || warn_entries!=NULL) ? LDAP_SCOPE_SUBTREE : LDAP_SCOPE_BASE, ld_attr, NULL, 0, &result)
			!= LDAP_SUCCESS) {
		if (verbose)
			ldap_perror(ld, "ldap_search");
		printf (_("Could not search/find objectclasses in %s\n"), ld_base);
		return STATE_CRITICAL;
	} else if (crit_entries!=NULL || warn_entries!=NULL) {
		num_entries = ldap_count_entries(ld, result);
	}

	/* unbind from the ldap server */
	ldap_unbind (ld);

	/* reset the alarm handler */
	alarm (0);

	/* calcutate the elapsed time and compare to thresholds */

	microsec = deltime (tv);
	elapsed_time = (double)microsec / 1.0e6;

	if (crit_time!=UNDEFINED && elapsed_time>crit_time)
		status = STATE_CRITICAL;
	else if (warn_time!=UNDEFINED && elapsed_time>warn_time)
		status = STATE_WARNING;
	else
		status = STATE_OK;

	if(entries_thresholds != NULL) {
		if (verbose) {
			printf ("entries found: %d\n", num_entries);
			print_thresholds("entry threasholds", entries_thresholds);
		}
		status_entries = get_status(num_entries, entries_thresholds);
		if (status_entries == STATE_CRITICAL) {
			status = STATE_CRITICAL;
		} else if (status != STATE_CRITICAL) {
			status = status_entries;
		}
	}

	/* print out the result */
	if (crit_entries!=NULL || warn_entries!=NULL) {
		printf (_("LDAP %s - found %d entries in %.3f seconds|%s %s\n"),
			state_text (status),
			num_entries,
			elapsed_time,
			fperfdata ("time", elapsed_time, "s",
				(int)warn_time, warn_time,
				(int)crit_time, crit_time,
				TRUE, 0, FALSE, 0),
			sperfdata ("entries", (double)num_entries, "",
				warn_entries,
				crit_entries,
				TRUE, 0.0, FALSE, 0.0));
	} else {
		printf (_("LDAP %s - %.3f seconds response time|%s\n"),
			state_text (status),
			elapsed_time,
			fperfdata ("time", elapsed_time, "s",
				(int)warn_time, warn_time,
				(int)crit_time, crit_time,
				TRUE, 0, FALSE, 0));
	}

	return status;
}