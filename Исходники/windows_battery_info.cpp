double windows_battery_info::get_battery_percentage()
{
	SYSTEM_POWER_STATUS power_status;
	BOOL success = GetSystemPowerStatus(&power_status);
	if(success) {
		return power_status.BatteryLifePercent;
	} else {
		return 0.0;
	}
}