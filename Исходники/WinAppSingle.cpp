BOOL CWinAppSingle::OnAnotherInstanceMessage( LPMSG pMsg )
{
	// Get command line arguments (if any) from new instance.
	
	BOOL bShellOpen = FALSE;
	
	if( pMsg->wParam != NULL ) 
	{
		::GlobalGetAtomName( (ATOM)pMsg->wParam, m_lpCmdLine, _MAX_FNAME );			
		::GlobalDeleteAtom(  (ATOM)pMsg->wParam );		
		bShellOpen = TRUE;		
	}
	
	// If got valid command line then try to open the document -
	// CDocManager will popup main window itself. Otherwise, we
	// have to popup the window 'manually' :

	if( m_pDocManager != NULL && bShellOpen ) 
	{
		CWaitCursor wait;		
		m_pDocManager->OpenDocumentFile( m_lpCmdLine );
	}
	else if( ::IsWindow( m_pMainWnd->GetSafeHwnd() ) )
	{
		// Does the main window have any popups ? If has, 
		// bring the main window or its popup to the top
		// before showing:

		CWnd* pPopupWnd = m_pMainWnd->GetLastActivePopup();
		pPopupWnd->BringWindowToTop();

		// If window is not visible then show it, else if
		// it is iconic, restore it:

		if( !m_pMainWnd->IsWindowVisible() )
			m_pMainWnd->ShowWindow( SW_SHOWNORMAL ); 
		else if( m_pMainWnd->IsIconic() )
			m_pMainWnd->ShowWindow( SW_RESTORE );
		
		// And finally, bring to top after showing again:

		pPopupWnd->BringWindowToTop();
		pPopupWnd->SetForegroundWindow(); 
	}
	
	return TRUE;
}