/**
 * Return remaining battery time in seconds.
 * @return Battery time in seconds or 0 if no battery (or connected to power)
 */
EXPORT int get_battery_state(void)
{
	SYSTEM_POWER_STATUS powerStatus;
	int batteryTime = 0;

	if (GetSystemPowerStatus(&powerStatus) == TRUE)
	{

		if (powerStatus.ACLineStatus == 0)
			batteryTime = (int) powerStatus.BatteryLifeTime;
	}
	return batteryTime;
}