VOID GetBatteryState(BOOL *pbLBI, BOOL *pbVLBI)
{
#if defined BAT_SIMULATION
	switch (GetPrivateProfileInt(_T("LowBat"),_T("Level"),2,_T(".\\Lowbat.ini")))
	{
	case 0: // empty
		*pbLBI = TRUE;
		*pbVLBI = TRUE;
		break;
	case 1: // low
		*pbLBI = TRUE;
		*pbVLBI = FALSE;
		break;
	default: // full
		*pbLBI = FALSE;
		*pbVLBI = FALSE;
		break;
	}
#else
	SYSTEM_POWER_STATUS sSps;

	*pbLBI = FALSE;							// no battery warning
	*pbVLBI = FALSE;

	VERIFY(GetSystemPowerStatus(&sSps));

	// low bat emulation enabled and battery powered
	if (!bLowBatDisable && sSps.ACLineStatus == AC_LINE_OFFLINE)
	{
		// on critical battery state make sure that lowbat flag is also set
		if ((sSps.BatteryFlag & BATTERY_FLAG_CRITICAL) != 0)
			sSps.BatteryFlag |= BATTERY_FLAG_LOW;

		// low bat detection
		*pbLBI = ((sSps.BatteryFlag & BATTERY_FLAG_LOW) != 0);

		// very low bat detection
		*pbVLBI = ((sSps.BatteryFlag & BATTERY_FLAG_CRITICAL) != 0);
	}
#endif
	return;
}