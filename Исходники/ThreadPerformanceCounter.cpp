void CThreadPerformanceCounter::DoPerformanceCount()
{
	if(m_TreadHandle)
	{
		m_CycleCount++;
		if(m_CountIntervalTimer.IsTimeOut(m_CountIntervalTime))
		{
			m_CountIntervalTimer.SaveTime();

			UINT64 CurPerformanceCount=CEasyTimerEx::GetTime();
			float CPUTime=(float)(CurPerformanceCount-m_StartPerformanceCount)/CEasyTimerEx::TIME_UNIT_PER_SECOND;		
			m_StartPerformanceCount=CurPerformanceCount;

			m_CycleTime=CPUTime*1000.0f/m_CycleCount;
			m_CycleCount=0;

			UINT64 CurCPUUsedTime;
#ifdef WIN32
			FILETIME CreationTime,ExitTime,KernelTime,UserTime;
			if(!GetThreadTimes(m_TreadHandle,
				&CreationTime,&ExitTime,
				&KernelTime,&UserTime))
			{
				PrintSystemLog(0,_T("获取线程CPU时间失败%d"),GetLastError());
			}
			CurCPUUsedTime=((UINT64)KernelTime.dwLowDateTime)|(((UINT64)KernelTime.dwHighDateTime)<<32);
			CurCPUUsedTime+=((UINT64)UserTime.dwLowDateTime)|(((UINT64)UserTime.dwHighDateTime)<<32);
#else
			timespec OrginTime;		
			clock_gettime(CLOCK_THREAD_CPUTIME_ID,&OrginTime);
			CurCPUUsedTime=(UINT64)OrginTime.tv_sec*1000000000+OrginTime.tv_nsec;
#endif

			m_CPUUsedRate=(float)(CurCPUUsedTime-m_StartCPUUsedTime)/(CPUTime*m_CPUCount*10000000.0f);

			m_StartCPUUsedTime=CurCPUUsedTime;
		}
	}
}