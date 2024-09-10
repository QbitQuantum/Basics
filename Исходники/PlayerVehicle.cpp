LTRESULT CPlayerVehiclePlugin::PreHook_EditStringList(
	const char* szRezPath,
	const char* szPropName,
	char** aszStrings,
    uint32* pcStrings,
    const uint32 cMaxStrings,
    const uint32 cMaxStringLength)
{

	// Handle vehicle type...

	if (_strcmpi("VehicleType", szPropName) == 0)
	{
		for (int i=PPM_FIRST; i < PPM_NUM_MODELS; i++)
		{
			_ASSERT(cMaxStrings > (*pcStrings) + 1);
			if (cMaxStrings > (*pcStrings) + 1)
			{
				strcpy(aszStrings[(*pcStrings)++], GetPropertyNameFromPlayerPhysicsModel((PlayerPhysicsModel)i));
			}
		}

		return LT_OK;
	}

	return LT_UNSUPPORTED;
}