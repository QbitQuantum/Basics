unsigned HostTimerDispatcher::setTimeout(unsigned delay, IDispatch* pDisp)
{
	if (!pDisp) return 0;
	unsigned timerID = timeSetEvent(delay, m_accuracy, g_timer_proc, reinterpret_cast<DWORD_PTR>(m_hWnd), TIME_ONESHOT);
	addTimerMap(timerID, pDisp);
	return timerID;
}