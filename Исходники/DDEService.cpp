void DDEService::_DoStop()
{
    DdeNameService(m_dwDDEInst, 0L, 0L, DNS_UNREGISTER);
    if (m_hszProgman)
    {
        DdeFreeStringHandle(m_dwDDEInst, m_hszProgman);
    }
    if (m_hszGroups)
    {
        DdeFreeStringHandle(m_dwDDEInst, m_hszGroups);
    }
    if (m_hszFolders)
    {
        DdeFreeStringHandle(m_dwDDEInst, m_hszFolders);
    }
    if (m_hszAppProperties)
    {
        DdeFreeStringHandle(m_dwDDEInst, m_hszAppProperties);
    }
    DdeUninitialize(m_dwDDEInst);

    m_dwDDEInst = 0;

    CoUninitialize();
}