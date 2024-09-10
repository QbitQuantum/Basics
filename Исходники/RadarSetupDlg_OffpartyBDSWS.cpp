void OFFBDSWS_OnApply( HWND hDlg )
{
	//log_error( LOG_OK, "OFFBDSWS_OnApply\n" );
	int c = IsDlgButtonChecked( hDlg, IDC_C_INVBD );
	if( c ) rsobdsws->inv_bd_enable = 1;
	else rsobdsws->inv_bd_enable = 0;
	c = IsDlgButtonChecked( hDlg, IDC_C_INVSWS );
	if( c ) rsobdsws->inv_sws_enable = 1;
	else rsobdsws->inv_sws_enable = 0;
	//
	GetDlgItemTextW( hDlg, IDC_E_BDNAME, rsobdsws->nameBD, 63 );
	GetDlgItemTextW( hDlg, IDC_E_SWSNAME, rsobdsws->nameSWS, 63 );
	//
	rsobdsws->inv_bd_secs = GetDlgItemInt( hDlg, IDC_E_INV_BD_SEC, NULL, TRUE );
	rsobdsws->inv_sws_secs = GetDlgItemInt( hDlg, IDC_E_INV_SWS_SEC, NULL, TRUE );
	//
	rsobdsws->dismiss_bd_secs = GetDlgItemInt( hDlg, IDC_E_DISMISS_BD_SEC, NULL, TRUE );
	rsobdsws->dismiss_sws_secs = GetDlgItemInt( hDlg, IDC_E_DISMISS_SWS_SEC, NULL, TRUE );
	//
	// apply setup immediately
	g_game_client->ai.setOffpartyBDSWS_Config( rsobdsws );
	//rsobdsws->saveToFile( "L2Detect_offp_BDSWS.ini" );
}