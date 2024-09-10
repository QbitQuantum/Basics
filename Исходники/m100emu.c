/*
=============================================================================
This routine de-intializes the system timer used for throttling the emulation
speed.
=============================================================================
*/
void deinit_throttle_timer(void)
{
#ifdef WIN32
	/* Kill the timer event */
	if (gThrottleId != 0)
		timeKillEvent(gThrottleId);

	/* End the timer period */
	timeEndPeriod(gThrottlePeriod);

	/* Destory the triggering event */
	CloseHandle(gThrottleEvent);
#else
    /* Instruct the throttle thread to terminate */
    gThrottleExit = 1;

    /* Join our throttle thread to ensure a clean shutdown */
    pthread_join(gThrottleThread, NULL);
#endif
}