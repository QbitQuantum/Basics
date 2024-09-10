//
// Function: LoadProviderPath
//
// Description:
//      This function retrieves the provider's DLL path, expands any environment
//      variables, loads the DLL, and retrieves it's WSPStartup function.
//
BOOL
LoadProviderPath(
    PROVIDER    *loadProvider,
    int         *lpErrno
    )
{
    int     rc;

    *lpErrno = 0;

    // Retrieve the provider path of the lower layer
    loadProvider->ProviderPathLen = MAX_PATH - 1;
    rc = WSCGetProviderPath(
           &loadProvider->NextProvider.ProviderId,
            loadProvider->ProviderPathW,
           &loadProvider->ProviderPathLen,
            lpErrno
            );
    if ( SOCKET_ERROR == rc )
    {
        dbgprint("LoadProviderPath: WSCGetProviderPath failed: %d", *lpErrno );
        goto cleanup;
    }

    rc = ExpandEnvironmentStringsW(
            loadProvider->ProviderPathW,
            loadProvider->LibraryPathW,
            MAX_PATH - 1
            );
    if ( ( 0 != rc ) && ( MAX_PATH-1 >= rc ) )
    {
        loadProvider->Module = LoadLibraryW( loadProvider->LibraryPathW );
        if ( NULL == loadProvider->Module )
        {
            dbgprint("LoadProviderPath: LoadLibraryW failed: %d", GetLastError() );
            goto cleanup;
        }
    }
    else if ( 0 == rc )
    {
        char    ProviderPathA[ MAX_PATH ],
                LibraryPathA[ MAX_PATH ];

        // No UNICODE so we must be on Win9x
        rc = WideCharToMultiByte( CP_ACP, 0,
                loadProvider->ProviderPathW,
                loadProvider->ProviderPathLen,
                ProviderPathA,
                loadProvider->ProviderPathLen,
                NULL,
                NULL
                );
        if ( 0 == rc )
        {
            dbgprint("LoadProviderPath: WideCharToMultiByte failed: %d", GetLastError() );
            goto cleanup;
        }

        rc = ExpandEnvironmentStringsA(
                ProviderPathA,
                LibraryPathA,
                MAX_PATH - 1
                );
        if ( ( 0 == rc ) || ( MAX_PATH - 1 < rc ) )
        {
            dbgprint("LoadProviderPath: ExpandEnvironmentStringsA failed: %d", GetLastError() );
            goto cleanup;
        }

        loadProvider->Module = LoadLibraryA( LibraryPathA );
        if ( NULL == loadProvider->Module )
        {
            dbgprint("LoadProviderPath: LoadLibraryA failed: %d", GetLastError() );
            goto cleanup;
        }
    }

    // Retrieve the next provider's WSPSTartup function
    loadProvider->fnWSPStartup = (LPWSPSTARTUP) GetProcAddress(
            loadProvider->Module,
            "WSPStartup"
            );
    if ( NULL == loadProvider->fnWSPStartup )
    {
        dbgprint("LoadProviderPath: GetProcAddress failed: %d", GetLastError() );
        goto cleanup;
    }

    return TRUE;

cleanup:

    if ( *lpErrno == 0 )
        *lpErrno = GetLastError();
    return FALSE;
}