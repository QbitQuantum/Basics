CSpeedLimiter::CSpeedLimiter()
{
    m_Frames = 0;
    m_LastTime = 0;
    m_Speed = 60;
    m_BaseSpeed = 60;
    m_Ratio = 1000.0F / (float)m_Speed;

#ifdef _WIN32
    TIMECAPS Caps;
    timeGetDevCaps(&Caps, sizeof(Caps));
    if (timeBeginPeriod(Caps.wPeriodMin) == TIMERR_NOCANDO)
    {
        g_Notify->DisplayError("Error during timer begin");
    }
#endif
}