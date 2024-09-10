void InputMapper::SaveMappingsToDisk()
{
	IniFile ini;
	ini.ReadFile( KEYMAPS_PATH );
	
	const Game* pGame = GAMESTATE->GetCurrentGame();

	// erase the key so that we overwrite everything for this game
	ini.DeleteKey( pGame->m_szName );

	// iterate over our input map and write all mappings to the ini file
	FOREACH_GameController( i )
	{
		for( int j=0; j<pGame->m_iButtonsPerController; j++ )
		{
			GameInput GameI( i, (GameButton)j );
			CString sNameString = GameI.toString( pGame );
			
			vector<CString> asValues;
			for( int button = 0; button < NUM_GAME_TO_DEVICE_SLOTS; ++button )
				asValues.push_back( m_GItoDI[i][j][button].toString() );
			while( asValues.size() && asValues.back() == "" )
				asValues.erase( asValues.begin()+asValues.size()-1 );
			CString sValueString = join( ",", asValues );

			ini.SetValue( pGame->m_szName, sNameString, sValueString );
		}
	}

	ini.WriteFile( KEYMAPS_PATH );
}