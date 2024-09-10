LTRESULT CPickupItemPlugin::PreHook_EditStringList(const char* szRezPath,
												   const char* szPropName,
												   char** aszStrings,
												   uint32* pcStrings,
												   const uint32 cMaxStrings,
												   const uint32 cMaxStringLength)
{

	if (_strcmpi("ModelOverride", szPropName) == 0)
	{
		if (m_PropTypeMgrPlugin.PreHook_EditStringList(szRezPath,
			szPropName, aszStrings, pcStrings, cMaxStrings, cMaxStringLength) == LT_OK)
		{
			qsort( aszStrings, *pcStrings, sizeof( char * ), CaseInsensitiveCompare );

			return LT_OK;
		}
	}
	else if( _strcmpi( "WorldAnimation", szPropName ) == 0 )
	{
		for( int i = 0; i < PICKUP_MAX_WORLD_ANIS; ++i )
		{
			strcpy( aszStrings[(*pcStrings)++], c_aWorldAnimations[i] );
		}

		return LT_OK;
	}
	else if( _stricmp( "Team", szPropName ) == 0 )
	{
		char szTeam[32] = {0};

		_ASSERT(cMaxStrings > (*pcStrings) + 1);
		strcpy( aszStrings[(*pcStrings)++], "NoTeam" );
		
		for( int i = 0; i < MAX_TEAMS; ++i )
		{
			_ASSERT(cMaxStrings > (*pcStrings) + 1);

			sprintf( szTeam, "Team%i", i );
			strcpy( aszStrings[(*pcStrings)++], szTeam );
		}

		return LT_OK;
	}


	return LT_UNSUPPORTED;
}