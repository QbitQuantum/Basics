bool UnlockSystem::Load()
{
	LOG->Trace( "UnlockSystem::Load()" );
	
	if( !IsAFile(UNLOCKS_PATH) )
		return false;

	MsdFile msd;
	if( !msd.ReadFile( UNLOCKS_PATH ) )
	{
		LOG->Warn( "Error opening file '%s' for reading: %s.", UNLOCKS_PATH, msd.GetError().c_str() );
		return false;
	}

	unsigned i;

	for( i=0; i<msd.GetNumValues(); i++ )
	{
		int iNumParams = msd.GetNumParams(i);
		const MsdFile::value_t &sParams = msd.GetValue(i);
		CString sValueName = sParams[0];

		if( iNumParams < 1 )
		{
			LOG->Warn("Got \"%s\" tag with no parameters", sValueName.c_str());
			continue;
		}

		if( !stricmp(sParams[0],"ROULETTE") )
		{
			for( unsigned j = 1; j < sParams.params.size(); ++j )
				m_RouletteCodes.insert( atoi(sParams[j]) );
			continue;
		}
		
		if( stricmp(sParams[0],"UNLOCK") )
		{
			LOG->Warn("Unrecognized unlock tag \"%s\", ignored.", sValueName.c_str());
			continue;
		}

		UnlockEntry current;
		current.m_sSongName = sParams[1];
		LOG->Trace("Song entry: %s", current.m_sSongName.c_str() );

		CStringArray UnlockTypes;
		split( sParams[2], ",", UnlockTypes );

		for( unsigned j=0; j<UnlockTypes.size(); ++j )
		{
			CStringArray readparam;

			split( UnlockTypes[j], "=", readparam );
			const CString &unlock_type = readparam[0];

			LOG->Trace("UnlockTypes line: %s", UnlockTypes[j].c_str() );

			const float fVal = strtof( readparam[1], NULL );
			const int iVal = atoi( readparam[1] );

			const UnlockType ut = StringToUnlockType( unlock_type );
			if( ut != UNLOCK_INVALID )
				current.m_fRequired[ut] = fVal;
			if( unlock_type == "CODE" )
				current.m_iCode = iVal;
			if( unlock_type == "RO" )
			{
				current.m_iCode = iVal;
				m_RouletteCodes.insert( iVal );
			}
		}

		m_SongEntries.push_back(current);
	}

	UpdateSongs();

	for(i=0; i < m_SongEntries.size(); i++)
	{
		CString str = ssprintf( "Unlock: %s; ", m_SongEntries[i].m_sSongName.c_str() );
		for( int j = 0; j < NUM_UNLOCK_TYPES; ++j )
			if( m_SongEntries[i].m_fRequired[j] )
				str += ssprintf( "%s = %f; ", g_UnlockNames[j], m_SongEntries[i].m_fRequired[j] );

		str += ssprintf( "code = %i ", m_SongEntries[i].m_iCode );
		str += m_SongEntries[i].IsLocked()? "locked":"unlocked";
		if( m_SongEntries[i].m_pSong )
			str += ( " (found song)" );
		if( m_SongEntries[i].m_pCourse )
			str += ( " (found course)" );
		LOG->Trace( "%s", str.c_str() );
	}
	
	return true;
}