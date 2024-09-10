HRESULT CTedPlayer::InitClear()
{
    HRESULT hr;
    
    if(m_spSession)
    {
        if(m_bIsPlaying)
        {
            m_bIsPlaying = false;
            m_spSession->Stop();
        }
        
        m_spSession.Release();
    }
    
	if(m_fPendingClearCustomTopoloader && m_spClearSession.p)
	{
        m_spClearSession->Shutdown();
        m_spClearSession.Release();
	}

    if(m_spClearSession.p == NULL)
    {
        CComPtr<IMFAttributes> spConfiguration = NULL;
        if(m_fPendingClearCustomTopoloader && GUID_NULL != m_gidCustomTopoloader)
        {
            IFC( MFCreateAttributes(&spConfiguration, 1) );
            IFC( spConfiguration->SetGUID(MF_SESSION_TOPOLOADER, m_gidCustomTopoloader) );
        }

        IFC( MFCreateMediaSession(spConfiguration, &m_spClearSession) );
        IFC( m_spClearSession->BeginGetEvent(&m_xOnClearSessionEvent, NULL) );

        m_fPendingClearCustomTopoloader = false;
    }
    
    m_spSession = m_spClearSession;
    
    IFC( InitFromSession() );
    
Cleanup:
    return hr;
}