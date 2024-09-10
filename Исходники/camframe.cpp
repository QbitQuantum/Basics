void CCamFrame::OnInitMenuPopup( wxMenuEvent& event )
{
	// Before anything else let's set Document::Current and DocView::Current properly...
	// Menus will either work on no document or the selected document. So the most useful
	// thing to do is to set Current to Selected.
	Document::GetSelected()->SetCurrent();
	DocView::GetSelected()->SetCurrent();

	wxSetCursor( *wxSTANDARD_CURSOR );

PORTNOTE( "other", "Removed usage of bSysMent from OnInitMenuPopup" )
#if !defined(EXCLUDE_FROM_XARALX)
	if (bSysMenu)
	{
		CMDIFrameWnd::OnInitMenuPopup(pMenu, n, bSysMenu);
		// bug fix 2996 
		if(FullScreenMode)
		{
			pMenu->EnableMenuItem(SC_MOVE,MF_GRAYED);
			pMenu->EnableMenuItem(SC_SIZE,MF_GRAYED);
			pMenu->EnableMenuItem(SC_MAXIMIZE,MF_GRAYED);
		}
	}
	else
#endif
	if( !UpdateMenu( event.GetMenu() ) )
		event.Skip();
}