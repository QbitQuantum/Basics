static int child_init(int rank)
{
	int i = 0, ld_count = 0;
	char* ld_name;

	/* don't do anything for non-worker process */
	if (rank==PROC_MAIN || rank==PROC_TCP_MAIN) {
		return 0;
	}

	/*
	* build ld_sessions and connect all sessions
	*/
	ld_count = iniparser_getnsec(config_vals);
	for (i = 0; i < ld_count; i++)
	{
		ld_name = iniparser_getsecname(config_vals, i);
		if (add_ld_session(ld_name,
					NULL,
					config_vals)
				!= 0)
		{
			LM_ERR("[%s]: add_ld_session failed\n", ld_name);
			return -1;
		}

		if (ldap_connect(ld_name) != 0)
		{
			LM_ERR("[%s]: failed to connect to LDAP host(s)\n", ld_name);
			ldap_disconnect(ld_name);
			return -1;
		}

	}

	return 0;
}