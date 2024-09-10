/* Start the service argv[2] */
static
INT
StartOneService(INT argc, WCHAR **argv)
{
    SC_HANDLE hManager = NULL;
    SC_HANDLE hService = NULL;
    LPCWSTR *lpArgVectors = NULL;
    DWORD dwError = ERROR_SUCCESS;
    INT nError = 0;
    INT i;

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
                            SERVICE_START);
    if (hService == NULL)
    {
        dwError = GetLastError();
        nError = 1;
        goto done;
    }

    lpArgVectors = HeapAlloc(GetProcessHeap(),
                             0,
                             (argc - 2) * sizeof(LPCWSTR));
    if (lpArgVectors == NULL)
    {
        dwError = GetLastError();
        nError = 1;
        goto done;
    }

    for (i = 2; i < argc; i++)
    {
        lpArgVectors[i - 2] = argv[i];
    }

    if (!StartServiceW(hService,
                       (DWORD)argc - 2,
                       lpArgVectors))
    {
        dwError = GetLastError();
        nError = 1;
    }

done:
    if (lpArgVectors != NULL)
        HeapFree(GetProcessHeap(), 0, (LPVOID)lpArgVectors);

    if (hService != NULL)
        CloseServiceHandle(hService);

    if (hManager != NULL)
        CloseServiceHandle(hManager);

    if (dwError != ERROR_SUCCESS)
    {
        /* FIXME: Print proper error message */
        printf("Error: %lu\n", dwError);
    }

    return nError;
}