//
// After the adapter parameter is changed, should call this function to active it.
//
BOOL ControlAdapter( DWORD dwStatus, CONST TCHAR* GUIDString) // _T("4D36E972-E325-11CE-BFC1-08002BE10318");
{
    BOOL bRet = FALSE;

    if ( 0 == dwStatus )
    {
        return FALSE;
    }

    //TCHAR* GUIDString = _T("4D36E972-E325-11CE-BFC1-08002BE10318");
    GUID guid;
    ZeroMemory( &guid, sizeof( GUID ) );
    if ( RPC_S_OK != UuidFromString( (unsigned char*)GUIDString, &guid ) )
    {
        bRet = FALSE;
    }
    else
    {
        HDEVINFO hDevInfo = NULL;
        hDevInfo = SetupDiGetClassDevs( &guid, REGSTR_KEY_PCIENUM, NULL, DIGCF_PRESENT );
        if ( INVALID_HANDLE_VALUE == hDevInfo )
        {
            bRet = FALSE;
        }
        else
        {
            DWORD i = 0;
            SP_DEVINFO_DATA DeviceInfoData;
            ZeroMemory( &DeviceInfoData, sizeof( SP_DEVINFO_DATA ) );
            DeviceInfoData.cbSize = sizeof( SP_DEVINFO_DATA );

            for ( i = 0; SetupDiEnumDeviceInfo( hDevInfo, i, &DeviceInfoData ); ++i )
            {
                // 获得设备的状态
                DWORD dwProblem = 0, dwDeviceStatus = 0;
                if ( CR_SUCCESS != CM_Get_DevNode_Status( &dwDeviceStatus, &dwProblem, DeviceInfoData.DevInst, 0 ) )
                {
                    continue;
                }

                // 获取设备注册表项描述
                CString strText;
                if ( !GetDeviceRegistryProperty( hDevInfo, &DeviceInfoData, SPDRP_CLASS, strText ) )
                {
                    continue;
                }

                TRACE( _T("\n The %d device instance handle : %d, Class : %s\n"), i, DeviceInfoData.DevInst, strText );

                if ( 0 == lstrcmp( strText, _T("Net") ) )
                {
                    TRACE( _T("This is the adapter device that I want.\n") );

                    //////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
                    if ( GetDeviceRegistryProperty( hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC, strText ) )
                    {
                        TRACE( _T("SPDRP_DEVICEDESC : %s\n"), strText );
                    }
#endif
                    //////////////////////////////////////////////////////////////////////////

                    if ( ChangeStatus( dwStatus, i, hDevInfo ) )
                    {
                        bRet = TRUE;
                    }
                }
            }

            // 释放 device information set
            bRet = SetupDiDestroyDeviceInfoList( hDevInfo );
        }
    }

    return bRet;
}