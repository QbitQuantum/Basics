void DisplayClsidKeys(
    CLSID_INFO * ClsidInfo )
{
    HKEY                    hProgId;
    HKEY                    hClsid;
    HKEY                    hProgIdClsid;
    HKEY                    hKey;
    DWORD                   RegStatus;
    DWORD                   RegType;
    DWORD                   BufSize;
    char                    ProgIdClsid[64];
    char                    Value[128];
    int                     Key;
    BOOL                    HasRunAs;
    char                    Password[64];
    LSA_HANDLE              hPolicy;
    LSA_OBJECT_ATTRIBUTES   ObjAttributes;
    LSA_UNICODE_STRING      LsaKey;
    LSA_UNICODE_STRING *    LsaData;
    WCHAR                   wszKey[64];
    WCHAR                   wszPassword[64];
    NTSTATUS                NtStatus;

    RegStatus = RegOpenKeyEx(
                    HKEY_CLASSES_ROOT,
                    "CLSID",
                    0,
                    KEY_READ,
                    &hRegClsid );

    if ( RegStatus != ERROR_SUCCESS )
    {
        printf( "Could not open HKEY_CLASSES_ROOT\\CLSID for reading.\n" );
        return;
    }

    if ( ClsidInfo->ProgId )
    {
        RegStatus = RegOpenKeyEx(
                        HKEY_CLASSES_ROOT,
                        ClsidInfo->ProgId,
                        0,
                        KEY_READ,
                        &hProgId );

        if ( RegStatus != ERROR_SUCCESS )
        {
            printf( "Couldn't open ProgID %s\n", ClsidInfo->ProgId );
            return;
        }

        RegStatus = RegOpenKeyEx(
                        hProgId,
                        "CLSID",
                        0,
                        KEY_READ,
                        &hProgIdClsid );

        if ( RegStatus != ERROR_SUCCESS )
        {
            printf( "Couldn't open CLSID key for ProgID %s\n", ClsidInfo->ProgId );
            return;
        }

        BufSize = sizeof(ProgIdClsid);

        RegStatus = RegQueryValueEx(
                        hProgIdClsid,
                        NULL,
                        0,
                        &RegType,
                        (LPBYTE) ProgIdClsid,
                        &BufSize );

        if ( RegStatus != ERROR_SUCCESS )
        {
            printf( "Couldn't open CLSID value for ProgID %s\n", ClsidInfo->ProgId );
            return;
        }

        if ( ClsidInfo->Clsid &&
             (_stricmp( ClsidInfo->Clsid, ProgIdClsid ) != 0) )
        {
            printf( "ProgID %s CLSID key value %s differs from given CLSID %s.\n",
                    ClsidInfo->ProgId,
                    ProgIdClsid,
                    ClsidInfo->Clsid );
            return;
        }
        else
            ClsidInfo->Clsid = ProgIdClsid;
    }


    if ( ! ClsidInfo->Clsid )
    {
        printf( "Could not determine CLSID.\n" );
        return;
    }

    RegStatus = RegOpenKeyEx(
                    hRegClsid,
                    ClsidInfo->Clsid,
                    0,
                    KEY_READ,
                    &hClsid );

    if ( RegStatus != ERROR_SUCCESS )
    {
        printf( "Could not open CLSID %s\n", ClsidInfo->Clsid );
        return;
    }

    putchar( '\n' );
    if ( ClsidInfo->ProgId )
        printf( "Server settings for ProgID %s, ", ClsidInfo->ProgId );
    else
        printf( "Server settings for " );

    printf( "CLSID %s\n", ClsidInfo->Clsid );

    HasRunAs = FALSE;

    for ( Key = 1; Key <= CLSID_KEYS; Key++ )
    {
        RegStatus = RegOpenKeyEx(
                        hClsid,
                        ClsidKeyNames[Key],
                        0,
                        KEY_READ,
                        &hKey );

        if ( RegStatus != ERROR_SUCCESS )
            continue;

        BufSize = sizeof(Value);

        if ( Key != ACCESS_PERMISSION )
        {
            RegStatus = RegQueryValueEx(
                            hKey,
                            NULL,
                            0,
                            &RegType,
                            (LPBYTE) Value,
                            &BufSize );
        }
        else
            RegStatus = ERROR_SUCCESS;

        if ( RegStatus != ERROR_SUCCESS )
        {
            printf( "    %-28s(key exists, but value could not be read)\n",
                    ClsidKeyNames[Key] );
            continue;
        }

        printf( "    %-28s%s\n",
                ClsidKeyNames[Key],
                (Key == ACCESS_PERMISSION) ? "on" : Value );

        if ( (Key == RUN_AS) && (_stricmp(Value,"Interactive User") != 0) )
            HasRunAs = TRUE;
    }

    if ( ! HasRunAs )
        return;

    //
    // Give the option of verifying the RunAs password.
    //

    printf( "\nCLSID configured with RunAs.  Would you like to verify the password? " );

    if ( (char)CharUpper((LPSTR)getchar()) != 'Y' )
        return;

    while ( getchar() != '\n' )
        ;

    putchar( '\n' );

    lstrcpyW( wszKey, L"SCM:" );
    MultiByteToWideChar( CP_ACP,
                         MB_PRECOMPOSED,
                         ClsidInfo->Clsid,
                         -1,
                         &wszKey[lstrlenW(wszKey)],
                         sizeof(wszKey)/2 - lstrlenW(wszKey) );

    LsaKey.Length = (lstrlenW(wszKey) + 1) * sizeof(WCHAR);
    LsaKey.MaximumLength = sizeof(wszKey);
    LsaKey.Buffer = wszKey;

    InitializeObjectAttributes( &ObjAttributes, NULL, 0L, NULL, NULL );

    // Open the local security policy
    NtStatus = LsaOpenPolicy( NULL,
                              &ObjAttributes,
                              POLICY_CREATE_SECRET,
                              &hPolicy );

    if ( ! NT_SUCCESS( NtStatus ) )
    {
        printf( "Could not open RunAs password (0x%x)\n", NtStatus );
        return;
    }

    // Retrive private data
    NtStatus = LsaRetrievePrivateData( hPolicy, &LsaKey, &LsaData );

    if ( ! NT_SUCCESS(NtStatus) )
    {
        printf( "Could not open RunAs password (0x%x)\n", NtStatus );
        return;
    }

    LsaClose(hPolicy);

    for (;;)
    {
        printf( "Password : "******"dcom4ever" ) == 0 )
        {
            printf( "\nThe RunAs password is %ws\n", LsaData->Buffer );
            return;
        }

        MultiByteToWideChar( CP_ACP,
                             MB_PRECOMPOSED,
                             Password,
                             -1,
                             wszPassword,
                             sizeof(wszPassword) );

        if ( lstrcmpW( wszPassword, LsaData->Buffer ) != 0 )
        {
            printf( "\nPassword does not match RunAs password.\n" );
            printf( "Enter another password or hit Control-C to exit.\n\n" );
        }
        else
        {
            printf( "\nPasswords match.\n" );
            return;
        }
    }
}