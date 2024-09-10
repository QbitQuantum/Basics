    /// 回报服务状态
    bool win_svc_base::ReportStatus(unsigned long dwCurrentState, unsigned long dwExitCode
        , unsigned long dwCheckPoint, unsigned long dwWaitHint)
    {
        if (dwCurrentState == SERVICE_START_PENDING)
            m_pWinStructImpl->m_ssStatus.dwControlsAccepted = 0;
        else
            m_pWinStructImpl->m_ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;

        // Initialize ss structure.
        m_pWinStructImpl->m_ssStatus.dwServiceType             = SERVICE_WIN32_OWN_PROCESS;
        m_pWinStructImpl->m_ssStatus.dwServiceSpecificExitCode = 0;
        m_pWinStructImpl->m_ssStatus.dwCurrentState            = dwCurrentState;
        m_pWinStructImpl->m_ssStatus.dwWin32ExitCode           = dwExitCode;
        m_pWinStructImpl->m_ssStatus.dwCheckPoint              = dwCheckPoint;
        m_pWinStructImpl->m_ssStatus.dwWaitHint                = dwWaitHint;

        bool bRet = (SetServiceStatus(m_pWinStructImpl->m_ssh, &m_pWinStructImpl->m_ssStatus) ? true : false);
        //LOG << "call ReportStatus dwCurrentState=" << dwCurrentState << " ret=" << bRet << std::endl;
        return bRet;
    }