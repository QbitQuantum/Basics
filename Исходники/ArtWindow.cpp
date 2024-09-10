ArtWindow::ArtWindow()
{
	TIMECAPS tc;
	UINT wTimerRes;

	if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
	{
		console::error("Smooth Album Art: Timer error");
		// TODO: handle error
	}

	wTimerRes = min(max(tc.wPeriodMin, 1), tc.wPeriodMax);
	timeBeginPeriod(wTimerRes); 

	TimerQueue = NULL;
	RepaintTimer = NULL;
}