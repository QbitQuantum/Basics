void SaveGamePrefsToDisk()
{
	if( !GAMESTATE )
		return;

	CString sGameName = GAMESTATE->GetCurrentGame()->m_szName;
	IniFile ini;
	ini.ReadFile( GAMEPREFS_INI_PATH );	// it's OK if this fails

	ini.SetValue( sGameName, "Announcer",			ANNOUNCER->GetCurAnnouncerName() );
	ini.SetValue( sGameName, "Theme",				THEME->GetCurThemeName() );
	ini.SetValue( sGameName, "DefaultModifiers",	PREFSMAN->m_sDefaultModifiers );
	ini.SetValue( "Options", "Game",				(CString)GAMESTATE->GetCurrentGame()->m_szName );

	ini.WriteFile( GAMEPREFS_INI_PATH );
}