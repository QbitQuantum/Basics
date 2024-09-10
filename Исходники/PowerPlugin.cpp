PLUGIN_EXPORT double Update(void* data)
{
	MeasureData* measure = (MeasureData*)data;

	SYSTEM_POWER_STATUS sps;
	if (GetSystemPowerStatus(&sps))
	{
		switch (measure->type)
		{
		case POWER_ACLINE:
			return sps.ACLineStatus == 1 ? 1.0 : 0.0;

		case POWER_STATUS:
			if (sps.BatteryFlag & 128)
			{
				return 0.0;	// No battery
			}
			else if (sps.BatteryFlag & 8)
			{
				return 1.0;	// Charging
			}
			else if (sps.BatteryFlag & 4)
			{
				return 2.0;	// Critical
			}
			else if (sps.BatteryFlag & 2)
			{
				return 3.0;	// Low
			}
			else if (sps.BatteryFlag & 1)
			{
				return 4.0;	// High
			}
			break;

		case POWER_STATUS2:
			return sps.BatteryFlag;

		case POWER_LIFETIME:
			return sps.BatteryLifeTime;

		case POWER_PERCENT:
			return sps.BatteryLifePercent == 255 ? 100.0 : sps.BatteryLifePercent;

		case POWER_MHZ:
		case POWER_HZ:
			if (g_NumOfProcessors > 0)
			{
				PROCESSOR_POWER_INFORMATION* ppi = new PROCESSOR_POWER_INFORMATION[g_NumOfProcessors];
				memset(ppi, 0, sizeof(PROCESSOR_POWER_INFORMATION) * g_NumOfProcessors);
				CallNtPowerInformation(ProcessorInformation, nullptr, 0, ppi, sizeof(PROCESSOR_POWER_INFORMATION) * g_NumOfProcessors);
				double value = (measure->type == POWER_MHZ) ? ppi[0].CurrentMhz : ppi[0].CurrentMhz * 1000000.0;
				delete [] ppi;
				return value;
			}
		}
	}

	return 0.0;
}