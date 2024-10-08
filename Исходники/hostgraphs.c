void parse_query(void)
{
	cgidata_t *cgidata, *cwalk;
	int sday = 0, smon = 0, syear = 0, eday = 0, emon = 0, eyear = 0;
	int smin = 0, shour = 0, ssec = 0, emin = -1, ehour = -1, esec = -1;
	int hostcount = 0, testcount = 0, alltests = 0;

	cgidata = cgi_request();
	if (cgidata == NULL) return;

	cwalk = cgidata;
	while (cwalk) {
		/*
		 * cwalk->name points to the name of the setting.
		 * cwalk->value points to the value (may be an empty string).
		 */

		if ((strcmp(cwalk->name, "hostpattern") == 0) && cwalk->value && strlen(cwalk->value)) {
			hostpattern = strdup(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "pagepattern") == 0) && cwalk->value && strlen(cwalk->value)) {
			pagepattern = strdup(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "ippattern") == 0)   && cwalk->value && strlen(cwalk->value)) {
			ippattern = strdup(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "classpattern") == 0)   && cwalk->value && strlen(cwalk->value)) {
			classpattern = strdup(cwalk->value);
		}
		else if (strcmp(cwalk->name, "DoReport") == 0) {
			action = A_GENERATE;
		}
		else if ((strcmp(cwalk->name, "hostname") == 0)   && cwalk->value && strlen(cwalk->value)) {
			if (!hosts) hosts = (char **) malloc(sizeof(char *));

			hosts = (char **)realloc(hosts, (hostcount+2) * sizeof(char *));
			hosts[hostcount] = strdup(cwalk->value); hostcount++;

			hosts[hostcount] = NULL;
		}
		else if ((strcmp(cwalk->name, "testname") == 0)   && cwalk->value && strlen(cwalk->value)) {
			if (!tests) tests = (char **) malloc(sizeof(char *));

			if (strcmp(cwalk->value, "ALL") == 0) {
				alltests = 1;
			}
			else {
				tests = (char **)realloc(tests, (testcount+2) * sizeof(char *));
				tests[testcount] = strdup(cwalk->value); testcount++;
			}

			tests[testcount] = NULL;
		}
		else if ((strcmp(cwalk->name, "start-day") == 0)   && cwalk->value && strlen(cwalk->value)) {
			sday = atoi(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "start-mon") == 0)   && cwalk->value && strlen(cwalk->value)) {
			smon = atoi(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "start-yr") == 0)   && cwalk->value && strlen(cwalk->value)) {
			syear = atoi(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "start-hour") == 0)   && cwalk->value && strlen(cwalk->value)) {
			shour = atoi(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "start-min") == 0)   && cwalk->value && strlen(cwalk->value)) {
			smin = atoi(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "start-sec") == 0)   && cwalk->value && strlen(cwalk->value)) {
			ssec = atoi(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "end-day") == 0)   && cwalk->value && strlen(cwalk->value)) {
			eday = atoi(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "end-mon") == 0)   && cwalk->value && strlen(cwalk->value)) {
			emon = atoi(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "end-yr") == 0)   && cwalk->value && strlen(cwalk->value)) {
			eyear = atoi(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "end-hour") == 0)   && cwalk->value && strlen(cwalk->value)) {
			ehour = atoi(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "end-min") == 0)   && cwalk->value && strlen(cwalk->value)) {
			emin = atoi(cwalk->value);
		}
		else if ((strcmp(cwalk->name, "end-sec") == 0)   && cwalk->value && strlen(cwalk->value)) {
			esec = atoi(cwalk->value);
		}

		cwalk = cwalk->next;
	}

	if (action == A_GENERATE) {
		struct tm tm;

		memset(&tm, 0, sizeof(tm));
		tm.tm_mday = sday;
		tm.tm_mon = smon - 1;
		tm.tm_year = syear - 1900;
		tm.tm_hour = shour;
		tm.tm_min  = smin;
		tm.tm_sec  = ssec;
		tm.tm_isdst = -1;
		starttime = mktime(&tm);

		if (ehour == -1) ehour = 23;
		if (emin  == -1) emin  = 59;
		if (esec  == -1) esec  = 59;
		memset(&tm, 0, sizeof(tm));
		tm.tm_mday = eday;
		tm.tm_mon = emon - 1;
		tm.tm_year = eyear - 1900;
		tm.tm_hour = ehour;
		tm.tm_min  = emin;
		tm.tm_sec  = esec;
		tm.tm_isdst = -1;
		endtime = mktime(&tm);
	}

	if (alltests) {
		if (tests) xfree(tests); testcount = 0;
		tests = (char **) calloc(8, sizeof(char *));

		if (hostcount == 1) {
			tests[testcount] = strdup("cpu"); testcount++;
			tests[testcount] = strdup("disk"); testcount++;
			tests[testcount] = strdup("memory"); testcount++;
			tests[testcount] = strdup("conn"); testcount++;
		}
		else {
			tests[testcount] = strdup("cpu"); testcount++;
			tests[testcount] = strdup("ram"); testcount++;
			tests[testcount] = strdup("mem"); testcount++;
			tests[testcount] = strdup("swap"); testcount++;
			tests[testcount] = strdup("conn-multi"); testcount++;
			tests[testcount] = strdup("netstat3"); testcount++;
			tests[testcount] = strdup("apache3"); testcount++;
		}

		tests[testcount] = NULL;
	}

	if (hostcount > 1) {
		int i;

		for (i = 0; (i < testcount); i++) {
			if (strcmp(tests[i], "conn") == 0) tests[i] = strdup("conn-multi");
		}
	}
}