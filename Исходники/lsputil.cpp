//
// Function: LoadUpdateProviderFunction
//
// Description:
//      This routine loads the WSCUpdateProvider function from ws2_32.dll.
//      This function is used when removing LSP entries and other LSPs are layered
//      on top of the one to be removed. If this API is present (which it is on
//      Windows XP and later), then the logic is much simpler. This routien will
//      load both the 32-bit and 64-bit versions of the function.
//
HMODULE
LoadUpdateProviderFunction()
{
    HMODULE hModule = NULL;
    HRESULT hr;
    char    WinsockLibraryPath[ MAX_PATH+1 ],
            szExpandPath[ MAX_PATH+1 ];

    //
    // See if we're on a platform that supports WSCUpdateProvider. If so then
    // uninstalling an LSP is easy; otherwise, it is very painful if you're
    // removing an LSP that has other LSPs on top if it.
    //
    if ( GetSystemDirectoryA( WinsockLibraryPath, MAX_PATH+1 ) == 0 )
    {
        hr = StringCchCopyA( szExpandPath, MAX_PATH+1, "%SYSTEMROOT%\\system32" );
        if ( FAILED( hr ) )
        {
            fprintf( stderr, "LoadUpdateProviderFunctions: StringCchCopyA failed: 0x%x\n", hr );
            goto cleanup;
        }

        if ( ExpandEnvironmentStringsA( WinsockLibraryPath, szExpandPath, MAX_PATH+1 ) == 0 )
        {
            fprintf(stderr, "LoadUpdateProviderFunctions: Unable to expand environment string: %d\n", 
                    GetLastError()
                   );
            goto cleanup;
        }
    }

    hr = StringCchCatA( WinsockLibraryPath, MAX_PATH+1, WINSOCK_DLL );
    if ( FAILED( hr ) )
    {
        fprintf( stderr, "LoadUpdateProviderFunctions: StringCchCatA failed: 0x%x\n", hr );
        goto cleanup;
    }

    hModule = LoadLibraryA( WinsockLibraryPath );
    if (hModule == NULL)
    {
        fprintf(stderr, "LoadUpdateProviderFunctions: Unable to load %s: %d\n", 
                WinsockLibraryPath, GetLastError()
                );
        goto cleanup;
    }
#ifdef _WIN64
    fnWscUpdateProvider   = (LPWSCUPDATEPROVIDER)GetProcAddress(hModule, "WSCUpdateProvider");

    fnWscUpdateProvider32 = (LPWSCUPDATEPROVIDER)GetProcAddress(hModule, "WSCUpdateProvider32");
#else
    fnWscUpdateProvider   = (LPWSCUPDATEPROVIDER)GetProcAddress(hModule, "WSCUpdateProvider");
#endif

    return hModule;

cleanup:

    if ( NULL != hModule )
    {
        FreeLibrary( hModule );
        hModule = NULL;
    }

    return NULL;
}