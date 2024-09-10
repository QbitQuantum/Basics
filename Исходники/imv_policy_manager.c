int main(int argc, char *argv[])
{
	database_t *db;
	char *uri;
	int session_id;
	bool start, success;

	/* enable attest debugging hook */
	dbg = stderr_dbg;

	atexit(library_deinit);

	/* initialize library */
	if (!library_init(NULL, "imv_policy_manager"))
	{
		exit(SS_RC_LIBSTRONGSWAN_INTEGRITY);
	}
	if (!lib->plugins->load(lib->plugins,
			lib->settings->get_str(lib->settings, "imv_policy_manager.load",
				 "sqlite")))
	{
		exit(SS_RC_INITIALIZATION_FAILED);
	}

	if (argc < 3)
	{
		usage();
		exit(SS_RC_INITIALIZATION_FAILED);
	}
	if (streq(argv[1], "start"))
	{
		start = TRUE;
	}
	else if (streq(argv[1], "stop"))
	{
		start = FALSE;
	}
	else
	{
		usage();
		exit(SS_RC_INITIALIZATION_FAILED);
	}

	session_id = atoi(argv[2]);

	/* attach IMV database */
	uri = lib->settings->get_str(lib->settings,
			"imv_policy_manager.database",
			lib->settings->get_str(lib->settings,
				"charon.imcv.database",
				lib->settings->get_str(lib->settings,
					"libimcv.database", NULL)));
	if (!uri)
	{
		fprintf(stderr, "database uri not defined.\n");
		exit(SS_RC_INITIALIZATION_FAILED);
	}

	db = lib->db->create(lib->db, uri);
	if (!db)
	{
		fprintf(stderr, "opening database failed.\n");
		exit(SS_RC_INITIALIZATION_FAILED);
	}

	if (start)
	{
		success = policy_start(db, session_id);
	}
	else
	{
		success = policy_stop(db, session_id);
	}
	db->destroy(db);

	fprintf(stderr, "imv_policy_manager %s %s\n", start ? "start" : "stop",
			success ? "successful" : "failed");

	exit(EXIT_SUCCESS);
}