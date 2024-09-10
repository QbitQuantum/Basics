static
DWORD
ParseJoinArgs(
    IN int argc,
    IN const char *argv[],
    OUT PJOIN_ARGS pArgs
    )
{
    DWORD dwError = 0;
    PCSTR programName = NULL;
    PCSTR option = NULL;
    LW_ARGV_CURSOR cursor;
    SHOW_USAGE_CALLBACK ShowUsageHelp = ShowJoinUsageHelp;
    SHOW_USAGE_CALLBACK ShowUsageError = ShowJoinUsageError;

    memset(pArgs, 0, sizeof(*pArgs));

    LwArgvCursorInit(&cursor, argc, argv);
    programName = LwArgvCursorPop(&cursor);

    // Process options:
    for (;;)
    {
        option = PopNextOption(&cursor);
        if (!option)
        {
            break;
        }
        else if (IsHelpOption(option))
        {
            ShowUsageHelp(programName);
        }
        else if (!strcmp("--name", option))
        {
            dwError = GetOptionValue(programName, ShowUsageError, &cursor, option,
                                     &pArgs->pszMachineName);
            GOTO_CLEANUP_ON_WINERROR(dwError);
        }
        else if (!strcmp("--dnssuffix", option))
        {
            dwError = GetOptionValue(programName, ShowUsageError, &cursor, option,
                                     &pArgs->pszDnsSuffix);
            GOTO_CLEANUP_ON_WINERROR(dwError);
        }
        else if (!strcmp("--ou", option))
        {
            dwError = GetOptionValue(programName, ShowUsageError, &cursor, option,
                                     &pArgs->pszOu);
            GOTO_CLEANUP_ON_WINERROR(dwError);
        }
        else if (!strcmp("--osname", option))
        {
            dwError = GetOptionValue(programName, ShowUsageError, &cursor, option,
                                     &pArgs->pszOsName);
            GOTO_CLEANUP_ON_WINERROR(dwError);
        }
        else if (!strcmp("--osversion", option))
        {
            dwError = GetOptionValue(programName, ShowUsageError, &cursor, option,
                                     &pArgs->pszOsVersion);
            GOTO_CLEANUP_ON_WINERROR(dwError);
        }
        else if (!strcmp("--osservicepack", option))
        {
            dwError = GetOptionValue(programName, ShowUsageError, &cursor, option,
                                     &pArgs->pszOsServicePack);
            GOTO_CLEANUP_ON_WINERROR(dwError);
        }
        else if (!strcmp("--notimesync", option))
        {
            SetFlag(pArgs->JoinFlags, LSA_NET_JOIN_DOMAIN_NOTIMESYNC);
        }
        else if (!strcmp("--multiple", option))
        {
            SetFlag(pArgs->JoinFlags, LSA_NET_JOIN_DOMAIN_NOTIMESYNC);
            SetFlag(pArgs->JoinFlags, LSA_NET_JOIN_DOMAIN_MULTIPLE);
        }
        else
        {
            fprintf(stderr, "Unrecognized option: %s\n", option);
            ShowUsageError(programName);
        }
    }

    // Process arguments:
    dwError = GetArgumentValue(programName, ShowUsageError, &cursor, "DOMAIN",
                               &pArgs->pszDomain);
    GOTO_CLEANUP_ON_WINERROR(dwError);

    LwStrToUpper(pArgs->pszDomain);

    dwError = GetArgumentValue(programName, ShowUsageError, &cursor, "USERNAME",
                               &pArgs->pszUsername);
    GOTO_CLEANUP_ON_WINERROR(dwError);

    // Optional argument
    dwError = GetArgumentValue(programName, ShowUsageError, &cursor, NULL,
                               &pArgs->pszPassword);
    assert(!dwError);

    if (LwArgvCursorRemaining(&cursor))
    {
        fprintf(stderr, "Too many arguments.\n");
        ShowUsageError(programName);
    }

    // Initialize missing options as needed

    if (!pArgs->pszDnsSuffix)
    {
        dwError = LwAllocateString(pArgs->pszDomain, &pArgs->pszDnsSuffix);
        GOTO_CLEANUP_ON_WINERROR(dwError);
    }
    LwStrToLower(pArgs->pszDnsSuffix);

    if (!pArgs->pszMachineName)
    {
        dwError = GetHostname(&pArgs->pszMachineName);
        GOTO_CLEANUP_ON_WINERROR(dwError);
    }

    if (!pArgs->pszOsName ||
        !pArgs->pszOsVersion ||
        !pArgs->pszOsServicePack)
    {
        dwError = GetOsInfo(
                        pArgs->pszOsName ? NULL : &pArgs->pszOsName,
                        pArgs->pszOsVersion ? NULL : &pArgs->pszOsVersion,
                        pArgs->pszOsServicePack ? NULL : &pArgs->pszOsServicePack);
        GOTO_CLEANUP_ON_WINERROR(dwError);
    }

    dwError = CleanupUsername(pArgs->pszDomain, &pArgs->pszUsername);
    GOTO_CLEANUP_ON_WINERROR(dwError);

    if (!pArgs->pszPassword)
    {
        dwError = PromptPassword(pArgs->pszUsername, &pArgs->pszPassword);
        GOTO_CLEANUP_ON_WINERROR(dwError);
    }

cleanup:
    if (dwError)
    {
        FreeJoinArgsContents(pArgs);
    }

    return dwError;
}