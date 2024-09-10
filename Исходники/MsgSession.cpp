//------------------------------------------------------------------*
HRESULT CFCMessageSessionThread::DoDisconnect()
{
    HRESULT hr;

    if (m_pMessage != NULL) {

        TrcPrint(TRC_INTERFACE, _T("MsgSession: DoDisconnect(%s)\n"),(LPCTSTR) m_pRawMsgSession->m_strMachineName);

        hr = m_pMessage->Disconnect(m_lKey);

        if (m_dwMsgNotifyCookie != 0UL) {
            hr = AtlUnadvise(m_pMessage, IID__ICERemoteMessageEvent, m_dwMsgNotifyCookie);
        }
        m_dwMsgNotifyCookie = 0;

        Logout();

        FC_RELEASE_PTR(m_pCheckConnection);
        FC_RELEASE_PTR(m_pMessage);
        CoDisconnectObject(this, 0);
    }
    return S_OK;
}