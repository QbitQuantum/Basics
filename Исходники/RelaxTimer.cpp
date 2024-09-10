void RelaxTimer::ProcessAutoPauseStatus()
{
    LASTINPUTINFO lpi;
    lpi.cbSize = sizeof(lpi);
    GetLastInputInfo(&lpi);

    if (m_eAutoPauseType == AUTO_PAUSE_FULLSCREEN)
    {
        if (FullscreenModeDectect() == FALSE)
        {// 如果不在全屏模式，则允许进入工作状态，且继续进行idle状态检测
            AutoPause2Work();
        }
        else
        {// 如果仍然处于是全屏状态，则不允许进行后续的idle状态检测
            return;
        }
    }
    
    if (m_bEnableAutoPause == TRUE)
    {
        // 如果发现有输入，则转入工作态
        if (::GetTickCount() - lpi.dwTime < m_nAutoPauseThreshold * 1000)
        {
            AutoPause2Work();
            return;
        }
    }
    if (m_bEnableAutoReset == TRUE)
    {
        // 如果长时间没有输入，则转入自动复位态
        if (::GetTickCount() - lpi.dwTime >= m_nAutoResetThreshold * 1000)
        {
            AutoPause2AutoReset();
            return;
        }
    }
}