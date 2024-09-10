bool classPARSESTR::DoFree( char* pStr )
{
	char* pARG;
	
	// ON, OFF
	pARG   = ParseString(pStr,1);

	if( _strcmpi( "WEIGHT", pARG ) == 0 )
	{
		if( CGame::GetInstance().GetRight() )
		{
			g_GameDATA.m_bNoWeight = !g_GameDATA.m_bNoWeight;
			if( g_GameDATA.m_bNoWeight )
				g_pNet->Send_cli_SET_WEIGHT_RATE( 0 );					

			return true;
		}
	}

	if( _strcmpi( "CHAT", pARG ) == 0 )
	{
		CTDialog* pDlg = g_itMGR.FindDlg( DLG_TYPE_CHAT );
		if( CGame::GetInstance().GetRight() && pDlg )
		{
			CChatDLG* pChatDlg = (CChatDLG*)pDlg;
			pChatDlg->SetDisableShoutRestrict();
			return true;
		}
	}
	return false;
}