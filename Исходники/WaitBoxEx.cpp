MyQProgressDialog::~MyQProgressDialog()
{
    if (m_hUpdateTimer)
    {
        DeleteTimerQueueTimer(m_hTimerQueue, m_hUpdateTimer, NULL);
        m_hUpdateTimer = NULL;
    }

    if (m_hTimerQueue)
    {
        DeleteTimerQueueEx(m_hTimerQueue, NULL);
        m_hTimerQueue = NULL;
    }

    if (m_hWinHook)
    {
        UnhookWindowsHookEx(m_hWinHook);
        m_hWinHook = NULL;
    }
    
    if (m_hMouseHook)
    {
        UnhookWindowsHookEx(m_hMouseHook);
        m_hMouseHook = NULL;
    }
}