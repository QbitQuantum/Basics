int
main(int argc, char **argv)
{
	int	ch;

	log_init(1);
	log_verbose(~0);

	while ((ch = getopt(argc, argv, "")) != -1) {
		switch (ch) {
		default:
			log_warnx("warn: table-ldap: bad option");
			return (1);
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 1) {
		log_warnx("warn: table-ldap: bogus argument(s)");
		return (1);
	}

	config = argv[0];

	if (!ldap_config()) {
		log_warnx("warn: table-ldap: could not parse config");
		return (1);
	}

	log_debug("debug: table-ldap: done reading config");

	if (!ldap_open()) {
		log_warnx("warn: table-ldap: failed to connect");
		return (1);
	}

	log_debug("debug: table-ldap: connected");

	table_api_on_update(table_ldap_update);
	table_api_on_check(table_ldap_check);
	table_api_on_lookup(table_ldap_lookup);
	table_api_on_fetch(table_ldap_fetch);
	table_api_dispatch();

	return (0);
}