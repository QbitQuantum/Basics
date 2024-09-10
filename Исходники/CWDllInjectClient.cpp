BOOL CDllInjectClient::Connect( CONST WCHAR * aKey , PFN_DLL_INJECT_CLIENT_INIT_CBK aInitCbk )
{
    DbgOut( VERB , DBG_DLL_INJECT_MGR , "Enter. aKey=%ws" , aKey );

    _ASSERT( aKey );
    BOOL bRet = FALSE;
    
    HANDLE hSmInit = NULL;
    DLL_INJECT_SERVER_SM_INIT * pSmInit = NULL;

    if ( this->IsConnected() )
    {
        if ( m_wstrKey == aKey )
        {
            DbgOut( WARN , DBG_DLL_INJECT_MGR , "Shared memory already connected. aKey=%ws" , aKey );
            SetLastError( ERROR_ALREADY_EXISTS );
            bRet = TRUE;
        }
        else
        {
            DbgOut( ERRO , DBG_DLL_INJECT_MGR , "Shared memory already used by others. m_wstrKey=%ws, aKey=%ws" , m_wstrKey.c_str() , aKey );
            SetLastError( ERROR_ADDRESS_ALREADY_ASSOCIATED );
        }
        goto exit;
    }

    //Get all necessary handles and configuration from named share memory
    hSmInit = OpenFileMappingW( FILE_MAP_READ | FILE_MAP_WRITE , FALSE , aKey );
    if ( ! hSmInit )
    {
        DbgOut( ERRO , DBG_DLL_INJECT_MGR , "OpenFileMappingW() with name %ws failed. GetLastError()=%!WINERROR!" , aKey , GetLastError() );
        goto exit;
    }
    pSmInit = (DLL_INJECT_SERVER_SM_INIT *)MapViewOfFile( hSmInit , FILE_MAP_ALL_ACCESS , 0 , 0 , 0 );
    if ( ! pSmInit )
    {
        DbgOut( ERRO , DBG_DLL_INJECT_MGR , "MapViewOfFile() with name %ws failed. GetLastError()=%!WINERROR!" , aKey , GetLastError() );
        goto exit;
    }

    //Shared memory can be opened. Get data from shared memory first and then validate the content later
    m_wstrKey = aKey;
    CopyMemory( &m_SmInit , pSmInit , sizeof(m_SmInit) );

    pSmInit->InitRsp.dwHookStatus = ERROR_APP_INIT_FAILURE;
    pSmInit->InitRsp.hModule = (UINT64)GetModuleHandleW( NULL );

    

    //Validate Local handles
    if ( NULL == pSmInit->InitReq.Local.pLocalCtx || NULL == pSmInit->InitReq.Local.hRemoteProc || NULL == pSmInit->InitReq.Local.pfnFreeLibrary )
    {
        DbgOut( ERRO , DBG_DLL_INJECT_MGR , "InitReq.Local data are invalid" );
        goto exit;
    }

    //Validate Remote handles
    if ( NULL == pSmInit->InitReq.Remote.hEvtInitRsp || NULL == pSmInit->InitReq.Remote.hDllInjectMgrAliveThread )
    {
        DbgOut( ERRO , DBG_DLL_INJECT_MGR , "InitReq.Remote data are invalid" );
        goto exit;
    }
    for ( size_t i = 0 ; i < _countof( pSmInit->InitReq.Remote.hPerServerSm ) ; i++ )
    {
        if ( NULL == pSmInit->InitReq.Remote.hPerServerSm[i] )
        {
            DbgOut( ERRO , DBG_DLL_INJECT_MGR , "InitReq.Remote.hPerServerSm are invalid" );
            goto exit;
        }
    }
    for ( size_t i = 0 ; i < _countof( pSmInit->InitReq.Remote.hPerServerMutex ) ; i++ )
    {
        if ( NULL == pSmInit->InitReq.Remote.hPerServerMutex[i] )
        {
            DbgOut( ERRO , DBG_DLL_INJECT_MGR , "InitReq.Remote.hPerServerMutex are invalid" );
            goto exit;
        }
    }
    for ( size_t i = 0 ; i < _countof( pSmInit->InitReq.Remote.hPerServerEvt ) ; i++ )
    {
        if ( NULL == pSmInit->InitReq.Remote.hPerServerEvt[i] )
        {
            DbgOut( ERRO , DBG_DLL_INJECT_MGR , "InitReq.Remote.hPerServerEvt are invalid" );
            goto exit;
        }
    }
    for ( size_t i = 0 ; i < _countof( pSmInit->InitReq.Remote.hPerClientEvt ) ; i++ )
    {
        if ( NULL == pSmInit->InitReq.Remote.hPerClientEvt[i] )
        {
            DbgOut( ERRO , DBG_DLL_INJECT_MGR , "InitReq.Remote.hPerClientEvt are invalid" );
            goto exit;
        }
    }

    //Get shared memory used to exchange data
    m_SmData[PER_SERVER_SM_INDEX_REMOTE_TO_LOCAL] = (PDLL_INJECT_SERVER_SM_DATA_HEADER)MapViewOfFile( (HANDLE)pSmInit->InitReq.Remote.hPerServerSm[PER_SERVER_SM_INDEX_REMOTE_TO_LOCAL] , FILE_MAP_ALL_ACCESS , 0 , 0 , 0 );
    if ( NULL == m_SmData[PER_SERVER_SM_INDEX_REMOTE_TO_LOCAL] )
    {
        DbgOut( ERRO , DBG_DLL_INJECT_MGR , "MapViewOfFile() with PER_SERVER_SM_INDEX_REMOTE_TO_LOCAL failed. GetLastError()=%!WINERROR!" , GetLastError() );
        pSmInit->InitRsp.dwHookStatus = GetLastError();
        goto exit;
    }
    m_SmData[PER_SERVER_SM_INDEX_LOCAL_TO_REMOTE] = (PDLL_INJECT_SERVER_SM_DATA_HEADER)MapViewOfFile( (HANDLE)pSmInit->InitReq.Remote.hPerServerSm[PER_SERVER_SM_INDEX_LOCAL_TO_REMOTE] , FILE_MAP_ALL_ACCESS , 0 , 0 , 0 );
    if ( NULL == m_SmData[PER_SERVER_SM_INDEX_LOCAL_TO_REMOTE] )
    {
        DbgOut( ERRO , DBG_DLL_INJECT_MGR , "MapViewOfFile() with PER_SERVER_SM_INDEX_LOCAL_TO_REMOTE failed. GetLastError()=%!WINERROR!" , GetLastError() );
        pSmInit->InitRsp.dwHookStatus = GetLastError();
        goto exit;
    }

    DbgOut( VERB , DBG_DLL_INJECT_MGR , "Remote.hPerClientEvt[PER_CLIENT_EVT_INDEX_STOP]=0x%p, Remote.hPerClientEvt[PER_CLIENT_EVT_INDEX_REMOTE_REQ_OK]=0x%p, Remote.hPerClientEvt[PER_CLIENT_EVT_INDEX_REMOTE_RSP]=0x%p" ,
            (HANDLE)pSmInit->InitReq.Remote.hPerClientEvt[PER_CLIENT_EVT_INDEX_STOP] , (HANDLE)pSmInit->InitReq.Remote.hPerClientEvt[PER_CLIENT_EVT_INDEX_REMOTE_REQ_OK] , (HANDLE)pSmInit->InitReq.Remote.hPerClientEvt[PER_CLIENT_EVT_INDEX_REMOTE_RSP] );

    pSmInit->InitRsp.dwHookStatus = ( aInitCbk ) ? aInitCbk( pSmInit->InitReq.wzServerDirPath , pSmInit->InitReq.wzClientCfgPath ) : ERROR_SUCCESS;
    if ( ERROR_SUCCESS == pSmInit->InitRsp.dwHookStatus )
    {
        ATOMIC_ASSIGN( m_bConnected , TRUE );
        bRet = TRUE;
    }
    
exit :
    if ( pSmInit && pSmInit->InitReq.Remote.hEvtInitRsp )
    {
        SetEvent( (HANDLE)pSmInit->InitReq.Remote.hEvtInitRsp );
        CloseHandle( (HANDLE)pSmInit->InitReq.Remote.hEvtInitRsp );
        pSmInit->InitReq.Remote.hEvtInitRsp = NULL;
        m_SmInit.InitReq.Remote.hEvtInitRsp = NULL;
    }

    if ( pSmInit && FALSE == UnmapViewOfFile( pSmInit ) )
    {
        DbgOut( ERRO , DBG_DLL_INJECT_MGR , "UnmapViewOfFile() pSmInit failed. GetLastError()=%!WINERROR!" , GetLastError() );
    }
    if ( hSmInit && FALSE == CloseHandle( hSmInit ) )
    {
        DbgOut( ERRO , DBG_DLL_INJECT_MGR , "CloseHandle() hSmInit failed. GetLastError()=%!WINERROR!" , GetLastError() );
    }

    if ( FALSE == bRet )
    {
        this->Disconnect();
    }
    return bRet;
}