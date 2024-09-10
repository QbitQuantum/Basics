/* Sleep function */
void SleepMs(uint32_t MilliSeconds)
{
	/* Lookup */
	MCoreDevice_t *tDevice = DmGetDevice(DeviceTimer);
	MCoreTimerDevice_t *Timer = NULL;

	/* Sanity */
	if (tDevice == NULL)
	{
		DelayMs(MilliSeconds);
		return;
	}
	
	/* Cast */
	Timer = (MCoreTimerDevice_t*)tDevice->Data;

	/* Go */
	Timer->Sleep(Timer->TimerData, MilliSeconds);
}