void CSystemTimer::RecordDifference(CLog &LogFile, const CSystemTimer& rSystemTimer)
{
    if (m_LastUpdate != rSystemTimer.m_LastUpdate)
    {
        LogFile.LogF("Timer-LastUpdate: %X %X\r\n", m_LastUpdate, rSystemTimer.m_LastUpdate);
    }
    if (m_NextTimer != rSystemTimer.m_NextTimer)
    {
        LogFile.LogF("Timer-NextTimer: %X %X\r\n", m_NextTimer, rSystemTimer.m_NextTimer);
    }
    if (m_Current != rSystemTimer.m_Current)
    {
        LogFile.LogF("Timer-Current %X %X\r\n", m_Current, rSystemTimer.m_Current);
    }
    if (m_inFixTimer != rSystemTimer.m_inFixTimer)
    {
        LogFile.LogF("Timer-inFixTimer %X %X\r\n", (int)m_inFixTimer, (int)rSystemTimer.m_inFixTimer);
    }

    for (int i = 0; i < MaxTimer; i++)
    {
        if (m_TimerDetatils[i].Active != rSystemTimer.m_TimerDetatils[i].Active)
        {
            LogFile.LogF("Timer-m_TimerDetatils[%d] %X %X\r\n", i, (int)m_TimerDetatils[i].Active, (int)rSystemTimer.m_TimerDetatils[i].Active);
        }
        if (m_TimerDetatils[i].CyclesToTimer != rSystemTimer.m_TimerDetatils[i].CyclesToTimer)
        {
            LogFile.LogF("Timer-m_TimerDetatils[%d] 0x%08X, 0x%08X\r\n", i, (uint32_t)m_TimerDetatils[i].CyclesToTimer, (uint32_t)rSystemTimer.m_TimerDetatils[i].CyclesToTimer);
        }
    }
}