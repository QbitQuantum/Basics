	double getTimeSeconds(void)
	{
		static char init = 0;
		static TIMECAPS timerInfo;
		
		if(!init)
		{
			timeGetDevCaps(&timerInfo, sizeof(TIMECAPS));
			timeBeginPeriod(timerInfo.wPeriodMin);
			init = 1;
		}	
		
		return (double) (timeGetTime() / 1000.0);
	}