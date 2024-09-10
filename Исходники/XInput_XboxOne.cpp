void WINAPI XInputEnable
(
__in bool enable										// [in] Indicates whether xinput is enabled or disabled. 
)
{
	writeLog("XInputEnable", "controllerInit = %d - enable = %d \n", controllerInit, enable);
	if (!controllerInit)
	{
		connectController(true);
	}

	if (controllerInit && !enable)
	{
		XINPUT_VIBRATION Vibration = { 0, 0 };
		int xboxControllerCounter = 0;

		while (xboxControllerCounter < 4)
		{
			if (controllerHandler[xboxControllerCounter])
			{
				XInputSetState(xboxControllerCounter, &Vibration);
			}
			xboxControllerCounter++;
		}
	}
}