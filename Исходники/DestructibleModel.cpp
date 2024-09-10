LTRESULT CDestructibleModelPlugin::PreHook_EditStringList(const char* szRezPath,
	const char* szPropName, char** aszStrings, uint32* pcStrings,
	const uint32 cMaxStrings, const uint32 cMaxStringLength)
{
	// DestructibleModel property lists here...

	if( !sm_bInitted )
	{
		// Make sure fx mgr is initialized...
		m_pFXButeMgrPlugin->PreHook_EditStringList(szRezPath, szPropName,
			aszStrings,	pcStrings, cMaxStrings, cMaxStringLength);

		sm_bInitted = LTTRUE;
	}

	if (m_DebrisPlugin.PreHook_EditStringList(szRezPath, szPropName,
		aszStrings, pcStrings, cMaxStrings, cMaxStringLength) == LT_OK)
	{
		return LT_OK;
	}
	else if (_strcmpi("SurfaceOverride", szPropName) == 0)
	{
		m_SurfaceMgrPlugin.PreHook_EditStringList(szRezPath, szPropName,
			aszStrings, pcStrings, cMaxStrings, cMaxStringLength);

		if (m_SurfaceMgrPlugin.PopulateStringList(aszStrings, pcStrings,
			 cMaxStrings, cMaxStringLength))
		{
			return LT_OK;
		}
	}

	return LT_UNSUPPORTED;
}