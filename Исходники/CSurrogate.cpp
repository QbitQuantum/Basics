STDMETHODIMP 
CSurrogate::FreeSurrogate()
{
// tear down all connections with COM
    for (int i = 0; i < m_rgdwReg.size(); i++)
        CoRevokeClassObject(m_rgdwReg[i]);

// tear down all apartments
    {
    for (int i = 0; i < m_nMaxThreads; i++)
        m_prgSTAs[i].RequestShutdown(30000);
    }
// terminate main thread
    PostThreadMessage(m_dwThreadId, WM_QUIT, 0, 0);
    return S_OK;
}