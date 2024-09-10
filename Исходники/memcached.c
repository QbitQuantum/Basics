static int memcached_read (void) /* {{{ */
{
	char buf[1024];
	char *fields[3];
	char *ptr;
	char *line;
	char *saveptr;
	int fields_num;

	gauge_t bytes_used = NAN;
	gauge_t bytes_total = NAN;
	gauge_t hits = NAN;
	gauge_t gets = NAN;
	counter_t rusage_user = 0;
	counter_t rusage_syst = 0;
	counter_t octets_rx = 0;
	counter_t octets_tx = 0;

	/* get data from daemon */
	if (memcached_query_daemon (buf, sizeof (buf)) < 0) {
		return -1;
	}

#define FIELD_IS(cnst) \
	(((sizeof(cnst) - 1) == name_len) && (strcmp (cnst, fields[1]) == 0))

	ptr = buf;
	saveptr = NULL;
	while ((line = strtok_r (ptr, "\n\r", &saveptr)) != NULL)
	{
		int name_len;

		ptr = NULL;

		fields_num = strsplit(line, fields, 3);
		if (fields_num != 3)
			continue;

		name_len = strlen(fields[1]);
		if (name_len == 0)
			continue;

		/*
		 * For an explanation on these fields please refer to
		 * <http://code.sixapart.com/svn/memcached/trunk/server/doc/protocol.txt>
		 */

		/*
		 * CPU time consumed by the memcached process
		 */
		if (FIELD_IS ("rusage_user"))
		{
			rusage_user = atoll (fields[2]);
		}
		else if (FIELD_IS ("rusage_system"))
		{
			rusage_syst = atoll(fields[2]);
		}

		/*
		 * Number of threads of this instance
		 */
		else if (FIELD_IS ("threads"))
		{
			submit_gauge2 ("ps_count", NULL, NAN, atof (fields[2]));
		}

		/*
		 * Number of items stored
		 */
		else if (FIELD_IS ("curr_items"))
		{
			submit_gauge ("memcached_items", "current", atof (fields[2]));
		}

		/*
		 * Number of bytes used and available (total - used)
		 */
		else if (FIELD_IS ("bytes"))
		{
			bytes_used = atof (fields[2]);
		}
		else if (FIELD_IS ("limit_maxbytes"))
		{
			bytes_total = atof(fields[2]);
		}

		/*
		 * Connections
		 */
		else if (FIELD_IS ("curr_connections"))
		{
			submit_gauge ("memcached_connections", "current", atof (fields[2]));
		}

		/*
		 * Commands
		 */
		else if ((name_len > 4) && (strncmp (fields[1], "cmd_", 4) == 0))
		{
			const char *name = fields[1] + 4;
			submit_counter ("memcached_command", name, atoll (fields[2]));
			if (strcmp (name, "get") == 0)
				gets = atof (fields[2]);
		}

		/*
		 * Operations on the cache, i. e. cache hits, cache misses and evictions of items
		 */
		else if (FIELD_IS ("get_hits"))
		{
			submit_counter ("memcached_ops", "hits", atoll (fields[2]));
			hits = atof (fields[2]);
		}
		else if (FIELD_IS ("get_misses"))
		{
			submit_counter ("memcached_ops", "misses", atoll (fields[2]));
		}
		else if (FIELD_IS ("evictions"))
		{
			submit_counter ("memcached_ops", "evictions", atoll (fields[2]));
		}

		/*
		 * Network traffic
		 */
		else if (FIELD_IS ("bytes_read"))
		{
			octets_rx = atoll (fields[2]);
		}
		else if (FIELD_IS ("bytes_written"))
		{
			octets_tx = atoll (fields[2]);
		}
	} /* while ((line = strtok_r (ptr, "\n\r", &saveptr)) != NULL) */

	if (!isnan (bytes_used) && !isnan (bytes_total) && (bytes_used <= bytes_total))
		submit_gauge2 ("df", "cache", bytes_used, bytes_total - bytes_used);

	if ((rusage_user != 0) || (rusage_syst != 0))
		submit_counter2 ("ps_cputime", NULL, rusage_user, rusage_syst);

	if ((octets_rx != 0) || (octets_tx != 0))
		submit_counter2 ("memcached_octets", NULL, octets_rx, octets_tx);

	if (!isnan (gets) && !isnan (hits))
	{
		gauge_t rate = NAN;

		if (gets != 0.0)
			rate = 100.0 * hits / gets;

		submit_gauge ("percent", "hitratio", rate);
	}

	return 0;
}