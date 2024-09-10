MAIN(appweb, int argc, char **argv)
{
    Mpr         *mpr;
    MaHttp      *http;
    cchar       *ipAddrPort, *documentRoot, *argp, *logSpec;
    char        *configFile, *ipAddr, *homeDir, *timeText, *ejsPrefix, *ejsPath, *changeRoot;
    int         workers, outputVersion, argind, port;
    
    documentRoot = 0;
    changeRoot = ejsPrefix = ejsPath = 0;
    ipAddrPort = 0;
    ipAddr = 0;
    port = -1;
    logSpec = 0;
    server = 0;
    outputVersion = 0;
    workers = -1;

    configFile = BLD_FEATURE_CONFIG_FILE;
    homeDir = BLD_FEATURE_SERVER_ROOT;

    mpr = mprCreate(argc, argv, memoryFailure);
    argc = mpr->argc;
    argv = mpr->argv;

#if BLD_FEATURE_ROMFS
    extern MprRomInode romFiles[];
    mprSetRomFileSystem(mpr, romFiles);
#endif

    if (osInit(mpr) < 0) {
        exit(2);
    }
    if (mprStart(mpr, 0) < 0) {
        mprUserError(mpr, "Can't start MPR for %s", mprGetAppName(mpr));
        mprFree(mpr);
        return MPR_ERR_CANT_INITIALIZE;
    }

    for (argind = 1; argind < argc; argind++) {
        argp = argv[argind];
        if (*argp != '-') {
            break;
        }
        if (strcmp(argp, "--config") == 0) {
            if (argind >= argc) {
                return printUsage(mpr);
            }
            configFile = argv[++argind];

#if BLD_UNIX_LIKE
        } else if (strcmp(argp, "--chroot") == 0) {
            if (argind >= argc) {
                return printUsage(mpr);
            }
            changeRoot = mprGetAbsPath(mpr, argv[++argind]);
#endif

        } else if (strcmp(argp, "--debug") == 0 || strcmp(argp, "-D") == 0 || 
                strcmp(argp, "-d") == 0 || strcmp(argp, "--debugger") == 0) {
            mprSetDebugMode(mpr, 1);

        } else if (strcmp(argp, "--ejs") == 0) {
            if (argind >= argc) {
                return printUsage(mpr);
            }
            ejsPrefix = mprStrdup(mpr, argv[++argind]);
            if ((ejsPath = strchr(ejsPrefix, ':')) != 0) {
                *ejsPath++ = '\0';
            }
            ejsPath = mprGetAbsPath(mpr, ejsPath);

        } else if (strcmp(argp, "--home") == 0) {
            if (argind >= argc) {
                return printUsage(mpr);
            }
            homeDir = mprGetAbsPath(mpr, argv[++argind]);
            if (chdir((char*) homeDir) < 0) {
                mprPrintfError(mpr, "%s: Can't change directory to %s\n", mprGetAppName(mpr), homeDir);
                exit(2);
            }

        } else if (strcmp(argp, "--log") == 0 || strcmp(argp, "-l") == 0) {
            if (argind >= argc) {
                return printUsage(mpr);
            }
            logSpec = argv[++argind];
            maStartLogging(mpr, logSpec);

        } else if (strcmp(argp, "--name") == 0 || strcmp(argp, "-n") == 0) {
            if (argind >= argc) {
                return printUsage(mpr);
            }
            mprSetAppName(mpr, argv[++argind], 0, 0);

        } else if (strcmp(argp, "--threads") == 0) {
            if (argind >= argc) {
                return printUsage(mpr);
            }
            workers = atoi(argv[++argind]);

        } else if (strcmp(argp, "--verbose") == 0 || strcmp(argp, "-v") == 0) {
            maStartLogging(mpr, "stdout:2");

        } else if (strcmp(argp, "--version") == 0 || strcmp(argp, "-V") == 0) {
            outputVersion++;

        } else {
            mprPrintfError(mpr, "Unknown switch \"%s\"\n", argp);
            printUsage(mpr);
            exit(2);
        }
    }

    if (argc > argind) {
        if (argc > (argind + 2)) {
            return printUsage(mpr);
        }
        ipAddrPort = argv[argind++];
        if (argc > argind) {
            documentRoot = argv[argind++];
        } else {
            documentRoot = ".";
        }
    }

    if (outputVersion) {
        mprPrintf(mpr, "%s %s-%s\n", mprGetAppTitle(mpr), BLD_VERSION, BLD_NUMBER);
        exit(0);
    }

    if (ipAddrPort) {
        mprParseIp(mpr, ipAddrPort, &ipAddr, &port, MA_SERVER_DEFAULT_PORT_NUM);
    } else {
#if BLD_FEATURE_CONFIG_PARSE
        if (configFile == 0) {
            configFile = mprStrcat(mpr, -1, mprGetAppName(mpr), ".conf", NULL);
        }
        if (!mprPathExists(mpr, configFile, R_OK)) {
            mprPrintfError(mpr, "Can't open config file %s\n", configFile);
            exit(2);
        }
#else
        return printUsage(mpr);
#endif
#if !BLD_FEATURE_ROMFS
        if (homeDir == 0) {
            homeDir = mprGetPathParent(mpr, configFile);
            if (chdir((char*) homeDir) < 0) {
                mprPrintfError(mpr, "%s: Can't change directory to %s\n", mprGetAppName(mpr), homeDir);
                exit(2);
            }
        }
#endif
    }
    homeDir = mprGetCurrentPath(mpr);
    if (checkEnvironment(mpr, argv[0], homeDir) < 0) {
        exit(3);
    }

#if BLD_UNIX_LIKE
    if (changeRoot) {
        homeDir = mprGetAbsPath(mpr, changeRoot);
        if (chdir(homeDir) < 0) {
            mprError(mpr, "%s: Can't change directory to %s", homeDir);
            exit(4);
        }
        if (chroot(homeDir) < 0) {
            if (errno == EPERM) {
                mprError(mpr, "%s: Must be super user to use the --chroot option", mprGetAppName(mpr));
            } else {
                mprError(mpr, "%s: Can't change change root directory to %s, errno %d",
                    mprGetAppName(mpr), homeDir, errno);
            }
            exit(5);
        }
    }
#endif

    /*
     *  Create the top level HTTP service and default HTTP server. Set the initial server root to "."
     */
    http = maCreateHttp(mpr);
    if (http == 0) {
        mprUserError(mpr, "Can't create HTTP service for %s", mprGetAppName(mpr));
        return MPR_ERR_CANT_INITIALIZE;
    }
    server = maCreateServer(http, "default", ".", 0, -1);
    if (server == 0) {
        mprUserError(mpr, "Can't create HTTP server for %s", mprGetAppName(mpr));
        return MPR_ERR_CANT_INITIALIZE;
    }
    if (maConfigureServer(mpr, http, server, configFile, ipAddr, port, documentRoot) < 0) {
        /* mprUserError(mpr, "Can't configure the server, exiting."); */
        exit(6);
    }
    if (mpr->ipAddr) {
        mprLog(mpr, 2, "Server IP address %s", mpr->ipAddr);
    }
    timeText = mprFormatLocalTime(mpr, mprGetTime(mpr));
    mprLog(mpr, 1, "Started at %s", timeText);
    mprFree(timeText);

#if BLD_FEATURE_EJS
    if (ejsPrefix) {
        createEjsAlias(mpr, http, server, ejsPrefix, ejsPath);
    }
#endif

#if BLD_FEATURE_MULTITHREAD
    if (workers >= 0) {
        mprSetMaxWorkers(http, workers);
    }
#endif
#if BLD_WIN_LIKE
    if (!ejsPrefix) {
        writePort(server->defaultHost);
    }
#endif

    if (maStartHttp(http) < 0) {
        mprUserError(mpr, "Can't start HTTP service, exiting.");
        exit(7);
    }

#if BLD_FEATURE_MULTITHREAD
    mprLog(mpr, 1, "HTTP services are ready with max %d worker threads", mprGetMaxWorkers(mpr));
#else
    mprLog(mpr, 1, "HTTP services are ready (single-threaded)");
#endif

    /*
     *  Service I/O events until instructed to exit
     */
    while (!mprIsExiting(mpr)) {
        mprServiceEvents(mpr->dispatcher, -1, MPR_SERVICE_EVENTS | MPR_SERVICE_IO);
    }

    /*
     *  Signal a graceful shutdown
     */
    mprLog(http, 1, "Exiting ...");
    maStopHttp(http);
    mprLog(http, 1, "Exit complete");

#if VXWORKS
    if (mprStop(mpr)) {
        mprFree(mpr);
    }
#endif
    return 0;
}