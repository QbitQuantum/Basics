BOOL CWndCloseExistingConnection::OnChildNotify( UINT message, UINT nID, LRESULT* pLResult ) 
{ 
	if( nID == WIDC_YES )
	{
		g_dpCertified.SendCloseExistingConnection( g_Neuz.m_szAccount, g_Neuz.m_szPassword );
		Sleep( 1000 );
		CWndLogin* pWndLogin	= (CWndLogin*)g_WndMng.GetWndBase( APP_LOGIN );
		if( pWndLogin )
			pWndLogin->GetDlgItem( WIDC_OK )->EnableWindow( TRUE );
		Destroy( TRUE );
	}
	else if( nID == WIDC_NO )
	{
//		g_dpCertified.Destroy( TRUE );
		CWndLogin* pWndLogin	= (CWndLogin*)g_WndMng.GetWndBase( APP_LOGIN );
		if( pWndLogin )
			pWndLogin->GetDlgItem( WIDC_OK )->EnableWindow( TRUE );
		Destroy( TRUE );
	}
	return CWndNeuz::OnChildNotify( message, nID, pLResult ); 
}