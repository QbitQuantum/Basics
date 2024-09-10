/*
 * Find the gtm port and try a connection
 */
static bool
test_gtm_connection()
{
	GTM_Conn	   *conn;
	bool		success = false;
	int			i;
	char		portstr[32];
	char	   *p;
	char	   *q;
	char		connstr[128];	/* Should be way more than enough! */

	*portstr = '\0';

	/*
	 * Look in gtm_opts for a -p switch.
	 *
	 * This parsing code is not amazingly bright; it could for instance
	 * get fooled if ' -p' occurs within a quoted argument value.  Given
	 * that few people pass complicated settings in gtm_opts, it's
	 * probably good enough.
	 */
	for (p = gtm_opts; *p;)
	{
		/* advance past whitespace */
		while (isspace((unsigned char) *p))
			p++;

		if (strncmp(p, "-p", 2) == 0)
		{
			p += 2;
			/* advance past any whitespace/quoting */
			while (isspace((unsigned char) *p) || *p == '\'' || *p == '"')
				p++;
			/* find end of value (not including any ending quote!) */
			q = p;
			while (*q &&
				   !(isspace((unsigned char) *q) || *q == '\'' || *q == '"'))
				q++;
			/* and save the argument value */
			strlcpy(portstr, p, Min((q - p) + 1, sizeof(portstr)));
			/* keep looking, maybe there is another -p */
			p = q;
		}
		/* Advance to next whitespace */
		while (*p && !isspace((unsigned char) *p))
			p++;
	}

	/*
	 * Search config file for a 'port' option.
	 *
	 * This parsing code isn't amazingly bright either, but it should be okay
	 * for valid port settings.
	 */
	if (!*portstr)
	{
		char      **optlines;

		optlines = readfile(conf_file);
		if (optlines != NULL)
		{
			for (; *optlines != NULL; optlines++)
			{
				p = *optlines;

				while (isspace((unsigned char) *p))
					p++;
				if (strncmp(p, "port", 4) != 0)
					continue;
				p += 4;
				while (isspace((unsigned char) *p))
					p++;
				if (*p != '=')
					continue;
				p++;
				/* advance past any whitespace/quoting */
				while (isspace((unsigned char) *p) || *p == '\'' || *p == '"')
					p++;
				/* find end of value (not including any ending quote/comment!) */
				q = p;
				while (*q &&
					   !(isspace((unsigned char) *q) ||
						 *q == '\'' || *q == '"' || *q == '#'))
					q++;
				/* and save the argument value */
				strlcpy(portstr, p, Min((q - p) + 1, sizeof(portstr)));
				/* keep looking, maybe there is another */
			}
		}
	}

	/* Still not found? Use compiled-in default */
#define GTM_DEFAULT_PORT               6666
	if (!*portstr)
		snprintf(portstr, sizeof(portstr), "%d", GTM_DEFAULT_PORT);

	/*
	 * We need to set a connect timeout otherwise on Windows the SCM will
	 * probably timeout first
	 * a PGXC node ID has to be set for GTM connection protocol,
	 * so its value doesn't really matter here.
	 */
	snprintf(connstr, sizeof(connstr),
			 "host=localhost port=%s connect_timeout=5 node_name=one", portstr);

	for (i = 0; i < wait_seconds; i++)
	{
		if ((conn = PQconnectGTM(connstr)) != NULL &&
			(GTMPQstatus(conn) == CONNECTION_OK))
		{
			GTMPQfinish(conn);
			success = true;
			break;
		}
		else
		{
			GTMPQfinish(conn);
			print_msg(".");
			sleep(1); /* 1 sec */
		}
	}

	return success;
}