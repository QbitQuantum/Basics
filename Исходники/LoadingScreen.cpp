void CLoadingScreen::UpdateSessionName( )
{
	// If connecting to a remote server, set our mission descriptor to 
	// the ip we're connecting to.
	if( g_pClientConnectionMgr->IsConnectedToRemoteServer( ))
	{
		// Make a loading string using the IP to be joined.
		wchar_t szLoadingString[256];

//		LTSNPrintF( szSession, LTARRAYSIZE(szSession), L"%s", g_pClientConnectionMgr->GetStartGameRequest().m_pNetSession->m_sName );
		if ( !LTStrEmpty(g_pClientConnectionMgr->GetServerName()))
		{
			LTSNPrintF( szLoadingString, LTARRAYSIZE(szLoadingString), L"%s:  %s", LoadString("IDS_CONNECTING_TO_SERVER"), 
				g_pClientConnectionMgr->GetServerName() );
		}
		else
		{
			LTSNPrintF( szLoadingString, LTARRAYSIZE(szLoadingString), L"%s", LoadString("IDS_CONNECTING_TO_SERVER"));
		}
		m_MissionName.SetFont(g_CurrentLayout.m_sLevelFont);
		m_MissionName.SetString(szLoadingString);

		LTSNPrintF( szLoadingString, LTARRAYSIZE(szLoadingString), L"    (%S)", g_pClientConnectionMgr->GetStartGameRequest( ).m_TCPAddress );

		m_LevelName.SetString(szLoadingString);
	}
	// Local game, set the mission descriptor to the level name.
	else
	{
		m_MissionName.SetFont(g_CurrentLayout.m_sTitleFont);
		if (g_pGameClientShell->IsRunningPerformanceTest())
		{
			m_MissionName.SetString(LoadString( "IDS_TITLE_PERFORMANCE_TEST" ));
			m_LevelName.SetString(L"");
		}
		else
		{
			m_MissionName.SetString(LoadString( "IDS_CUSTOM_LEVEL" ));
			// Split the worldname up into parts so we can get the load string.
			wchar_t szWorldTitle[MAX_PATH] = L"";
			_wsplitpath( MPA2W(g_pMissionMgr->GetCurrentWorldName( )).c_str(), NULL, NULL, szWorldTitle, NULL );
			m_LevelName.SetString(szWorldTitle);
		}
	}
}