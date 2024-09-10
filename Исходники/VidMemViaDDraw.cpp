HRESULT GetDeviceIDFromHMonitor( HMONITOR hm, WCHAR* strDeviceID, int cchDeviceID )
{

    HINSTANCE hInstDDraw;

    hInstDDraw = LoadLibrary( L"ddraw.dll" );
    if( hInstDDraw )
    {
        DDRAW_MATCH match = {};
        match.hMonitor = hm;

        LPDIRECTDRAWENUMERATEEXA pDirectDrawEnumerateEx = nullptr;
        pDirectDrawEnumerateEx = ( LPDIRECTDRAWENUMERATEEXA )GetProcAddress( hInstDDraw, "DirectDrawEnumerateExA" );

        if( pDirectDrawEnumerateEx )
            pDirectDrawEnumerateEx( DDEnumCallbackEx, ( VOID* )&match, DDENUM_ATTACHEDSECONDARYDEVICES );

        if( match.bFound )
        {
            LONG iDevice = 0;
            DISPLAY_DEVICEA dispdev = {};
            dispdev.cb = sizeof( dispdev );

            while( EnumDisplayDevicesA( nullptr, iDevice, ( DISPLAY_DEVICEA* )&dispdev, 0 ) )
            {
                // Skip devices that are monitors that echo another display
                if( dispdev.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER )
                {
                    iDevice++;
                    continue;
                }

                // Skip devices that aren't attached since they cause problems
                if( ( dispdev.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP ) == 0 )
                {
                    iDevice++;
                    continue;
                }

                if( _stricmp( match.strDriverName, dispdev.DeviceName ) == 0 )
                {
                    MultiByteToWideChar( CP_ACP, 0, dispdev.DeviceID, -1, strDeviceID, cchDeviceID );
                    return S_OK;
                }

                iDevice++;
            }
        }

        FreeLibrary( hInstDDraw );
    }

    return E_FAIL;
}