int
main(
    int argc,
    char *argv[]
    )
{
    enum
    {
        UNSET,
        SHOW_HELP,
        CHECK_VERSION,
        INSTALL,
        UNINSTALL
    } mode = UNSET;
    PCSTR pSmbdPath = NULL;
    PSTR pFoundSmbdPath = NULL;
    DWORD error = 0;
    DWORD argIndex = 0;
    LW_RTL_LOG_LEVEL logLevel = LW_RTL_LOG_LEVEL_ERROR;
    PCSTR pErrorSymbol = NULL;

    for (argIndex = 1; argIndex < argc; argIndex++)
    {
        if (!strcmp(argv[argIndex], "--check-version"))
        {
            if (mode == UNSET)
            {
                mode = CHECK_VERSION;
            }
            else
            {
                mode = SHOW_HELP;
            }
        }
        else if (!strcmp(argv[argIndex], "--install"))
        {
            if (mode == UNSET)
            {
                mode = INSTALL;
            }
            else
            {
                mode = SHOW_HELP;
            }
        }
        else if (!strcmp(argv[argIndex], "--uninstall"))
        {
            if (mode == UNSET)
            {
                mode = UNINSTALL;
            }
            else
            {
                mode = SHOW_HELP;
            }
        }
        else if (!strcmp(argv[argIndex], "--loglevel"))
        {
            argIndex++;
            if (argIndex >= argc)
            {
                error = ERROR_INVALID_PARAMETER;
                BAIL_ON_LSA_ERROR(error);
            }
            if (!strcmp(argv[argIndex], "error"))
            {
                logLevel = LW_RTL_LOG_LEVEL_ERROR;
            }
            else if (!strcmp(argv[argIndex], "warning"))
            {
                logLevel = LW_RTL_LOG_LEVEL_WARNING;
            }
            else if (!strcmp(argv[argIndex], "info"))
            {
                logLevel = LW_RTL_LOG_LEVEL_INFO;
            }
            else if (!strcmp(argv[argIndex], "verbose"))
            {
                logLevel = LW_RTL_LOG_LEVEL_VERBOSE;
            }
            else if (!strcmp(argv[argIndex], "debug"))
            {
                logLevel = LW_RTL_LOG_LEVEL_DEBUG;
            }
            else
            {
                error = ERROR_INVALID_PARAMETER;
                BAIL_ON_LSA_ERROR(error);
            }
        }
        else if (argIndex == argc - 1)
        {
            pSmbdPath = argv[2];
        }
        else
        {
            mode = SHOW_HELP;
        }
    }

    if (mode == UNSET || mode == SHOW_HELP)
    {
        ShowUsage(argv[0]);
        goto cleanup;
    }

    LwRtlLogSetCallback(LogCallback, NULL);
    LwRtlLogSetLevel(logLevel);

    if (pSmbdPath == NULL)
    {
        error = FindFileInPath(
                        "smbd",
                        "/usr/sbin",
                        &pFoundSmbdPath);
        BAIL_ON_LSA_ERROR(error);
        pSmbdPath = pFoundSmbdPath;
    }

    error = CheckSambaVersion(pSmbdPath);
    BAIL_ON_LSA_ERROR(error);

    if (mode == CHECK_VERSION)
    {
        fprintf(stderr, "Samba version supported\n");
    }
    else if (mode == INSTALL)
    {
        error = InstallWbclient(pSmbdPath);
        BAIL_ON_LSA_ERROR(error);

        error = InstallLwiCompat(pSmbdPath);
        BAIL_ON_LSA_ERROR(error);

        error = SynchronizePassword(
                    pSmbdPath);
        BAIL_ON_LSA_ERROR(error);

        fprintf(stderr, "Install successful\n");
    }
    else if (mode == UNINSTALL)
    {
        error = UninstallWbclient(pSmbdPath);
        BAIL_ON_LSA_ERROR(error);

        error = UninstallLwiCompat(pSmbdPath);
        BAIL_ON_LSA_ERROR(error);

        error = DeletePassword(
                    pSmbdPath);
        BAIL_ON_LSA_ERROR(error);

        fprintf(stderr, "Uninstall successful\n");
    }
    else
    {
        fprintf(stderr, "Uninstall mode not implemented\n");
        error = ERROR_INVALID_PARAMETER;
        BAIL_ON_LSA_ERROR(error);
    }

cleanup:
    LW_SAFE_FREE_STRING(pFoundSmbdPath);

    if (error)
    {
        pErrorSymbol = LwWin32ErrorToName(error);
        if (pErrorSymbol != NULL)
        {
            fprintf(stderr, "Error: %s\n", pErrorSymbol);
        }
        else
        {
            fprintf(stderr, "Unknown error\n");
        }
    }
    return error;
}