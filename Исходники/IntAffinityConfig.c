BOOL GetFilterAffinityMask( HDEVINFO hDevInfo,
                            PSP_DEVINFO_DATA pDevInfoData,
                            DWORD* pAffinityMask )
{
    HKEY  hkeyDeviceParams;
    LONG  lRetVal;
    BOOL  fToReturn = TRUE;  // success
    DWORD regValueType;
    DWORD regValueSize;


    ASSERT( NULL != pAffinityMask );


    //
    // Get a handle to the device's "Device Parameters" registry subkey
    //
    hkeyDeviceParams = SetupDiOpenDevRegKey( hDevInfo,
                                             pDevInfoData,
                                             DICS_FLAG_GLOBAL,  //CPRINCE: SHOULD (CAN?) USE 'DICS_FLAG_CONFIGSPECIFIC' INSTEAD ???
                                             0,
                                             DIREG_DEV,
                                             KEY_QUERY_VALUE  // desired access
                                           );

    if( INVALID_HANDLE_VALUE == hkeyDeviceParams )
    {
        // Probably just means that the "Device Parameters" subkey
        // does not exist, so return, but _don't_ display error message.
        return FALSE;  // failure
    }


    //
    // Get the desired registry value
    //
    regValueSize = sizeof(DWORD);
    lRetVal = RegQueryValueEx( hkeyDeviceParams,
                               FILTER_REGISTRY_VALUE,
                               0,
                               &regValueType,
                               (BYTE*)pAffinityMask,
                               &regValueSize
                             );

    if( ERROR_SUCCESS != lRetVal )
    {
        if( ERROR_FILE_NOT_FOUND == lRetVal )
        {
            // Just means key didn't already exist.
            // So don't display error message.
        }
        else
        {
            //MessageBox_FromErrorCode( lRetVal );
        }
        fToReturn = FALSE; // failure
    }
    else if( REG_DWORD != regValueType )
    {
        
        fToReturn = FALSE;  // failure
    }


    //
    // Close the registry key(s) we opened
    //
    lRetVal = RegCloseKey( hkeyDeviceParams );
    if( ERROR_SUCCESS != lRetVal )
    {
        //MessageBox_FromErrorCode( lRetVal );
        fToReturn = FALSE;  // failure
    }


    return fToReturn;
}