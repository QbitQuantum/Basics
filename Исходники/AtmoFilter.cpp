CAtmoLightFilter::~CAtmoLightFilter( )
{
    OleInitialize(NULL); 

    log("destroying atmo filtern\n");

    if(m_AtmoInitialized)
    {
        IAtmoRemoteControl *remoteControl = getAtmoRemoteControl();
        if(remoteControl)
        {
        if( m_CurrentAtmoEffect != cemLivePicture)
        {
            remoteControl->setEffect( m_CurrentAtmoEffect, &m_CurrentAtmoEffect );
        } else {
            IAtmoLiveViewControl *liveControl = getAtmoLiveViewControl();
            if(liveControl)
                {
                    liveControl->setLiveViewSource( lvsGDI );
                    liveControl->Release();
                }
        }
        remoteControl->Release(); 
        }
        if(m_pixel_buffer)
           SafeArrayDestroy( m_pixel_buffer );

        if(m_bitmap_header)
           SafeArrayDestroy( m_bitmap_header );
    }

    OleUninitialize();
    log("atmo filter destroyed\n\n\n");

    if(m_log_file)
       fclose( m_log_file );
    
    free( m_pszAtmoWin );
    free( m_pszLogFileName );
    free( m_pszImageLogPath );
}