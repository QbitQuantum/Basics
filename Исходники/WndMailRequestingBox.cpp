//-----------------------------------------------------------------------------
BOOL CWndMailRequestingBox::OnChildNotify( UINT message, UINT nID, LRESULT* pLResult )
{
	switch( nID )
	{
	case WIDC_BUTTON_REQUEST:
		{
			++m_nDestroyCounter;
			CWndButton* pWndButton = ( CWndButton* )GetDlgItem( WIDC_BUTTON_REQUEST );
			if( pWndButton == NULL )
			{
				break;
			}

			if( pWndButton->IsWindowEnabled() == FALSE )
			{
				break;
			}

			g_DPlay.SendQueryMailBox();
			m_timeWaitingRequest = g_tmCurrent + SEC( REQUEST_BUTTON_WAITING_TIME );
			pWndButton->EnableWindow( FALSE );

			break;
		}
	}

	return CWndNeuz::OnChildNotify( message, nID, pLResult );
}