PtpClock *
ptpdStartup(int argc, char **argv, Integer16 * ret, RunTimeOpts * rtOpts)
{
    PtpClock * ptpClock;
    int i = 0;

    /*
     * Set the default mode for all newly created files - previously
     * this was not the case for log files. This adds consistency
     * and allows to use FILE* vs. fds everywhere
     */
    umask(~DEFAULT_FILE_PERMS);

    /**
     * If a required setting, such as interface name, or a setting
     * requiring a range check is to be set via getopts_long,
     * the respective currentConfig dictionary entry should be set,
     * instead of just setting the rtOpts field.
     *
     * Config parameter evaluation priority order:
     * 	1. Any dictionary keys set in the getopt_long loop
     * 	2. CLI long section:key type options
     * 	3. Config file (parsed last), merged with 2. and 3 - will be overwritten by CLI options
     * 	4. Defaults and any rtOpts fields set in the getopt_long loop
    **/

    /**
     * Load defaults. Any options set here and further inside loadCommandLineOptions()
     * by setting rtOpts fields, will be considered the defaults
     * for config file and section:key long options.
     */
    loadDefaultSettings(rtOpts);
    /* initialise the config dictionary */
    rtOpts->candidateConfig = dictionary_new(0);
    rtOpts->cliConfig = dictionary_new(0);
    /* parse all long section:key options and clean up argv for getopt */
    loadCommandLineKeys(rtOpts->cliConfig,argc,argv);
    /* parse the normal short and long option, exit on error */
    if (!loadCommandLineOptions(rtOpts, rtOpts->cliConfig, argc, argv, ret)) {
        goto fail;
    }

    /* Display startup info and argv if not called with -? or -H */
    NOTIFY("%s version %s starting\n",USER_DESCRIPTION, USER_VERSION);
    dump_command_line_parameters(argc, argv);
    /*
     * we try to catch as many error conditions as possible, but before we call daemon().
     * the exception is the lock file, as we get a new pid when we call daemon(),
     * so this is checked twice: once to read, second to read/write
     */
    if(geteuid() != 0)
    {
        printf("Error: "PTPD_PROGNAME" daemon can only be run as root\n");
        *ret = 1;
        goto fail;
    }

    /* Have we got a config file? */
    if(strlen(rtOpts->configFile) > 0) {
        /* config file settings overwrite all others, except for empty strings */
        INFO("Loading configuration file: %s\n",rtOpts->configFile);
        if(loadConfigFile(&rtOpts->candidateConfig, rtOpts)) {
            dictionary_merge(rtOpts->cliConfig, rtOpts->candidateConfig, 1, "from command line");
        } else {
            *ret = 1;
            dictionary_merge(rtOpts->cliConfig, rtOpts->candidateConfig, 1, "from command line");
            goto configcheck;
        }
    } else {
        dictionary_merge(rtOpts->cliConfig, rtOpts->candidateConfig, 1, "from command line");
    }
    /**
     * This is where the final checking  of the candidate settings container happens.
     * A dictionary is returned with only the known options, explicitly set to defaults
     * if not present. NULL is returned on any config error - parameters missing, out of range,
     * etc. The getopt loop in loadCommandLineOptions() only sets keys verified here.
     */
    if( ( rtOpts->currentConfig = parseConfig(rtOpts->candidateConfig,rtOpts)) == NULL ) {
        *ret = 1;
        dictionary_del(rtOpts->candidateConfig);
        goto configcheck;
    }

    /* we've been told to print the lock file and exit cleanly */
    if(rtOpts->printLockFile) {
        printf("%s\n", rtOpts->lockFile);
        *ret = 0;
        goto fail;
    }

    /* we don't need the candidate config any more */
    dictionary_del(rtOpts->candidateConfig);

    /* Check network before going into background */
    if(!testInterface(rtOpts->ifaceName, rtOpts)) {
        ERROR("Error: Cannot use %s interface\n",rtOpts->ifaceName);
        *ret = 1;
        goto configcheck;
    }

configcheck:
    /*
     * We've been told to check config only - clean exit before checking locks
     */
    if(rtOpts->checkConfigOnly) {
        if(*ret != 0) {
            printf("Configuration has errors\n");
            *ret = 1;
        }
        else
            printf("Configuration OK\n");
        return 0;
    }

    /* Previous errors - exit */
    if(*ret !=0)
        return 0;

    /* First lock check, just to be user-friendly to the operator */
    if(!rtOpts->ignore_daemon_lock) {
        if(!writeLockFile(rtOpts)) {
            /* check and create Lock */
            ERROR("Error: file lock failed (use -L or global:ignore_lock to ignore lock file)\n");
            *ret = 3;
            return 0;
        }
        /* check for potential conflicts when automatic lock files are used */
        if(!checkOtherLocks(rtOpts)) {
            *ret = 3;
            return 0;
        }
    }

    /* Manage log files: stats, log, status and quality file */
    restartLogging(rtOpts);

    /* Allocate memory after we're done with other checks but before going into daemon */
    ptpClock = (PtpClock *) calloc(1, sizeof(PtpClock));
    if (!ptpClock) {
        PERROR("Error: Failed to allocate memory for protocol engine data");
        *ret = 2;
        return 0;
    } else {
        DBG("allocated %d bytes for protocol engine data\n",
            (int)sizeof(PtpClock));
        ptpClock->foreign = (ForeignMasterRecord *)
                            calloc(rtOpts->max_foreign_records,
                                   sizeof(ForeignMasterRecord));
        if (!ptpClock->foreign) {
            PERROR("failed to allocate memory for foreign "
                   "master data");
            *ret = 2;
            free(ptpClock);
            return 0;
        } else {
            DBG("allocated %d bytes for foreign master data\n",
                (int)(rtOpts->max_foreign_records *
                      sizeof(ForeignMasterRecord)));
        }

        ptpClock->owd_filt = FilterCreate(FILTER_EXPONENTIAL_SMOOTH, "owd");
        ptpClock->ofm_filt = FilterCreate(FILTER_MOVING_AVERAGE, "ofm");
    }

    if(rtOpts->statisticsLog.logEnabled)
        ptpClock->resetStatisticsLog = TRUE;

    /* Init to 0 net buffer */
    memset(ptpClock->msgIbuf, 0, PACKET_SIZE);
    memset(ptpClock->msgObuf, 0, PACKET_SIZE);

    /* Init user_description */
    memset(ptpClock->user_description, 0, sizeof(ptpClock->user_description));
    memcpy(ptpClock->user_description, &USER_DESCRIPTION, sizeof(USER_DESCRIPTION));

    /* Init outgoing management message */
    ptpClock->outgoingManageTmp.tlv = NULL;


    /*  DAEMON */
#ifdef PTPD_NO_DAEMON
    if(!rtOpts->nonDaemon) {
        rtOpts->nonDaemon=TRUE;
    }
#endif

    if(!rtOpts->nonDaemon) {
        /*
         * fork to daemon - nochdir non-zero to preserve the working directory:
         * allows relative paths to be used for log files, config files etc.
         * Always redirect stdout/err to /dev/null
         */
        if (daemon(1,0) == -1) {
            PERROR("Failed to start as daemon");
            *ret = 3;
            return 0;
        }
        INFO("  Info:    Now running as a daemon\n");
        /*
         * Wait for the parent process to terminate, but not forever.
         * On some systems this happened after we tried re-acquiring
         * the lock, so the lock would fail. Hence, we wait.
         */
        for (i = 0; i < 1000000; i++) {
            /* Once we've been reaped by init, parent PID will be 1 */
            if(getppid() == 1)
                break;
            usleep(1);
        }
    }

    /* Second lock check, to replace the contents with our own new PID and re-acquire the advisory lock */
    if(!rtOpts->nonDaemon && !rtOpts->ignore_daemon_lock) {
        /* check and create Lock */
        if(!writeLockFile(rtOpts)) {
            ERROR("Error: file lock failed (use -L or global:ignore_lock to ignore lock file)\n");
            *ret = 3;
            return 0;
        }
    }

#if defined(linux) && defined(HAVE_SCHED_H)
    /* Try binding to a single CPU core if configured to do so */

    if(rtOpts->cpuNumber > -1) {

        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(rtOpts->cpuNumber,&mask);
        if(sched_setaffinity(0, sizeof(mask), &mask) < 0) {
            PERROR("Could not bind to CPU core %d", rtOpts->cpuNumber);
        } else {
            INFO("Successfully bound "PTPD_PROGNAME" to CPU core %d\n", rtOpts->cpuNumber);
        }
    }
#endif /* linux && HAVE_SCHED_H */

#ifdef HAVE_SYS_CPUSET_H

    /* Try binding to a single CPU core if configured to do so */

    if(rtOpts->cpuNumber > -1) {
        cpuset_t mask;
        CPU_ZERO(&mask);
        CPU_SET(rtOpts->cpuNumber,&mask);
        if(cpuset_setaffinity(CPU_LEVEL_WHICH, CPU_WHICH_PID,
                              -1, sizeof(mask), &mask) < 0) {
            PERROR("Could not bind to CPU core %d",
                   rtOpts->cpuNumber);
        } else {
            INFO("Successfully bound "PTPD_PROGNAME" to CPU core %d\n",
                 rtOpts->cpuNumber);
        }
    }
#endif /* HAVE_SYS_CPUSET_H */

    /* use new synchronous signal handlers */
    signal(SIGINT,  catchSignals);
    signal(SIGTERM, catchSignals);
    signal(SIGHUP,  catchSignals);

    signal(SIGUSR1, catchSignals);
    signal(SIGUSR2, catchSignals);

#if defined PTPD_SNMP
    /* Start SNMP subsystem */
    if (rtOpts->snmp_enabled)
        snmpInit(rtOpts, ptpClock);
#endif



    NOTICE(USER_DESCRIPTION" started successfully on %s using \"%s\" preset (PID %d)\n",
           rtOpts->ifaceName,
           (getPtpPreset(rtOpts->selectedPreset,rtOpts)).presetName,
           getpid());
    ptpClock->resetStatisticsLog = TRUE;

#ifdef PTPD_STATISTICS
    if (rtOpts->delayMSOutlierFilterEnabled) {
        ptpClock->delayMSRawStats = createDoubleMovingStdDev(rtOpts->delayMSOutlierFilterCapacity);
        strncpy(ptpClock->delayMSRawStats->identifier, "delayMS", 10);
        ptpClock->delayMSFiltered = createDoubleMovingMean(rtOpts->delayMSOutlierFilterCapacity);
    } else {
        ptpClock->delayMSRawStats = NULL;
        ptpClock->delayMSFiltered = NULL;
    }

    if (rtOpts->delaySMOutlierFilterEnabled) {
        ptpClock->delaySMRawStats = createDoubleMovingStdDev(rtOpts->delaySMOutlierFilterCapacity);
        strncpy(ptpClock->delaySMRawStats->identifier, "delaySM", 10);
        ptpClock->delaySMFiltered = createDoubleMovingMean(rtOpts->delaySMOutlierFilterCapacity);
    } else {
        ptpClock->delaySMRawStats = NULL;
        ptpClock->delaySMFiltered = NULL;
    }
#endif

    *ret = 0;
    return ptpClock;

fail:
    dictionary_del(rtOpts->candidateConfig);
    return 0;
}