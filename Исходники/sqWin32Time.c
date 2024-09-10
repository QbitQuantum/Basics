void
ioInitTime()
{
# if !defined(_WIN32_WCE)
	TIMECAPS tCaps;

	dwTimerPeriod = 0;
	if(timeGetDevCaps(&tCaps,sizeof(tCaps)) != 0)
		return;
	dwTimerPeriod = tCaps.wPeriodMin;
	if (timeBeginPeriod(dwTimerPeriod) != 0)
		return;
# endif
}