//
// IService::Stop
//
HRESULT ExplorerService::Stop()
{
    if (m_dwThreadID)
    {
        HWND hProgman = FindWindow(_T("Progman"), NULL);
        SendMessage(hProgman, 0x44D, 0, 0);
        PostMessage(hProgman, WM_QUIT, 0, 1);
    }

    if (m_hExplorerThread)
    {
        if (WaitForSingleObject(m_hExplorerThread, 1000) != WAIT_OBJECT_0)
        {
            TerminateThread(m_hExplorerThread, 0);
        }

        TRACE("%p", GetShellWindow());

        CloseHandle(m_hExplorerThread);
        m_hExplorerThread = nullptr;
    }

    return S_OK;
}