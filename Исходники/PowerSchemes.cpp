/// <summary>
/// Restores the individual default power scheme settings.
/// </summary>
/// <returns></returns>
BOOL PowerSchemes::RestoreIndividualDefaultPowerSchemeSettings()
{
	/*   GUID_MIN_POWER_SAVINGS      = High performance                        */
	/*   GUID_MAX_POWER_SAVINGS      = Power saver                             */
	/*   GUID_TYPICAL_POWER_SAVINGS  = Balanced                                */
	BOOL IsSuccess = FALSE; 

	if(CompareScheme(*mySchemeGuid, GUID_MIN_POWER_SAVINGS))
	{ 
		IsSuccess = PowerRestoreIndividualDefaultPowerScheme(&GUID_MIN_POWER_SAVINGS); 
	}

	else if(CompareScheme(*mySchemeGuid, GUID_MAX_POWER_SAVINGS))
	{ 
		IsSuccess = PowerRestoreIndividualDefaultPowerScheme(&GUID_MAX_POWER_SAVINGS); 
	}

	else if(CompareScheme(*mySchemeGuid, GUID_TYPICAL_POWER_SAVINGS))
	{ 
		IsSuccess = PowerRestoreIndividualDefaultPowerScheme(&GUID_TYPICAL_POWER_SAVINGS); 
	}

	else if(CompareScheme(*mySchemeGuid, GUID_POWER_AWARE_SMJ))
	{ 
		IsSuccess = PowerRestoreIndividualDefaultPowerScheme(&GUID_MIN_POWER_SAVINGS); 
	} 

	return IsSuccess;
}