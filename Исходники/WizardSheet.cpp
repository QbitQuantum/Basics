BOOL CWizardSheet::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	CWnd* pWnd = GetActivePage();

	if ( pWnd != NULL )
	{
		if ( GetWindowLongPtr( pWnd->GetSafeHwnd(), GWLP_USERDATA ) == TRUE )
		{
			pWnd = NULL;
		}
		else
		{
			SetWindowLongPtr( pWnd->GetSafeHwnd(), GWLP_USERDATA, TRUE );
			pWnd->SetFont( &theApp.m_gdiFont, FALSE );
			pWnd = pWnd->GetWindow( GW_CHILD );
		}
	}

	while ( pWnd != NULL )
	{
		TCHAR szName[32];

		GetClassName( pWnd->GetSafeHwnd(), szName, 32 );

		if ( _tcscmp( szName, L"Static" ) == 0 )
			pWnd->SetFont( &theApp.m_gdiFont, FALSE );
		else if ( _tcscmp( szName, L"RICHEDIT" ) != 0 )
			pWnd->SetFont( &theApp.m_gdiFont, TRUE );

		pWnd = pWnd->GetNextWindow();
	}

	return CPropertySheetAdv::OnChildNotify( message, wParam, lParam, pLResult );
}