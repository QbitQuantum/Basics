// Get an unsigned numeric value.  Return ERROR_INVALID_DATA if value isn't
// numeric.
NET_API_STATUS
NetpGetConfigDword(
    IN LPNET_CONFIG_HANDLE ConfigHandle,
    IN LPTSTR KeyWanted,
    IN DWORD DefaultValue,
    OUT LPDWORD ValueBuffer
    )

/*++

Routine Description:

    This function gets the keyword value from the configuration file.
    This value is converted from a string to a DWORD (unsigned).

Arguments:

    SectionPointer - Supplies the pointer to a specific section in the config
        file.

    KeyWanted - Supplies the string of the keyword within the specified
        section to look for.

    DefaultValue - Gives a default value to use if KeyWanted isn't present
        in the section or if KeyWanted exists but no value is in the config
        data.

    ValueBuffer - Returns the numeric value of the keyword.

Return Value:

    NET_API_STATUS - NERR_Success, ERROR_INVALID_DATA (if string wasn't a
    valid unsigned number), or other error code.

--*/

{
    NET_API_STATUS ApiStatus;
    DWORD CharCount;                 // Count of TCHARs, not including null.
    DWORD TempDword = DefaultValue;
    LPTSTR ValueString;

    //
    // Error check the caller somewhat.
    //
    if (ValueBuffer == NULL) {
        return (ERROR_INVALID_PARAMETER);
    }

    //
    // Check for GP fault and set default value.
    //
    *ValueBuffer = DefaultValue;

    if (ConfigHandle == NULL) {
        return (ERROR_INVALID_PARAMETER);
    }

#if defined(USE_WIN32_CONFIG)
    {
        DWORD dwType;
        LONG Error;
        NET_CONFIG_HANDLE * MyHandle = ConfigHandle;  // conv from opaque type
        DWORD ValueLength;

        // Find out what max value length is.
        ApiStatus = NetpGetConfigMaxSizes (
                MyHandle,
                NULL,  // Don't need max keyword size.
                & ValueLength);  // Get max value length.
        NetpAssert( ApiStatus == NO_ERROR );  // BUGBUG

        // Handle empty section.
        if (ValueLength == 0 ) {
            return (NO_ERROR);  // Default already set, so we're done.  Ok!
        }

        // Alloc space for the value.
        ValueString = NetpMemoryAllocate( ValueLength );
        if (ValueString == NULL) {
            return (ERROR_NOT_ENOUGH_MEMORY);
        }

        // Get the actual value.
        Error = RegQueryValueEx (
                MyHandle->WinRegKey,
                KeyWanted,
                NULL,      // reserved
                & dwType,
                (LPVOID) ValueString,    // out: value string (TCHARs).
                & ValueLength
                );
        IF_DEBUG(CONFIG) {
            NetpKdPrint(( PREFIX_NETLIB "NetpGetConfigDword: RegQueryValueEx("
                    FORMAT_LPTSTR ") returned " FORMAT_LONG ".\n",
                    KeyWanted, Error ));
        }
        if (Error == ERROR_FILE_NOT_FOUND) {
            NetpMemoryFree( ValueString );
            return (NO_ERROR);  // Default already set, so we're done.  Ok!
        } else if ( Error != ERROR_SUCCESS ) {
            NetpMemoryFree( ValueString );
            return (Error);
        }

        NetpAssert( ValueString != NULL );
        if (dwType == REG_SZ) {

            goto ParseString;   // Type is good, go parse the string.

        } else if (dwType == REG_DWORD) {

            NetpAssert( ValueLength == sizeof(DWORD) );
            TempDword = * (LPDWORD) (LPVOID) ValueString;
            goto GotValue;

        } else {
            NetpMemoryFree( ValueString );
            IF_DEBUG(CONFIG) {
                NetpKdPrint(( PREFIX_NETLIB
                        "NetpGetConfigDword: read unexpected reg type "
                        FORMAT_DWORD ".\n", dwType ));
            }
            return (ERROR_INVALID_DATA);
        }

    }

#else // ndef USE_WIN32_CONFIG

    //
    // Get a copy of the string from the config data.
    //

    ApiStatus = NetpGetConfigValue(
            ConfigHandle,
            KeyWanted,
            & ValueString );         // Must be freed by NetApiBufferFree().
    if (ApiStatus != NO_ERROR) {

        //
        // If KeyWanted isn't in config data, return default (and NO_ERROR).
        //
        if (ApiStatus == NERR_CfgParamNotFound) {
            NetpAssert( *ValueBuffer == DefaultValue );  // Already set.
            ApiStatus = NO_ERROR;
        }
        return (ApiStatus);
    }
#endif

    NetpAssert( ValueString != NULL );

ParseString:

    //
    // Do some error checking on the value string.
    //

    CharCount = STRLEN( ValueString );

    if ( CharCount == 0 ) {

        //
        // If "key=" line exists (but no value), return default and say
        // NO_ERROR.
        //
        ApiStatus = NO_ERROR;

    } else if ( _wcsnicmp( ValueString, L"0x", 2 ) == 0 ) {
        LPWSTR end;

        TempDword = wcstoul( ValueString, &end, 16 );

        if ( end - ValueString == (ptrdiff_t) CharCount ) {
            ApiStatus = NO_ERROR;
        } else {
            NetpKdPrint(( PREFIX_NETLIB
                    "NetpGetConfigDword: invalid string for keyword "
                    FORMAT_LPTSTR " is '" FORMAT_LPTSTR "'...\n",
                    KeyWanted, ValueString ));

            ApiStatus = ERROR_INVALID_DATA;
        }

    } else if ( STRSPN( ValueString, TEXT("0123456789") ) != CharCount ) {

        NetpKdPrint(( PREFIX_NETLIB
                "NetpGetConfigDword: invalid string for keyword "
                FORMAT_LPTSTR " is '" FORMAT_LPTSTR "'...\n",
                KeyWanted, ValueString ));

        ApiStatus = ERROR_INVALID_DATA;

    } else {

        //
        // Convert the string to a numeric value.
        //
        TempDword = (DWORD) ATOL( ValueString );

        ApiStatus = NO_ERROR;

    }

    IF_DEBUG(CONFIG) {
        NetpKdPrint(( PREFIX_NETLIB "NetpGetConfigDword: string for "
                FORMAT_LPTSTR " is '" FORMAT_LPTSTR "'...\n",
                KeyWanted, ValueString));
    }

GotValue:

    IF_DEBUG(CONFIG) {
        NetpKdPrint(( PREFIX_NETLIB "NetpGetConfigDword: numeric value is "
                FORMAT_DWORD ",\n", TempDword ));
        NetpKdPrint(("  returning ApiStatus " FORMAT_API_STATUS ".\n",
                ApiStatus ));
    }

    (void) NetApiBufferFree( ValueString );

    //
    // Tell caller how things went.
    //
    * ValueBuffer = TempDword;
    return (ApiStatus);
}