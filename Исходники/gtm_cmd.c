int
remove_gtmSlave(bool clean_opt)
{
	FILE *f;

	/* Check if gtm_slave is configured */
	if (!isVarYes(VAR_gtmSlave) || !sval(VAR_gtmSlaveServer) || is_none(sval(VAR_gtmSlaveServer)))
	{
		elog(ERROR, "ERROR: GTM slave is not configured.\n");
		return 1;
	}
	/* Check if gtm_slave is not running */
	if (!do_gtm_ping(sval(VAR_gtmSlaveServer), atoi(sval(VAR_gtmSlavePort))))
	{
		elog(ERROR, "ERROR: GTM slave is now running. Cannot remove it.\n");
		return 1;
	}
	elog(NOTICE, "Removing gtm slave.\n");
	/* Clean */
	if (clean_opt)
		clean_gtm_slave();
	/* Reconfigure */
	reset_var(VAR_gtmSlave);
	assign_sval(VAR_gtmSlave, Strdup("n"));
	reset_var(VAR_gtmSlaveServer);
	assign_sval(VAR_gtmSlaveServer, Strdup("none"));
	reset_var(VAR_gtmSlavePort);
	assign_sval(VAR_gtmSlavePort, Strdup("-1"));
	reset_var(VAR_gtmSlaveDir);
	assign_sval(VAR_gtmSlaveDir, Strdup("none"));
	/* Write the configuration file and bakup it */
	if ((f = fopen(pgxc_ctl_config_path, "a")) == NULL)
	{
		/* Should it be panic? */
		elog(ERROR, "ERROR: cannot open configuration file \"%s\", %s\n", pgxc_ctl_config_path, strerror(errno));
		return 1;
	}
	fprintf(f, 
			"#===================================================\n"
			"# pgxc configuration file updated due to GTM slave removal\n"
			"#        %s\n",
			timeStampString(date, MAXTOKEN+1));
	fprintSval(f, VAR_gtmSlave);
	fprintSval(f, VAR_gtmSlaveServer);
	fprintSval(f, VAR_gtmSlavePort);
	fprintSval(f, VAR_gtmSlaveDir);
	fprintf(f, "%s", "#----End of reconfiguration -------------------------\n");
	fclose(f);
	backup_configuration();
	elog(NOTICE, "Done.\n");
	return 0;
}