VOID
ExamineKey(
    IN  HKEY    PredefinedKey,
    IN  LPCWSTR ParentName,
    IN  LPCWSTR KeyName,
    IN  LPCWSTR PredefinedKeyName
    )

{
    LPWSTR      CompleteKeyName;

    HKEY        Key;

    LONG        Status;

    WCHAR       szClass[ MAX_PATH + 1 ];
    DWORD       cchClass;
    DWORD       cSubKeys;
    DWORD       cchMaxSubKey;
    DWORD       cchMaxClass;
    DWORD       cValues;
    DWORD       cchMaxValueName;
    DWORD       cbMaxValueData;
    DWORD       cbSecurityDescriptor;
    FILETIME    ftLastWriteTime;

    WCHAR       szSubKeyName[ MAX_PATH + 1 ];
    DWORD       cchSubKeyNameLength;

    DWORD       iSubKey;
    BOOLEAN     KeyNameAlreadyPrinted;


    //
    //  Build the complete key name
    //

    if( wcslen( ParentName ) == 0 ) {
        CompleteKeyName = wcsdup( KeyName );
        if( CompleteKeyName == NULL ) {
            printf( "ERROR: wcsdup( KeyName ) failed \n" );
            return;
        }
    } else {
        CompleteKeyName = wcsdup( ParentName );
        if( CompleteKeyName == NULL ) {
            printf( "ERROR: wcsdup( ParentName ) failed \n" );
            return;
        }
        if( wcslen( KeyName ) != 0 ) {
            CompleteKeyName = realloc( CompleteKeyName,
                                       ( wcslen( CompleteKeyName ) +
                                         wcslen( L"\\" ) +
                                         wcslen( KeyName ) + 1 )*sizeof( WCHAR ) );
            wcscat( CompleteKeyName, L"\\" );
            wcscat( CompleteKeyName, KeyName );
        }
    }

//
//  For debugging only
//
//    printf( "%ls\\%ls \n", PredefinedKeyName, CompleteKeyName );
//

    //
    //  Open the key
    //

    Status = RegOpenKeyExW( PredefinedKey,
                           CompleteKeyName,
                           0,
                           MAXIMUM_ALLOWED,
                           &Key );


    if( Status != ERROR_SUCCESS ) {
        printf( MSG_COMPLETE_KEY_NAME, PredefinedKeyName, CompleteKeyName );
        printf( MSG_ERROR_REG_OPEN_KEY_EX, Status );
        free( CompleteKeyName );
        return;
    }

    //
    //  Determine the number of value entries, the maximum length of a value
    //  entry name, the maximum data size, and the number of subkeys
    //

    cchClass = sizeof( szClass ) / sizeof( WCHAR );
    Status = RegQueryInfoKeyW( Key,
                               szClass,
                               &cchClass,
                               0,
                               &cSubKeys,
                               &cchMaxSubKey,
                               &cchMaxClass,
                               &cValues,
                               &cchMaxValueName,
                               &cbMaxValueData,
                               &cbSecurityDescriptor,
                               &ftLastWriteTime );

    if( Status != ERROR_SUCCESS ) {
        printf( MSG_COMPLETE_KEY_NAME, PredefinedKeyName, CompleteKeyName );
        printf( MSG_ERROR_REG_QUERY_INFO_KEY, Status );
        free( CompleteKeyName );
        RegCloseKey( Key );
        return;
    }


    if( cValues != 0 ) {

        //
        // Examine the value entries
        //

        ExamineValueEntries( Key,
                            CompleteKeyName,
                            cchMaxValueName,
                            cbMaxValueData,
                            cValues,
                            PredefinedKeyName );

    }

    //
    //  Traverse each subkey
    //
    if( cSubKeys != 0 ) {
        KeyNameAlreadyPrinted = FALSE;
        for( iSubKey = 0; iSubKey < cSubKeys; iSubKey++ ) {
            cchSubKeyNameLength = sizeof( szSubKeyName )/sizeof( WCHAR );
            cchClass = sizeof( szClass ) / sizeof( WCHAR );
            Status = RegEnumKeyExW( Key,
                                    iSubKey,
                                    szSubKeyName,
                                    &cchSubKeyNameLength,
                                    0,
                                    NULL,
                                    NULL,
                                    &ftLastWriteTime );

            if( Status != ERROR_SUCCESS ) {
                if( !KeyNameAlreadyPrinted ) {
                    KeyNameAlreadyPrinted = TRUE;
                    printf( MSG_COMPLETE_KEY_NAME, PredefinedKeyName, CompleteKeyName );
                }
                printf( MSG_ERROR_REG_ENUM_KEY_EX, Status, iSubKey );
                continue;
            }
            ExamineKey( PredefinedKey,
                        CompleteKeyName,
                        szSubKeyName,
                        PredefinedKeyName );
        }
    }
    RegCloseKey( Key );

    free( CompleteKeyName );
}