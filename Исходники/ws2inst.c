BOOL
RemoveNameSpaceProviderCallback(
    LPTSTR IniFile,
    LPTSTR SectionName,
    DWORD Context
    )

/*++

Routine Description:

    Callback routine for EnumProviderSections() that removes the
    namespace service provider described by the given .INI file section.

Arguments:

    IniFile - The name of the .INI file describing the namespace provider.

    SectionName - The name of the .INI file section for this provider.

    Context - Actually contains behaviour control options (OPTION_FLAG_*).

Return Value:

    BOOL - TRUE if successful, FALSE otherwise.

--*/

{


    TCHAR providerName[MAX_INIFILE_LINE];
    TCHAR providerIdString[MAX_INIFILE_LINE];
    DWORD length;
    INT result;
    INT error;
    GUID providerId;
    RPC_STATUS status;
    BOOL ignoreErrors;

    //
    // Let the user know what we're up to.
    //

    _tprintf(
        TEXT("Removing %s\n"),
        SectionName
        );

    //
    // Determine if we should ignore errors. If so, then this routine
    // will always return TRUE.
    //

    ignoreErrors = ( ( Context & OPTION_FLAG_IGNORE_ERRORS ) != 0 );

    //
    // Read the provider name & ID.
    //

    length = GetPrivateProfileString(
                 SectionName,
                 TEXT("ProviderName"),
                 TEXT(""),
                 providerName,
                 sizeof(providerName) / sizeof(providerName[0]),
                 IniFile
                 );

    if( length == 0 ) {

        _tprintf(
            TEXT("ERROR: missing ProviderName key\n")
            );

        return ignoreErrors;

    }

    length = GetPrivateProfileString(
                     SectionName,
                     TEXT("ProviderId"),
                     TEXT(""),
                     providerIdString,
                     sizeof(providerIdString) / sizeof(providerIdString[0]),
                     IniFile
                     );

    if( length == 0 ) {

        _tprintf(
            TEXT("ERROR: missing ProviderId key\n")
            );

        return ignoreErrors;

    }

    //
    // Build the GUID.
    //

    status = UuidFromString(
                 providerIdString,
                 &providerId
                 );

    if( status != RPC_S_OK ) {

        _tprintf(
            TEXT("ERROR: invalid ProviderId %s\n"),
            providerIdString
            );

        return ignoreErrors;

    }

    //
    // Remove it.
    //

    result = WSCUnInstallNameSpace(
                 &providerId
                 );

    if( result == SOCKET_ERROR ) {

        error = GetLastError();

        _tprintf(
            TEXT("Cannot remove %s, error %d\n"),
            providerName,
            error
            );

        return ignoreErrors;

    }

    return TRUE;

}   // RemoveNameSpaceProviderCallback