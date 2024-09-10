HOOKFUNC MMRESULT WINAPI MytimeSetEvent(UINT uDelay, UINT uResolution, LPTIMECALLBACK lpTimeProc, DWORD_PTR dwUser, UINT fuEvent)
{
	if(tasflags.timersMode == 0)
	{
		debuglog(LCF_TIMERS, __FUNCTION__ " called (and suppressed).\n");
		return 11 * ++timerUID;
	}
	debuglog(LCF_TIMERS, __FUNCTION__ "(%d, %d, 0x%X, 0x%X, 0x%X) called.\n", uDelay, uResolution, (DWORD)lpTimeProc, (DWORD)dwUser, fuEvent);
	if(tasflags.timersMode == 2)
		return timeSetEvent(uDelay, uResolution, lpTimeProc, dwUser, fuEvent);
	TimerThreadInfo* threadInfo = new TimerThreadInfo(uDelay, uResolution, fuEvent, lpTimeProc, dwUser, 11 * ++timerUID);
	threadInfo->prevTime = detTimer.GetTicks();
	threadInfo->prev = ttiTail;
	ttiTail->next = threadInfo;
	ttiTail = threadInfo;
	timerListSize++;
	//threadInfo->handle = MyCreateThread(NULL, 0, MyTimerThread, threadInfo, 0, NULL);
	//SetThreadPriority(threadInfo->handle, THREAD_PRIORITY_BELOW_NORMAL);
	//if(!threadInfo->handle)
	//{
	//	threadInfo->prev->next = NULL;
	//	delete threadInfo;
	//	return NULL;
	//}
	debuglog(LCF_TIMERS, __FUNCTION__ " created TimerThreadInfo with uid 0x%X.\n", threadInfo->uid);
	return threadInfo->uid;
}