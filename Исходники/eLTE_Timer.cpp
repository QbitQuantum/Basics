ELTE_VOID CTimer::SetTimer(ELTE_UINT32 tick)
{
	LOG_TRACE();
	if(m_uTimerID)
	{
		timeKillEvent(m_uTimerID);
		m_uTimerID = 0;
	}

	if(0 == tick)
	{
		//默认200ms发送数据
		tick = 200;
	}

	TIMECAPS   timecaps; 
	ELTE_UINT32 TimerAccuracy = Accuracy; 

	//从系统获得关于定时器服务能力的信息， 
	//分辨率不能超出系统许可值（1到16毫秒） 
	if   (timeGetDevCaps(&timecaps,sizeof(TIMECAPS))==TIMERR_NOERROR) 
		TimerAccuracy = min(max(timecaps.wPeriodMin,Accuracy),timecaps.wPeriodMax); 

	timeBeginPeriod(TimerAccuracy); 
	m_uDelayTime = tick;

	m_uTimerID = timeSetEvent(m_uDelayTime, TimerAccuracy, TimeProc, (DWORD_PTR)this, TIME_PERIODIC);
	LOG_RUN_DEBUG("TimerId is %d.", m_uTimerID);
	timeEndPeriod(TimerAccuracy); 
}