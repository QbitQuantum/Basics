MFPlayerService::~MFPlayerService()
{

#ifndef Q_WS_SIMULATOR
    if (m_videoWindowControl)
        delete m_videoWindowControl;
#endif

    if (m_videoRendererControl)
        delete m_videoRendererControl;

    m_session->shutdown();
    m_session->Release();

    MFShutdown();
    CoUninitialize();
}