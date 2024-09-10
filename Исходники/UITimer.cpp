	CDuiTimerBase::CDuiTimerBase( HWND hWnd,LPARAM lParam,WPARAM wParam,int iInterval,int iTotalTimer /*= NULL*/,bool bAutoRun /*= true*/,bool bLoop /*= false*/,bool bRevers /*= false*/ )
	{
		SetTimerParam(hWnd,lParam,wParam,iInterval,iTotalTimer,bAutoRun,bLoop,bRevers);

		TIMECAPS tc;
		if(timeGetDevCaps(&tc,sizeof(TIMECAPS))==TIMERR_NOERROR)
		{
			m_uTimerAccuracy=min(max(tc.wPeriodMin,1),tc.wPeriodMax);
			timeBeginPeriod(m_uTimerAccuracy);
		}
	}