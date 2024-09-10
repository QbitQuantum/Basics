/*
 * set up all the config files
 */
static void
setup_config(void)
{
	char	  **conflines;
	char		repltok[100];
	char		path[MAXPGPATH];

	fputs(_("creating configuration files ... "), stdout);
	fflush(stdout);

	/* gtm.conf/gtm_proxy.conf */

	conflines = readfile(conf_file);

	/* Set options dedicated to both nodes */
	snprintf(repltok, sizeof(repltok), "nodename = '%s'", n_name);
	conflines = replace_token(conflines, "#nodename = ''", repltok);

	snprintf(repltok, sizeof(repltok), "port = %d", n_port);
	conflines = replace_token(conflines, "#port = 6666", repltok);

	if (is_gtm)
		snprintf(path, sizeof(path), "%s/gtm.conf", pg_data);
	else
	{
		/* Set options dedicated to Proxy */
		snprintf(repltok, sizeof(repltok), "gtm_host = '%s'", gtm_host);
		conflines = replace_token(conflines, "#gtm_host = ''", repltok);

		snprintf(repltok, sizeof(repltok), "gtm_port = %d", gtm_port);
		conflines = replace_token(conflines, "#gtm_port =", repltok);

		snprintf(path, sizeof(path), "%s/gtm_proxy.conf", pg_data);
	}

	writefile(path, conflines);
	chmod(path, S_IRUSR | S_IWUSR);

	free(conflines);

	check_ok();
}