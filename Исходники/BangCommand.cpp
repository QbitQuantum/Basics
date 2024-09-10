void Bang::Execute(HWND hCaller, LPCWSTR pwzParams) const
{
    if (GetCurrentThreadId() != m_dwThreadID)
    {
        ThreadedBangCommand * pInfo = new ThreadedBangCommand(hCaller,
                m_pwzCommand, pwzParams);

        if (pInfo != nullptr)
        {
            // target thread releases pInfo
            PostThreadMessageW(m_dwThreadID, LM_THREAD_BANGCOMMAND,
                               (WPARAM)pInfo, 0);
        }
    }
    else
    {
        if (m_bEX)
        {
            m_bBangEX(hCaller, m_pwzCommand, pwzParams);
        }
        else
        {
            m_bBang(hCaller, pwzParams);
        }
    }
}