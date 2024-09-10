bool CJSWatchDog::StartWatching()
{
	if(m_hTimer != INVALID_HANDLE_VALUE)
	{
		return false;
	}

	if(CreateTimerQueueTimer(&m_hTimer, NULL, TimerCallback, this,
		WATCHDOG_INTERVAL_IN_SECONDS * 2 * 1000, WATCHDOG_INTERVAL_IN_SECONDS * 1000,
		WT_EXECUTEINTIMERTHREAD))
	{
		m_bIsWatching = true;
		return true;
	}

	return false;
}