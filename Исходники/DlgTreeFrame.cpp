BOOL CDlgTreeFrame::SetPage(HTPAGE hpg)
{
	// Sanity checks
	if ( hpg == NULL ) return FALSE;

	// Lose current page
	if (	m_hpg != NULL && m_hpg->pg != NULL &&
			IsWindow( m_hpg->pg->GetSafeHwnd() ) )
	{
		// Hide the page
		m_hpg->pg->ShowWindow( SW_HIDE );

	} // end if

	// Get a pointer to the help button
	CWnd *pHelp = GetDlgItem( IDC_PLEASEHELP );

	// Enable / Disable help button
	if ( pHelp != NULL )
	{
		// Show help button if help file
		if ( hpg != NULL && hpg->help[ 0 ] != NULL )
		{
			pHelp->ShowWindow( SW_SHOWNORMAL );

			// Disable button if file not available
			char link[ CWF_STRSIZE ];
			CWinFile::BuildPath( link, m_helproot, hpg->help );
			pHelp->EnableWindow( CWinFile::DoesExist( link ) );
		} // end if

		// Is there a link
		else if ( hpg != NULL && hpg->hlink[ 0 ] != NULL )
			pHelp->EnableWindow( TRUE );

		// Hide help button if no help
		else pHelp->ShowWindow( SW_HIDE );

	} // end if

	if ( hpg != NULL && hpg->pg != NULL )
	{
		// Create dialog if needed
		if ( !::IsWindow( hpg->pg->GetSafeHwnd() ) )
			hpg->pg->Create( hpg->idd, &m_blank );

	} // end if

	// Save current page
	m_hpg = hpg;

	m_dwLastPage = m_hpg->index;

	// Size everything
	Size();

	return TRUE;
}