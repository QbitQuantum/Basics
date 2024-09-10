void *CVSCPBTDetectWrkTread::Entry()
{
    BLUETOOTH_FIND_RADIO_PARAMS bt_find_radio = {
        sizeof( BLUETOOTH_FIND_RADIO_PARAMS )
    };

    BLUETOOTH_RADIO_INFO bt_info = {
        sizeof( BLUETOOTH_RADIO_INFO ),
        0,
    };

    BLUETOOTH_DEVICE_SEARCH_PARAMS search_params = {
        sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS),
        1,
        0,
        1,
        1,
        1,
        1,  // Timeout
        NULL
    };

    BLUETOOTH_DEVICE_INFO device_info = {
        sizeof( BLUETOOTH_DEVICE_INFO ),
        0,
    };

    HANDLE radio = NULL;
    HBLUETOOTH_RADIO_FIND bt = NULL;
    HBLUETOOTH_DEVICE_FIND bt_dev = NULL;

    // First log on to the host and get configuration 
    // variables
    
    if ( VSCP_ERROR_SUCCESS != m_srv.doCmdOpen( m_pObj->m_host,
                                                    m_pObj->m_username,
                                                    m_pObj->m_password ) ) {
        return NULL;
    }

    // Find the channel id
    uint32_t ChannelID;
    m_srv.doCmdGetChannelID( &ChannelID );

    // It is possible that there is configuration data the server holds 
    // that we need to read in. 
    // We look for 
    //      prefix_period Seconds between scans.
    //      prefix_zone Zone to use for Token Activity
    //      prefix_subzone Subzone to use for Token Activity
    //      prefix_bsendtoken Send Token activity. Class=20 (Information, Type=37 
    //      prefix_bsenddetect Send detect event. Class=20 (Information), Type=49
    //      prefix_detectzone
    //      prefix_detectsubzone
    //
    //      Future defines.
    //      ===============
    //      prefix_onaddresses - List with addresses that will generate on-event
    //      prefix_offaddresses - List with addresses that will generate off-event

    bool bSendTokenActivity = true;     // Sending Token Activity is default behaviour.
    bool bSendDetect = false;           // Sending detect events must be enabled.
    uint16_t pausTime = 1;              // default svan period is one seconds.
    uint8_t zone = 0;                   // Zone for token activity.
    uint8_t subzone = 0;                // Subzone for token activity.
    uint8_t detectIndex = 0;            // Index used for detect event.
    uint8_t detectZone = 0;             // Zone used for detect event.
    uint8_t detectSubzone = 0;          // Subzone used for detect events.
    bool bDisableRadiodetect= false;    // Don't report radio discovery.

    wxString        strAddress;
    _deviceHash     deviceHashPrev;
    _deviceHash     deviceHashNow;
    CDetectedDevice *pDevice;

    int intvalue;
    bool bvalue;
    if ( VSCP_ERROR_SUCCESS == m_srv.getVariableInt( m_pObj->m_prefix + _( "_pausetime" ), &intvalue ) ) {
        if ( intvalue >= 0 ) pausTime = intvalue;
    }

    if ( VSCP_ERROR_SUCCESS == m_srv.getVariableInt( m_pObj->m_prefix + _( "_zone" ), &intvalue ) ) {
        zone = intvalue;
    }

    if ( VSCP_ERROR_SUCCESS == m_srv.getVariableInt( m_pObj->m_prefix + _( "_subzone" ), &intvalue ) ) {
        subzone = intvalue;
    }

    if ( VSCP_ERROR_SUCCESS == m_srv.getVariableInt( m_pObj->m_prefix + _( "_detectindex" ), &intvalue ) ) {
        detectIndex = intvalue;
    }

    if ( VSCP_ERROR_SUCCESS == m_srv.getVariableInt( m_pObj->m_prefix + _( "_detectzone" ), &intvalue ) ) {
        detectZone = intvalue;
    }

    if ( VSCP_ERROR_SUCCESS == m_srv.getVariableInt( m_pObj->m_prefix + _( "_detectsubzone" ), &intvalue ) ) {
        detectSubzone = intvalue;
    }

    if ( VSCP_ERROR_SUCCESS == m_srv.getVariableBool( m_pObj->m_prefix + _( "_send_token_activity" ), &bvalue ) ) {
        bSendTokenActivity = bvalue;
    }

    if ( VSCP_ERROR_SUCCESS == m_srv.getVariableBool( m_pObj->m_prefix + _( "_send_detect" ), &bvalue ) ) {
        bSendDetect = bvalue;
    }

    if ( VSCP_ERROR_SUCCESS == m_srv.getVariableBool( m_pObj->m_prefix + _( "_disable_radio_detect" ), &bvalue ) ) {
        bDisableRadiodetect = bvalue;
    }

    // Close the channel
    m_srv.doCmdClose();

    while ( !TestDestroy() && !m_pObj->m_bQuit ) {

        bt = BluetoothFindFirstRadio( &bt_find_radio, &radio );
    
        int radio_id = 0;
        do {

            radio_id++;

            if ( ERROR_SUCCESS == BluetoothGetRadioInfo( radio, &bt_info ) ) {

                strAddress.Printf( _("%02x:%02x:%02x:%02x:%02x:%02x"), 
                                        bt_info.address.rgBytes[ 0 ], 
                                        bt_info.address.rgBytes[ 1 ], 
                                        bt_info.address.rgBytes[ 2 ], 
                                        bt_info.address.rgBytes[ 3 ], 
                                        bt_info.address.rgBytes[ 4 ], 
                                        bt_info.address.rgBytes[ 5 ] );

                if ( deviceHashPrev.count( strAddress ) &&
                    ( NULL != ( pDevice = deviceHashPrev[ strAddress ] ) ) ) {
                    // Address is known and in the table 
                    pDevice->m_bfound = true;
                }
                else {

                    if ( !bDisableRadiodetect ) {

                        // Add the new device 
                        pDevice = new CDetectedDevice();
                        if ( NULL != pDevice ) {
                            pDevice->m_radio_id = radio_id;
                            pDevice->m_device_id = 0;
                            memcpy( pDevice->m_address, bt_info.address.rgBytes, 6 );
                            pDevice->m_name = bt_info.szName;
                            pDevice->m_class = bt_info.ulClassofDevice;
                            pDevice->m_manufacturer = bt_info.manufacturer;
                            deviceHashNow[ strAddress ] = pDevice;
                        }

                    }

                }

                search_params.hRadio = radio;

                ::ZeroMemory( &device_info, sizeof( BLUETOOTH_DEVICE_INFO ) );
                device_info.dwSize = sizeof( BLUETOOTH_DEVICE_INFO );

                if ( NULL != ( bt_dev = BluetoothFindFirstDevice( &search_params, &device_info ) ) ) {

                    int device_id = 0;
                    do {

                        device_id++;

                        strAddress.Printf( _("%02x:%02x:%02x:%02x:%02x:%02x"), 
                                                device_info.Address.rgBytes[ 0 ], 
                                                device_info.Address.rgBytes[ 1 ], 
                                                device_info.Address.rgBytes[ 2 ], 
                                                device_info.Address.rgBytes[ 3 ], 
                                                device_info.Address.rgBytes[ 4 ], 
                                                device_info.Address.rgBytes[ 5 ]);

                        if ( deviceHashPrev.count( strAddress ) &&
                                ( NULL != ( pDevice = deviceHashPrev[ strAddress ] ) ) ) {
                            // Address is known and in the table 
                            pDevice->m_bfound = true;
                        }
                        else {
                            
                            // Add the new device 
                            pDevice = new CDetectedDevice();
                            if ( NULL != pDevice ) {
                                pDevice->m_radio_id = radio_id;
                                pDevice->m_device_id = device_id;
                                memcpy( pDevice->m_address, device_info.Address.rgBytes, 6 );
                                pDevice->m_name = device_info.szName;
                                pDevice->m_class = device_info.ulClassofDevice;
                                memcpy( &pDevice->m_lastSeen, &device_info.stLastSeen, sizeof( SYSTEMTIME ) );
                                deviceHashNow[ strAddress ] = pDevice;
                            }   
                          
                        }

                    } while ( BluetoothFindNextDevice( bt_dev, &device_info ) );

                    BluetoothFindDeviceClose( bt_dev );
                }
            }

        } while ( BluetoothFindNextRadio( &bt_find_radio, &radio ) );

        BluetoothFindRadioClose( bt );

        // Go through devices that have been lost since last run
        
        _deviceHash::iterator itPrev;
        for ( itPrev = deviceHashPrev.begin(); itPrev != deviceHashPrev.end(); ++itPrev ) {

            wxString key = itPrev->first;
            CDetectedDevice *pDev = itPrev->second;
            if ( NULL == pDev ) {
                continue;
            }
            
            if ( false == pDev->m_bfound ) {

                if ( bSendTokenActivity ) {

                    vscpEventEx evx;

                    memset( evx.GUID, 0, 16 );   // Use interface GUID
                    evx.vscp_class = VSCP_CLASS2_LEVEL1_INFORMATION;
                    evx.vscp_type = VSCP_TYPE_INFORMATION_TOKEN_ACTIVITY;
                    evx.timestamp = wxDateTime::Now().GetTicks();
                    evx.head = VSCP_PRIORITY_NORMAL;
                    evx.sizeData = 8;
                    evx.data[ 0 ] = ( 18 << 2 ) + 2;   // Bluetooth device + "Released" 
                    evx.data[ 1 ] = zone;
                    evx.data[ 2 ] = subzone;
                    evx.data[ 3 ] = 0;               // Frame 0
                    evx.data[ 4 ] = pDev->m_address[ 0 ];
                    evx.data[ 5 ] = pDev->m_address[ 1 ];
                    evx.data[ 6 ] = pDev->m_address[ 2 ];
                    evx.data[ 7 ] = pDev->m_address[ 3 ];
   
                    sendEvent( evx ); // Send the event

                    memset( evx.GUID, 0, 16 );   // Use interface GUID
                    evx.vscp_class = VSCP_CLASS2_LEVEL1_INFORMATION;
                    evx.vscp_type = VSCP_TYPE_INFORMATION_TOKEN_ACTIVITY;
                    evx.timestamp = wxDateTime::Now().GetMillisecond();
                    evx.head = VSCP_PRIORITY_NORMAL;
                    evx.sizeData = 6;
                    evx.data[ 0 ] = ( 18 << 2 ) + 2;   // Bluetooth device + "Released" 
                    evx.data[ 1 ] = zone;
                    evx.data[ 2 ] = subzone;
                    evx.data[ 3 ] = 1;               // Frame 1
                    evx.data[ 4 ] = pDev->m_address[ 4 ];
                    evx.data[ 5 ] = pDev->m_address[ 5 ];

                    sendEvent( evx );

                }

                // Remove it
                delete pDev;
                deviceHashPrev[ key ] = NULL;

            }
            else {

                // Prepare for next detection loop
                pDev->m_bfound = false;

            }

        }

        // Go through devices that have been found since last run
        
        _deviceHash::iterator itNow;
        for ( itNow = deviceHashNow.begin(); itNow != deviceHashNow.end(); ++itNow ) {
            
            wxString key = itNow->first;
            CDetectedDevice *pDev = itNow->second;

            if ( NULL == pDev ) {
                continue;
            }

            // Save it in previously found devices
            deviceHashPrev[ key ] =  pDev;
            deviceHashNow[ key ] = NULL;

            if ( bSendTokenActivity ) {

                // Tell the world we found it
                vscpEventEx evx;

                memset( evx.GUID, 0, 16 );   // Use interface GUID
                evx.vscp_class = VSCP_CLASS2_LEVEL1_INFORMATION;
                evx.vscp_type = VSCP_TYPE_INFORMATION_TOKEN_ACTIVITY;
                evx.timestamp = wxDateTime::Now().GetMillisecond();
                evx.head = VSCP_PRIORITY_NORMAL;
                evx.sizeData = 8;
                evx.data[ 0 ] = ( 18 << 2 ) + 1;   // Bluetooth device + "Touched" 
                evx.data[ 1 ] = zone;
                evx.data[ 2 ] = subzone;
                evx.data[ 3 ] = 0;               // Frame 0
                evx.data[ 4 ] = pDev->m_address[ 0 ];
                evx.data[ 5 ] = pDev->m_address[ 1 ];
                evx.data[ 6 ] = pDev->m_address[ 2 ];
                evx.data[ 7 ] = pDev->m_address[ 3 ];

                sendEvent( evx );    // Send the event

                memset( evx.GUID, 0, 16 );   // Use interface GUID
                evx.vscp_class = VSCP_CLASS2_LEVEL1_INFORMATION;
                evx.vscp_type = VSCP_TYPE_INFORMATION_TOKEN_ACTIVITY;
                evx.timestamp = wxDateTime::Now().GetMillisecond();
                evx.head = VSCP_PRIORITY_NORMAL;
                evx.sizeData = 6;
                evx.data[ 0 ] = ( 18 << 2 ) + 1;   // Bluetooth device + "Touched" 
                evx.data[ 1 ] = zone;
                evx.data[ 2 ] = subzone;
                evx.data[ 3 ] = 1;               // Frame 1
                evx.data[ 4 ] = pDev->m_address[ 4 ];
                evx.data[ 5 ] = pDev->m_address[ 5 ];

                sendEvent( evx );    // Send the event
            
            }


            if ( bSendDetect ) {
            
                // Tell the world we detected it
                vscpEventEx evx;

                memset( evx.GUID, 0, 16 );   // Use interface GUID
                evx.vscp_class = VSCP_CLASS2_LEVEL1_INFORMATION;
                evx.vscp_type = VSCP_TYPE_INFORMATION_DETECT;
                evx.timestamp = wxDateTime::Now().GetMillisecond();
                evx.head = VSCP_PRIORITY_NORMAL;
                evx.sizeData = 3;
                evx.data[ 0 ] = detectIndex;
                evx.data[ 1 ] = detectZone;
                evx.data[ 2 ] = detectSubzone;

                sendEvent( evx );    // Send the event
            
            }       
            
        }

        wxSleep( pausTime );

    } // detect loop

    return NULL;  
}