void RadarSetupDlg_FollowAssist_OnApply( HWND hDlg )
{
	// follow sets
	g_game_client->ai.folAsiCfg.m_follow_enable = IsDlgButtonChecked( hDlg, IDC_C_FOLLOW_ENABLE );
	g_game_client->ai.folAsiCfg.m_follow_dist = (int)GetDlgItemInt( hDlg, IDC_E_FOLLOW_DISTANCE, NULL, FALSE );
	GetDlgItemTextW( hDlg, IDC_E_NAME_FOLLOW, g_game_client->ai.folAsiCfg.m_follow_name, 127 );
	g_game_client->ai.folAsiCfg.m_follow_only_in_party = IsDlgButtonChecked( hDlg, IDC_C_FOLLOW_ONLY_IN_PARTY );
	// assist sets
	g_game_client->ai.folAsiCfg.m_assist_enable = IsDlgButtonChecked( hDlg, IDC_C_ASSIST_ENABLE );
	GetDlgItemTextW( hDlg, IDC_E_NAME_ASSIST, g_game_client->ai.folAsiCfg.m_assist_name, 127 );
	g_game_client->ai.folAsiCfg.m_assist_only_in_party = IsDlgButtonChecked( hDlg, IDC_C_ASSIST_ONLY_IN_PARTY );
	g_game_client->ai.folAsiCfg.m_assist_dont_ally = IsDlgButtonChecked( hDlg, IDC_C_DONT_ASSIST_ALLIES );
	// save config to file
	g_game_client->ai.folAsiCfg.saveToFile( "L2Detect_folAsi.ini" );
	// checks
	if( !g_game_client->ai.folAsiCfg.m_follow_enable )
		g_game_client->ai.followDisable(); // zero follow objectID
	if( !g_game_client->ai.folAsiCfg.m_assist_enable )
		g_game_client->ai.assistDisable(); // zero assist objectID
}