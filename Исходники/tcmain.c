static int
WorkerBee(struct cmd_syndesc *as, void *arock)
{
    afs_int32 code, numClasses;
    struct rx_securityClass *(nullObjects[1]), **secObjs, **allObjs;
    struct rx_service *service;
    time_t tokenExpires;
    char cellName[64];
    int localauth;
    /*process arguments */
    afs_int32 portOffset = 0;
#ifdef AFS_PTHREAD_ENV
    pthread_t dbWatcherPid;
    pthread_attr_t tattr;
    AFS_SIGSET_DECL;
#else
    PROCESS dbWatcherPid;
#endif
    char hoststr[16];
    afs_uint32 host = htonl(INADDR_ANY);
    char *auditFileName = NULL;
    char *auditInterface = NULL;

    debugLevel = 0;

    /*initialize the error tables */
    initialize_KA_error_table();
    initialize_RXK_error_table();
    initialize_KTC_error_table();
    initialize_ACFG_error_table();
    initialize_CMD_error_table();
    initialize_VL_error_table();
    initialize_BUTM_error_table();
    initialize_BUTC_error_table();
#ifdef xbsa
    initialize_BUTX_error_table();
#endif /*xbs */
    initialize_VOLS_error_table();
    initialize_BUDB_error_table();
    initialize_BUCD_error_table();

    if (as->parms[0].items) {
	portOffset = SafeATOL(as->parms[0].items->data);
	if (portOffset == -1) {
	    fprintf(stderr, "Illegal port offset '%s'\n",
		    as->parms[0].items->data);
	    exit(1);
	} else if (portOffset > BC_MAXPORTOFFSET) {
	    fprintf(stderr, "%u exceeds max port offset %u\n", portOffset,
		    BC_MAXPORTOFFSET);
	    exit(1);
	}
    }

    xbsaType = XBSA_SERVER_TYPE_NONE;	/* default */
    if (as->parms[3].items) {	/* -device */
	globalTapeConfig.capacity = 0x7fffffff;	/* 2T for max tape capacity */
	globalTapeConfig.fileMarkSize = 0;
	globalTapeConfig.portOffset = portOffset;
	strncpy(globalTapeConfig.device, as->parms[3].items->data, 100);
	xbsaType = XBSA_SERVER_TYPE_NONE;	/* Not XBSA */
    } else {
	/* Search for an entry in tapeconfig file */
	code = GetDeviceConfig(tapeConfigFile, &globalTapeConfig, portOffset);
	if (code == -1) {
	    fprintf(stderr, "Problem in reading config file %s\n",
		    tapeConfigFile);
	    exit(1);
	}
	/* Set xbsaType. If code == 1, no entry was found in the tapeconfig file so
	 * it's an XBSA server. Don't know if its ADSM or not so its unknown.
	 */
	xbsaType =
	    ((code == 1) ? XBSA_SERVER_TYPE_UNKNOWN : XBSA_SERVER_TYPE_NONE);
    }

    if (as->parms[6].items) {	/* -restoretofile */
	restoretofile = strdup(as->parms[6].items->data);
	printf("Restore to file '%s'\n", restoretofile);
    }

    /* Go and read the config file: CFG_<device> or CFG_<port>. We will also set
     * the exact xbsaType within the call (won't be unknown) - double check.
     */
    code = GetConfigParams(pFile, portOffset);
    if (code)
	exit(code);
#ifdef xbsa
    if (xbsaType == XBSA_SERVER_TYPE_UNKNOWN) {
	printf
	    ("\nConfiguration file error, the TYPE parameter must be specified, or\n");
	printf("an entry must exist in %s for port %d\n", tapeConfigFile,
	       portOffset);
	exit(1);
    }
#else
    /* Not compiled for XBSA code so we can't support it */
    if (CONF_XBSA) {
	printf("\nNo entry found in %s for port %d\n", tapeConfigFile,
	       portOffset);
	printf("This binary does not have XBSA support\n");
	exit(1);
    }
#endif

    /* Open the log files. The pathnames were set in GetConfigParams() */
    logIO = fopen(logFile, "a");
    if (!logIO) {
	fprintf(stderr, "Failed to open %s\n", logFile);
	exit(1);
    }
    ErrorlogIO = fopen(ErrorlogFile, "a");
    if (!ErrorlogIO) {
	fprintf(stderr, "Failed to open %s\n", ErrorlogFile);
	exit(1);
    }
    if (lastLog) {
	lastLogIO = fopen(lastLogFile, "a");
	if (!lastLogIO) {
	    fprintf(stderr, "Failed to open %s\n", lastLogFile);
	    exit(1);
	}
    }
    if (centralLogFile) {
	struct stat sbuf;
	afs_int32 statcode;
#ifndef AFS_NT40_ENV
	char *path;
#endif

	statcode = stat(centralLogFile, &sbuf);
	centralLogIO = fopen(centralLogFile, "a");
	if (!centralLogIO) {
	    fprintf(stderr, "Failed to open %s; error %d\n", centralLogFile,
		    errno);
	    exit(1);
	}
#ifndef AFS_NT40_ENV
	/* Make sure it is not in AFS, has to have been created first */
	path = malloc(AFSDIR_PATH_MAX);
	if (path == NULL || !realpath(centralLogFile, path)) {
	    fprintf(stderr,
		    "Warning: can't determine real path of '%s' (%d)\n",
		    centralLogFile, errno);
	} else {
	    if (strncmp(path, "/afs/", 5) == 0) {
		fprintf(stderr, "The central log '%s' should not be in AFS\n",
			centralLogFile);
		exit(1);
	    }
	}
	free(path);
#endif

	/* Write header if created it */
	if (statcode) {
	    char *h1 =
		"TASK   START DATE/TIME      END DATE/TIME        ELAPSED   VOLUMESET\n";
	    char *h2 =
		"-----  -------------------  -------------------  --------  ---------\n";
	    /* File didn't exist before so write the header lines */
	    fwrite(h1, strlen(h1), 1, centralLogIO);
	    fwrite(h2, strlen(h2), 1, centralLogIO);
	    fflush(centralLogIO);
	}
    }

    /* Open the configuration directory */
    butc_confdir = afsconf_Open(AFSDIR_SERVER_ETC_DIRPATH);
    if (butc_confdir == NULL) {
	TLog(0, "Failed to open server configuration directory");
	exit(1);
    }

    /* Start auditing */
    osi_audit_init();
    if (as->parms[9].items) {
	auditFileName = as->parms[9].items->data;
    }
    if (auditFileName != NULL)
	osi_audit_file(auditFileName);
    if (as->parms[10].items) {
	auditInterface = as->parms[10].items->data;
	if (osi_audit_interface(auditInterface)) {
	    TLog(0, "Invalid audit interface '%s'\n", auditInterface);
	    exit(1);
	}
    }
    osi_audit(TC_StartEvent, 0, AUD_END);
    osi_audit_set_user_check(butc_confdir, tc_IsLocalRealmMatch);

    if (as->parms[1].items) {
	debugLevel = SafeATOL(as->parms[1].items->data);
	if (debugLevel == -1) {
	    TLog(0, "Illegal debug level '%s'\n", as->parms[1].items->data);
	    exit(1);
	}
    }
#ifdef xbsa
    /* Setup XBSA library interface */
    if (CONF_XBSA) {
	afs_int32 rc;
	rc = xbsa_MountLibrary(&butxInfo, xbsaType);
	if (rc != XBSA_SUCCESS) {
	    TapeLog(0, 0, rc, 0, "Unable to mount the XBSA library\n");
	    return (1);
	}

	forcemultiple = (as->parms[7].items ? 1 : 0);/*-xbsaforcemultiple */
	if (forcemultiple)
	    printf("Force XBSA multiple server support\n");

	rc = InitToServer(0 /*taskid */ , &butxInfo, adsmServerName);
	if (rc != XBSA_SUCCESS)
	    return (1);
	(void)signal(SIGINT, xbsa_shutdown);
	(void)signal(SIGHUP, xbsa_shutdown);
    }
#endif /*xbsa */

    /* cell switch */
    if (as->parms[2].items)
	strncpy(cellName, as->parms[2].items->data, sizeof(cellName));
    else
	cellName[0] = '\0';

    if (as->parms[4].items)
	autoQuery = 0;

    localauth = (as->parms[5].items ? 1 : 0);
    rxBind = (as->parms[8].items ? 1 : 0);
    allow_unauth = (as->parms[11].items ? 1 : 0);

    if (!allow_unauth && !localauth) {
	const char *errstr = "Neither -localauth nor -allow_unauthenticated was provided; refusing to start in unintended insecure configuration\n";
	TLog(0, "%s", (char *)errstr);
	exit(1);
    }

    if (rxBind) {
        afs_int32 ccode;
        if (AFSDIR_SERVER_NETRESTRICT_FILEPATH ||
            AFSDIR_SERVER_NETINFO_FILEPATH) {
            char reason[1024];
            ccode = afsconf_ParseNetFiles(SHostAddrs, NULL, NULL,
                                          ADDRSPERSITE, reason,
                                          AFSDIR_SERVER_NETINFO_FILEPATH,
                                          AFSDIR_SERVER_NETRESTRICT_FILEPATH);
        } else
	{
            ccode = rx_getAllAddr(SHostAddrs, ADDRSPERSITE);
        }
        if (ccode == 1)
            host = SHostAddrs[0];
    }

    TLog(0, "butc binding rx to %s:%d\n",
         afs_inet_ntoa_r(host, hoststr), BC_TAPEPORT + portOffset);
    code = rx_InitHost(host, htons(BC_TAPEPORT + portOffset));
    if (code) {
	TapeLog(0, 0, code, 0, "rx init failed on port %u\n",
		BC_TAPEPORT + portOffset);
	exit(1);
    }
    rx_SetRxDeadTime(150);

    /* Establish connection with the vldb server */
    code = vldbClientInit(0, localauth, cellName, &cstruct, &tokenExpires);
    if (code) {
	TapeLog(0, 0, code, 0, "Can't access vldb\n");
	return code;
    }

    strcpy(globalCellName, cellName);

    /*initialize the dumpNode list */
    InitNodeList(portOffset);

    deviceLatch = malloc(sizeof(struct deviceSyncNode));
    Lock_Init(&(deviceLatch->lock));
    deviceLatch->flags = 0;

    /* initialize database support, volume support, and logs */

    /*
     * Create security objects for the Rx server functionality.  Historically
     * this was a single rxnull security object, since the tape controller was
     * run by an operator that had local access to the tape device and some
     * administrative privilege in the cell (to be able to perform volume-level
     * accesses), but on a machine that was not necessarily trusted to hold the
     * cell-wide key.
     *
     * Such a configuration is, of course, insecure because anyone can make
     * inbound RPCs and manipulate the database, including creating bogus
     * dumps and restoring them!  Additionally, in modern usage, butc is
     * frequently run with -localauth to authenticate its outbound connections
     * to the volservers and budb with the cell-wide key, in which case the
     * cell-wide key is present and could be used to authenticate incoming
     * connections as well.
     *
     * If -localauth is in use, create the full barrage of server security
     * objects, including rxkad, so that inbound connections can be verified
     * to only be made by authenticated clients.  Otherwise, only the rxnull
     * class is in use with a single server security object.  Note that butc
     * will refuse to start in this configuration unless the
     * "-allow_unauthenticated" flag is provided, indicating that the operator
     * has ensured that incoming connections are appropriately restricted by
     * firewall configuration or network topology.
     */

    if (allow_unauth) {
	nullObjects[RX_SECIDX_NULL] = rxnull_NewServerSecurityObject();
	if (!nullObjects[RX_SECIDX_NULL]) {
	    TLog(0, "rxnull_NewServerSecurityObject");
	    exit(1);
	}
	numClasses = 1;
	secObjs = nullObjects;
    } else {
	/* Must be -localauth, so the cell keys are available. */
	afsconf_BuildServerSecurityObjects(butc_confdir, &allObjs, &numClasses);
	secObjs = allObjs;
    }

    service =
	rx_NewServiceHost(host, 0, 1, "BUTC", secObjs, numClasses, TC_ExecuteRequest);
    if (!service) {
	TLog(0, "rx_NewService");
	exit(1);
    }
    rx_SetMaxProcs(service, 4);

    /* Establish connection to the backup database */
    code = udbClientInit(0, localauth, cellName);
    if (code) {
	TapeLog(0, 0, code, 0, "Can't access backup database\n");
	exit(1);
    }
    /* This call is here to verify that we are authentiated.
     * The call does nothing and will return BUDB_NOTPERMITTED
     * if we don't belong.
     */
    code = bcdb_deleteDump(0, 0, 0, 0);
    if (code == BUDB_NOTPERMITTED) {
	TapeLog(0, 0, code, 0, "Can't access backup database\n");
	exit(1);
    }

    initStatus();
#ifdef AFS_PTHREAD_ENV
    code = pthread_attr_init(&tattr);
    if (code) {
	TapeLog(0, 0, code, 0,
		"Can't pthread_attr_init database monitor task");
	exit(1);
    }
    code = pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
    if (code) {
	TapeLog(0, 0, code, 0,
		"Can't pthread_attr_setdetachstate database monitor task");
	exit(1);
    }
    AFS_SIGSET_CLEAR();
    code = pthread_create(&dbWatcherPid, &tattr, dbWatcher, (void *)2);
    AFS_SIGSET_RESTORE();
#else
    code =
	LWP_CreateProcess(dbWatcher, 20480, LWP_NORMAL_PRIORITY, (void *)2,
			  "dbWatcher", &dbWatcherPid);
#endif
    if (code) {
	TapeLog(0, 0, code, 0, "Can't create database monitor task");
	exit(1);
    }

    TLog(0, "Starting Tape Coordinator: Port offset %u   Debug level %u\n",
	 portOffset, debugLevel);
    TLog(0, "Token expires: %s\n", cTIME(&tokenExpires));

    rx_StartServer(1);		/* Donate this process to the server process pool */
    TLog(0, "Error: StartServer returned");
    exit(1);
}