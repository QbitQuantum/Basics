int COption::Defalt( LPCTSTR szFileName )
{
	CResFile file; 
	_tcscpy( m_szFileName, szFileName);

	  CScannerEx scan;

	if(file.Open( szFileName, "rb" ) == FALSE )
			Error( "%s failed to load", szFileName );
	   return 0;

	if(scan.Load_FileIO( szFileName ) == FALSE )
	   return 0;

	do {
		scan.GetToken();

		if( scan.Token == _T( "view" ) )
		{
			m_nViewArea = scan.GetNumber();
		}
		else
		if( scan.Token == _T( "distant" ) )
		{
			m_nObjectDistant = scan.GetNumber();
		}
		else
		if( scan.Token == _T( "detail" ) )
			m_nObjectDetail = scan.GetNumber();
		else
		if( scan.Token == _T( "shadow" ) )
		{
			m_nShadow = scan.GetNumber();
		}
		else
#ifdef __SFX_OPT
	    if(scan.Token == _T( "SFXLEVEL" ))
	    {
			m_nSfxLevel = scan.GetNumber();
	    }
#endif
		if( scan.Token == _T( "SFXRenderOff" ) )
		{
			m_bSFXRenderOff = scan.GetNumber();
		}
	    else if(scan.Token == _T( "ZOOMLIMIT" ))
	    {
			m_bZoomLimit = scan.GetNumber();
	    }
		if( scan.Token == _T( "DamageRender" ) )
		{
			m_bDamageRender = scan.GetNumber();
		}
		else
		if( scan.Token == _T( "PRenderName" ) )
		{
			m_nPlayerName = scan.GetNumber();
		}	
		else
		if( scan.Token == _T( "OPRenderName" ) )
		{
			m_nOtherPlayerName = scan.GetNumber();
		}
	    else 
		if(scan.Token == _T( "WEATHEREFFECT" ))
	    {
			m_nWeatherEffect = scan.GetNumber();
	    }
	    else
		if(scan.Token == _T( "VIEWMASK" ))
	    {
			m_bViewMask = scan.GetNumber();
	    }
		if( scan.Token == _T( "CameraLock" ) )
		{
			m_bCameraLock = scan.GetNumber();
		}	
		else
		if( scan.Token == _T( "Trade") )
		{
			m_bTrade = scan.GetNumber();
		}
		else
		if( scan.Token == _T( "Say") )
		{
			m_bSay = scan.GetNumber();
		}
		else
		if( scan.Token == _T( "Messenger") )
		{
			m_bMessenger = scan.GetNumber();
		}
		else
		if( scan.Token == _T( "Party") )
		{
			m_bParty = scan.GetNumber();
		}
		else
		if( scan.Token == _T( "AutoAttack" ) )
		{
			m_bAutoAttack = scan.GetNumber();
		}
		else

		if( scan.Token == _T( "MessengerJoin" ) )
		{
			m_bMessengerJoin = scan.GetNumber();
		}
		else
		if( scan.Token == _T( "InstantHelp" ) ) 
		{
			m_nInstantHelp = scan.GetNumber();
		}
		else
		if( scan.Token == _T( "Guide" ) )
		{
			m_nGuide1        = scan.GetNumber();
		}
		else
#ifdef __GAME_GRADE_SYSTEM
		if( scan.Token == _T( "GameGrade") )
		{
			m_bGameGradeRendering = scan.GetNumber();
		}
		else
#endif // __GAME_GRADE_SYSTEM
		if( scan.Token == _T( "WindowAlpha" ) ) 
		{
			m_nWindowAlpha = scan.GetNumber();
		}
		else
		if( scan.Token == _T( "Sound" ) )
		{
			m_bVoice        = scan.GetNumber();
			m_fEffectVolume = scan.GetFloat();
			m_fBGMVolume    = scan.GetFloat();
		}
		else
		if( scan.Token == _T( "BattleBGM") )
		{
			m_bBattleBGM = scan.GetNumber();
		}

	} while( scan.tok != FINISHED );

	CheckResolution();


	m_nChatCommand				= 0;
	m_nSlangWord				= 0;
	m_nInterface				= 1;
	m_bRollEffect				= FALSE;
	m_MouseSpeed				= 1;
	m_bVisibleBuffTimeRender	= TRUE;
	m_bShout					= TRUE;
	m_bMessengerJoin   			= TRUE;

	return 1;
}