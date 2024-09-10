TimeSource * TimeSource::get()
{
    if (!m_pTimeSource) {
#ifdef _WIN32
        TIMECAPS tc;
        UINT wTimerRes;
        MMRESULT err = timeGetDevCaps(&tc, sizeof(TIMECAPS));
        AVG_ASSERT(err == TIMERR_NOERROR);
        wTimerRes = max(tc.wPeriodMin, 1);
        timeBeginPeriod(wTimerRes);
#endif
        m_pTimeSource = new TimeSource;
    }
    return m_pTimeSource;
}