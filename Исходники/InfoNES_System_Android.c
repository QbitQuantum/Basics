/*===================================================================*/
static void InfoNES_StopTimer()
{
	LOGV("InfoNES_StopTimer");
	if ( 0 != uTimerID )
	{
#ifdef WIN32
		TIMECAPS caps;
		timeKillEvent( uTimerID );
		uTimerID = 0;
		timeGetDevCaps( &caps, sizeof(caps) );
		timeEndPeriod( caps.wPeriodMin * TIMER_PER_LINE );
#else
		timer_delete( uTimerID );
		uTimerID = 0;
#endif
	}
	// Delete Critical Section Object
	LOGV("InfoNES_StopTimer finished");
}