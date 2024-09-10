JNIEXPORT void JNICALL Java_sage_PowerManagement_setPowerState0
  (JNIEnv *env, jobject jo, jint powerState)
{
	EXECUTION_STATE es = 0;
	if (powerState & sage_PowerManagement_SYSTEM_POWER)
		es |= ES_SYSTEM_REQUIRED;
	if (powerState & sage_PowerManagement_DISPLAY_POWER)
		es |= ES_DISPLAY_REQUIRED;
	// This one will reset the idle timer so we'll be up for the PM timeout; which is good for when there's user activity
	if (powerState & sage_PowerManagement_USER_ACTIVITY)
		SetThreadExecutionState(es);
	// This one doesn't involve timeouts; it just tells the system if we need display or system power
	es |= ES_CONTINUOUS;
	SetThreadExecutionState(es);

	// See if we need to enable the SS
	if (disabledSS && ((powerState & sage_PowerManagement_DISPLAY_POWER) == 0))
	{
		// Enable the SS
		SystemParametersInfo(SPI_SETSCREENSAVEACTIVE,
		     TRUE,
             0,
             SPIF_SENDWININICHANGE);
		disabledSS = FALSE;
		slog((env, "Enabled SS\r\n"));
	}
	else if (!disabledSS && ((powerState & sage_PowerManagement_DISPLAY_POWER) != 0))
	{
		// Check if the screen saver is enabled, disable it if it is
		BOOL pvParam = 0;
		SystemParametersInfo(SPI_GETSCREENSAVEACTIVE,
                         0,
                         &pvParam,
                         0
                       );
		if (pvParam)
		{
			if (SystemParametersInfo(SPI_SETSCREENSAVEACTIVE,
		         FALSE,
                 0,
                 SPIF_SENDWININICHANGE))
			{
				slog((env, "Disabled SS\r\n"));
				disabledSS = TRUE;
			}
		}
	}
}