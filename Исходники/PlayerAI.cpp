void PlayerAI::InitFromDisk()
{
	IniFile ini;
	ini.ReadFile( AI_PATH );

	for( int i=0; i<NUM_SKILL_LEVELS; i++ )
	{
		CString sKey = ssprintf("Skill%d", i);
		XNode* pNode = ini.GetChild(sKey);
		if( pNode == NULL )
			RageException::Throw( "AI.ini: '%s' doesn't exist.", sKey.c_str() );

		TapScoreDistribution& dist = g_Distributions[i];
		dist.fPercent[TNS_NONE] = 0;
		pNode->GetAttrValue( "MissWeight", dist.fPercent[TNS_MISS] );
		pNode->GetAttrValue( "BooWeight", dist.fPercent[TNS_BOO] );
		pNode->GetAttrValue( "GoodWeight", dist.fPercent[TNS_GOOD] );
		pNode->GetAttrValue( "GreatWeight", dist.fPercent[TNS_GREAT] );
		pNode->GetAttrValue( "PerfectWeight", dist.fPercent[TNS_PERFECT] );
		pNode->GetAttrValue( "MarvelousWeight", dist.fPercent[TNS_MARVELOUS] );
		
		float fSum = 0;
		for( int j=0; j<NUM_TAP_NOTE_SCORES; j++ )
			fSum += dist.fPercent[j];
		for( int j=0; j<NUM_TAP_NOTE_SCORES; j++ )
			dist.fPercent[j] /= fSum;
	}
}