INT cmdStop(INT argc, WCHAR **argv)
{
    SC_HANDLE hManager = NULL;
    SC_HANDLE hService = NULL;
    SERVICE_STATUS ServiceStatus;
    DWORD dwError = ERROR_SUCCESS;
    INT nError = 0;
    INT i;

    if (argc != 3)
    {
        ConResPuts(StdOut, IDS_GENERIC_SYNTAX);
        ConResPuts(StdOut, IDS_STOP_SYNTAX);
        return 1;
    }

    for (i = 2; i < argc; i++)
    {
        if (_wcsicmp(argv[i], L"/help") == 0)
        {
            ConResPuts(StdOut, IDS_GENERIC_SYNTAX);
            ConResPuts(StdOut, IDS_STOP_SYNTAX);
            ConResPuts(StdOut, IDS_STOP_HELP_1);
            ConResPuts(StdOut, IDS_STOP_HELP_2);
            ConResPuts(StdOut, IDS_STOP_HELP_3);
            return 1;
        }
    }

    hManager = OpenSCManagerW(NULL,
                              SERVICES_ACTIVE_DATABASE,
                              SC_MANAGER_ENUMERATE_SERVICE);
    if (hManager == NULL)
    {
        dwError = GetLastError();
        nError = 1;
        goto done;
    }

    hService = OpenServiceW(hManager,
                            argv[2],
                            SERVICE_STOP);
    if (hService == NULL)
    {
        dwError = GetLastError();
        nError = 1;
        goto done;
    }

    if (!ControlService(hService, SERVICE_CONTROL_STOP, &ServiceStatus))
    {
        dwError = GetLastError();
        nError = 1;
        goto done;
    }

done:
    if (hService != NULL)
        CloseServiceHandle(hService);

    if (hManager != NULL)
        CloseServiceHandle(hManager);

    if (dwError != ERROR_SUCCESS)
    {
        /* FIXME: Print proper error message */
        ConPrintf(StdErr, L"Error: %lu\n", dwError);
    }

    return nError;
}