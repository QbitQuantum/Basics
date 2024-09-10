int main (int argc, char **argv)
{
    int				k;
    int				fd;
    uint32_t			driverVersion = 0;
    uint32_t			numAdapters;
    int				startSelfTest = -1;
    int				healthCheck = 0;
    int				checkBattery = 1;
    char			*device = MEGA_DEVICE;
    struct query_object {
	int			    adapter;
	int			    channel;
	int			    id;
    }				*object = NULL;
    int				numObjects = 0;
    uint8_t			readLog[LOG_PAGE_MAX] = { 0, };
    int				reportPhysical = 1;
    int				showVersion = 0;
#ifdef	MEGA_SAS_CTL
    int				sas = 1;
#else
    int				sas = 0;
#endif

    if ((me = strrchr (argv[0], '/')))
	++me;
    else
	me = argv[0];

    if (argc > 1)
    {
	if ((object = (struct query_object *) malloc ((argc - 1) * sizeof (*object))) == NULL)
	{
	    perror ("malloc");
	    return 1;
	}
    }

    for (k = 1; k < argc; ++k)
    {
	if (argv[k][0] == '-')
	{
	    char		*s;

	    for (s = argv[k] + 1; *s; ++s)
	    {
		if (*s == 'v')
		{
		    ++verbosity;
		    continue;
		}
		if (*s == 'e')
		{
		    /* read error log pages */
		    readLog[0x02] = 1;	/* write errors */
		    readLog[0x03] = 1;	/* read errors */
		    readLog[0x05] = 1;	/* read errors */
		    continue;
		}
		if (*s == 's')
		{
		    /* read self test log page */
		    readLog[0x10] = 1;
		    continue;
		}
		if (*s == 't')
		{
		    /* read temperature log page */
		    readLog[0x0d] = 1;
		    continue;
		}
		if (*s == 'l')
		{
		    /* read specific log page */
		    char		*t;
		    unsigned long	u;

		    if ((++k) >= argc)
			usage (2, "no log page specified");
		    u = strtoul (argv[k], &t, 0);
		    if (*t)
			usage (2, "invalid log page \"%s\"", argv[k]);
		    if (u >= sizeof (readLog) / sizeof (readLog[0]))
			usage (2, "log page out of range: \"%s\"", argv[k]);
		    readLog[u] = 1;
		    continue;
		}
		if (*s == 'D')
		{
		    /* specify device file */
		    if ((++k) >= argc)
			usage (2, "no device specified");
		    device = argv[k];
		    continue;
		}
		if (*s == 'p')
		{
		    reportPhysical = 0;;
		    continue;
		}
		if (*s == 'B')
		{
		    /* skip battery check */
		    checkBattery = 0;
		    continue;
		}
		if (*s == 'H')
		{
		    /* perform adapter health check */
		    ++healthCheck;
		    continue;
		}
		if (*s == 'T')
		{
		    /* start self test */
		    if ((++k) >= argc)
			usage (2, "must specify short or long self-test");
		    if (!strcmp (argv[k], "short"))
			startSelfTest = SCSI_SELFTEST_BACKGROUND_SHORT;
		    else if (!strcmp (argv[k], "long"))
			startSelfTest = SCSI_SELFTEST_BACKGROUND_LONG;
		    else
			usage (2, "invalid self test: \"%s\"; must specify short or long", argv[k]);
		    continue;
		}
		else if ((*s == '?') || (*s == 'h'))
		    usage (0, NULL);
		else if (*s == 'V')
		{
		    ++showVersion;
		    continue;
		}
		usage (2, "invalid flag \"%s\"", s);
	    }
	}
	else
	{
	    char		*s;
	    char		*t;
	    unsigned long	l;

	    s = argv[k];
	    object[numObjects].adapter = -1;
	    object[numObjects].channel = -1;
	    object[numObjects].id = -1;

	    if (*s)
	    {
		if (tolower (*s) != 'a')
		    usage (2, "invalid specifier \"%s\"", argv[k]);
		++s;
		l = strtoul (s, &t, 10);
		if (s == t)
		    usage (2, "invalid specifier \"%s\"", argv[k]);
#ifndef	MEGA_SAS_CTL
		if (l >= MAX_CONTROLLERS)
		    usage (2, "adapter out of range: \"%s\"", argv[k]);
#endif
		object[numObjects].adapter = l;
		s = t;
	    }

	    if (*s)
	    {
		if (tolower (*s) != (sas ? 'e' : 'c'))
		    usage (2, "invalid specifier \"%s\"", argv[k]);
		++s;
		l = strtoul (s, &t, 10);
		if (s == t)
		    usage (2, "invalid specifier \"%s\"", argv[k]);
#ifndef	MEGA_SAS_CTL
		if (l >= MAX_MBOX_CHANNELS)
		    usage (2, "channel out of range: \"%s\"", argv[k]);
#endif
		object[numObjects].channel = l;
		s = t;
	    }

	    if (*s)
	    {
		if (tolower (*s) != (sas ? 's' : 't'))
		    usage (2, "invalid specifier \"%s\"", argv[k]);
		++s;
		l = strtoul (s, &t, 10);
		if (s == t)
		    usage (2, "invalid specifier \"%s\"", argv[k]);
#ifndef	MEGA_SAS_CTL
		if (l > MAX_MBOX_TARGET)
		    usage (2, "target out of range: \"%s\"", argv[k]);
#endif
		object[numObjects].id = l;
		s = t;
	    }

	    ++numObjects;
	}
    }

    if (showVersion)
    {
	if (verbosity)
	    fprintf (stdout, "%s: version %s by Jefferson Ogata\n", me, version);
	else
	    fprintf (stdout, "%s\n", version);
	return 0;
    }

    if (healthCheck)
    {
	int			set = 0;

	for (k = 0; k < numObjects; ++k)
	    if ((object[k].channel >= 0) || (object[k].id >= 0))
		usage (2, "for health check, must specify adapter only");
	for (k = 0; k < sizeof readLog / sizeof (readLog[0]); ++k)
	    if (readLog[k])
	    {
		set = 1;
		break;
	    }
	if (set == 0)
	{
	    /* No specific log pages requested; check read/write/verify errors and temperature. */
	    readLog[0x02] = 1;
	    readLog[0x03] = 1;
	    readLog[0x05] = 1;
	    readLog[0x0d] = 1;
	}
    }

    if ((fd = open (device, O_RDONLY)) < 0)
    {
	fprintf (stderr, "unable to open device %s: %s\n", device, strerror (errno));
	return 1;
    }

#ifndef	MEGA_SAS_CTL
    if (megaGetDriverVersion (fd, &driverVersion) < 0)
    {
	fprintf (stderr, "unable to determine megaraid driver version: %s\n", megaErrorString ());
	return 1;
    }

    if (driverVersion < MEGA_MIN_VERSION)
    {
	fprintf (stderr, "megaraid driver version %x too old.\n", driverVersion);
	return 1;
    }
#endif

    if (megaGetNumAdapters (fd, &numAdapters, sas) < 0)
    {
	fprintf (stderr, "unable to find any adapters: %s\n", megaErrorString ());
	return 1;
    }

    if (verbosity > 2)
	fprintf (stderr, "%u adapters, driver version %08x\n\n", numAdapters, driverVersion);

    /* Default to enumerating all adapters. */
    if (numObjects == 0)
    {
	if (object)
	    free (object);
	if ((object = (struct query_object *) malloc (numAdapters * sizeof (*object))) == NULL)
	{
	    perror ("malloc");
	    return 1;
	}
	for (k = 0; k < numAdapters; ++k)
	{
	    object[k].adapter = k;
	    object[k].channel = -1;
	    object[k].id = -1;
	}
	numObjects = k;
    }

    for (k = 0; k < numObjects; ++k)
    {
	int				adapter = object[k].adapter;
	int				channel = object[k].channel;
	int				id = object[k].id;
	char				name[32];
	struct adapter_config		*a;
	uint32_t			c;
	uint32_t			i;
	int				j;

	if (id >= 0)
	    snprintf (name, sizeof name, "a%u%c%u%c%u", adapter, sas ? 'e' : 'c', channel, sas ? 's' : 't', id);
	else if (channel >= 0)
	    snprintf (name, sizeof name, "a%u%c%u", adapter, sas ? 'e' : 'c', channel);
	else
	    snprintf (name, sizeof name, "a%u", adapter);

	if (adapter >= numAdapters)
	{
	    fprintf (stderr, "%s: no such adapter\n", name);
	    continue;
	}

	if ((a = getAdapterConfig (fd, adapter, sas)) == NULL)
	{
	    fprintf (stderr, "%s: cannot read adapter configuration: %s\n", name, megaErrorString ());
	    break;
	}

	if (healthCheck)
	{
	    int				adapterReported = 0;
	    struct logical_drive_info	*l;

	    if (checkBattery && (!a->battery.healthy))
	    {
		if (!(adapterReported++))
		    describeAdapter (stdout, a, verbosity);
	    }

#ifndef	MEGA_SAS_CTL
	    /* Scan all physical devices. */
	    for (c = 0; c < a->num_channels; ++c)
	    {
		for (i = 0; i <= MAX_MBOX_TARGET; ++i)
		{
		    uint8_t			target = (a->channel[c] << 4) | i;

		    (void) getPhysicalDriveInfo (a, target, 1);
		}
	    }
#endif

	    for (i = 0, l = a->logical; i < a->num_logicals; ++i, ++l)
	    {
		int				reportDrive = 0;

		if ((l->state != LdStateOptimal) && (l->state != LdStateDeleted))
		    ++reportDrive;

		if (reportDrive)
		{
		    if (!(adapterReported++))
			describeAdapter (stdout, a, verbosity);
		    describeLogicalDrive (stdout, l, verbosity);
		}
	    }

	    for (i = 0; i < a->num_physicals; ++i)
	    {
		struct physical_drive_info	*d = a->physical_list[i];
		int				reportDrive = 0;
		struct log_page_list		*log;

		if (d == NULL)
		    break;
		if (!(d->present))
		    continue;

//describePhysicalDrive (stdout, d, verbosity);

		/* check for drive problems */
		if ((d->state == PdStateRebuild) || (d->span && (d->state == PdStateFailed)))
		    ++reportDrive;
		if (d->media_errors)
		    ++reportDrive;
		if (d->predictive_failures)
		    ++reportDrive;

		/* check interesting log pages */
		for (j = 0; j < sizeof (readLog) / sizeof (readLog[0]); ++j)
		{
		    if (readLog[j] == 0)
			continue;

		    if ((log = getDriveLogPage (d, j)) == NULL)
			continue;

		    if (log->log.problem)
			++reportDrive;
		}

		if (reportDrive)
		{
		    if (!(adapterReported++))
			describeAdapter (stdout, a, verbosity);
		    describePhysicalDrive (stdout, d, verbosity);
		    for (j = 0; j < sizeof (readLog) / sizeof (readLog[0]); ++j)
		    {
			if (readLog[j] == 0)
			    continue;

			if ((log = getDriveLogPage (d, j)) == NULL)
			    continue;

			dumpLogPage (stdout, &log->log, NULL, 0, verbosity);
		    }
		}
	    }
	    continue;
	}

	if (channel >= 0)
	{
	    for (c = 0; c < a->num_channels; ++c)
		if (channel == a->channel[c])
		    break;
	    if (c >= a->num_channels)
	    {
		fprintf (stderr, "%s: no such channel\n", name);
		continue;
	    }
	}

	if ((channel < 0) && (id < 0))
	{
	    struct logical_drive_info	*l;
	    int				x;

	    describeAdapter (stdout, a, verbosity);

#ifndef	MEGA_SAS_CTL
	    /* Scan all physical devices. */
	    for (c = 0; c < a->num_channels; ++c)
	    {
		for (i = 0; i <= MAX_MBOX_TARGET; ++i)
		{
		    uint8_t			target = (a->channel[c] << 4) | i;

		    (void) getPhysicalDriveInfo (a, target, 1);
		}
	    }
#endif

	    for (i = 0, l = a->logical; i < a->num_logicals; ++i, ++l)
		describeLogicalDrive (stdout, l, verbosity);

	    x = 0;

	    for (i = 0; i < a->num_physicals; ++i)
	    {
		struct physical_drive_info	*d = a->physical_list[i];

		if (d == NULL)
		    break;
		if (!(d->present))
		    continue;

		if (d->state == PdStateHotspare)
		{
		    if (x == 0)
			fprintf (stdout, "hot spares  :");
		    else if ((x % 8) == 0)
			fprintf (stdout, "            :");
		    fprintf (stdout, "  %-8s", d->name);
		    if (((++x) % 8) == 0)
			fprintf (stdout, "\n");
		}
	    }
	    if (x % 8)
		fprintf (stdout, "\n");

	    x = 0;
	    for (i = 0; i < a->num_physicals; ++i)
	    {
		struct physical_drive_info	*d = a->physical_list[i];

		if (d == NULL)
		    break;
		if (!(d->present))
		    continue;

		if ((!(d->span)) && (d->state != PdStateHotspare))
		{
		    if (x == 0)
			fprintf (stdout, "unconfigured:");
		    else if ((x % 8) == 0)
			fprintf (stdout, "            :");
		    fprintf (stdout, "  %-8s", d->name);
		    if (((++x) % 8) == 0)
			fprintf (stdout, "\n");
		}
	    }
	    if (x % 8)
		fprintf (stdout, "\n");
	}

	for (c = 0; c < a->num_channels; ++c)
	{
	    if ((channel >= 0) && (channel != a->channel[c]))
		continue;

#ifndef	MEGA_SAS_CTL
	    if (id >= 0)
	    {
		uint8_t			target = (a->channel[c] << 4) | id;
		(void) getPhysicalDriveInfo (a, target, 1);
	    }
	    else
	    {
		/* Scan all devices on this channel. */
		for (i = 0; i <= MAX_MBOX_TARGET; ++i)
		{
		    uint8_t			target = (a->channel[c] << 4) | i;

		    (void) getPhysicalDriveInfo (a, target, 1);
		}
	    }
#endif

	    for (i = 0; i < a->num_physicals; ++i)
	    {
		struct physical_drive_info	*d = a->physical_list[i];

		if (d == NULL)
		    break;

		if (d->channel != a->channel[c])
		    continue;

		if ((id >= 0) && (id != d->id))
		    continue;

		if (startSelfTest >= 0)
		{
		    uint8_t		diag[256];

		    memset (diag, 0, sizeof diag);
		    if (megaScsiSendDiagnostic (&a->target, d->target, diag, sizeof diag, startSelfTest, 0, 0) < 0)
			fprintf (stderr, "self test: %s\n", megaErrorString ());
		}

		if (reportPhysical)
		{
		    describePhysicalDrive (stdout, d, verbosity);
		    for (j = 0; j < sizeof (readLog) / sizeof (readLog[0]); ++j)
		    {
			struct log_page_list	*log;

			if (readLog[j] == 0)
			    continue;

			if ((log = getDriveLogPage (d, j)) == NULL)
			    continue;

			dumpLogPage (stdout, &log->log, &log->buf, sizeof (log->buf), verbosity);
		    }
		}
	    }
	}

	fprintf (stdout, "\n");
    }

    return 0;
}