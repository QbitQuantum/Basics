//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CDPlay8Client::JoinSession( DWORD num )
{
    HRESULT hr;
    IDirectPlay8Address* pHostAddress = NULL;
    IDirectPlay8Address* pDeviceAddress = NULL;

    if( m_pDPlay == NULL )
        return E_FAIL;

    DXTRACE( TEXT("MazeClient: Trying to connect to server\n") );

    DPN_APPLICATION_DESC dpnAppDesc;
    ZeroMemory( &dpnAppDesc, sizeof( DPN_APPLICATION_DESC ) );
    dpnAppDesc.dwSize          = sizeof( DPN_APPLICATION_DESC );
    dpnAppDesc.guidApplication = StressMazeAppGUID;
    dpnAppDesc.guidInstance    = m_Sessions[num].guidInstance;

    EnterCriticalSection( &m_csLock );
    
    // Copy the host and device address pointers, and addref them.
    // If this is not done, then there is a rare chance that 
    // EnumSessionCallback() may be called during the Connect() call 
    // and destory the address before DirectPlay gets a chance to copy them.
    pHostAddress = m_pHostAddresses[num];
    pHostAddress->AddRef();

    pDeviceAddress = m_pDeviceAddresses[num];
    pDeviceAddress->AddRef();

    LeaveCriticalSection( &m_csLock );

    // Connect to the remote host
    // The enumeration is automatically canceled after Connect is called 
    if( FAILED( hr = m_pDPlay->Connect( &dpnAppDesc,        // Application description
                                        pHostAddress,       // Session host address
                                        pDeviceAddress,     // Address of device used to connect to the host
                                        NULL, NULL,         // Security descriptions & credientials (MBZ in DPlay8)
                                        NULL, 0,            // User data & its size
                                        NULL,               // Asynchronous connection context (returned with DPNMSG_CONNECT_COMPLETE in async handshaking)
                                        NULL,               // Asynchronous connection handle (used to cancel connection process)
                                        DPNOP_SYNC ) ) )    // Connect synchronously
    {
        if( hr == DPNERR_NORESPONSE || hr == DPNERR_ABORTED )
            goto LCleanup; // These are possible if the server exits while joining 

        if( hr == DPNERR_INVALIDINSTANCE )
            goto LCleanup; // This is possible if the original server exits and another server comes online while we are connecting

        DXTRACE_ERR_NOMSGBOX( TEXT("Connect"), hr );
        goto LCleanup;
    }

    m_bSessionLost = FALSE;
    
    DXTRACE( TEXT("MazeClient: Connected to server.  Enum automatically canceled\n") );

    UpdateConnectionInfo();
    m_fLastUpdateConnectInfoTime = DXUtil_Timer( TIMER_GETAPPTIME );


LCleanup:
    SAFE_RELEASE( pHostAddress );
    SAFE_RELEASE( pDeviceAddress );

    return hr;
}