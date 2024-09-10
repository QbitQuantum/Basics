void SysTimer::trigger(unsigned long msec)
{
	EnterCriticalSection(&Win32::win32Section);
	data->lastDelay = msec;
	if (data->timerId != NULL)
		timeKillEvent(data->timerId);
	data->timerId = timeSetEvent(msec, 5, timerProc, (DWORD_PTR)data, TIME_ONESHOT | TIME_CALLBACK_FUNCTION | TIME_KILL_SYNCHRONOUS);
	LeaveCriticalSection(&Win32::win32Section);
}