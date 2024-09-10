wxZRColaFrame::~wxZRColaFrame()
{
    // Unregister global hotkey(s).
    UnregisterHotKey(wxZRColaHKID_INVOKE_DECOMPOSE);
    UnregisterHotKey(wxZRColaHKID_INVOKE_COMPOSE);

#if defined(__WXMSW__)
    if (m_tfSource) {
        m_tfSource->UnadviseSink(m_dwCookie);
        m_tfSource->Release();
    }
#endif

    if (m_chrReq)
        delete m_chrReq;

    if (m_chrSelect)
        delete m_chrSelect;

    if (m_settings)
        delete m_settings;

    if (m_taskBarIcon) {
        m_taskBarIcon->Disconnect(wxEVT_TASKBAR_LEFT_DOWN, wxTaskBarIconEventHandler(wxZRColaFrame::OnTaskbarIconClick), NULL, this);
        delete m_taskBarIcon;
    }
}