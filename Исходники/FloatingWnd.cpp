LRESULT CFloatingWnd::OnRButtonDown(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL& bHandled){
	if (m_FloatingWndmenu.m_hMenu != NULL)
		return 0;
	SetFocus();
	RECT rc;
	GetClientRect(&rc);
	MapWindowPoints(HWND_DESKTOP, (POINT *)&rc, 2);
	// Cursor's horizontal and vertical position
	CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); 
	// Convert client coordinates to screen coordinates 
	ClientToScreen(&pt);
	// Load the menu resource 
	if (!m_FloatingWndmenu.LoadMenu(IDR_POPUP))
	{
		ATLTRACE(_T("Menu resource was not loaded successfully!\n"));
		return 0;
	}
	// TrackPopupMenu cannot display the menu bar so get 
	// a handle to the first shortcut menu. 
 	CMenuHandle menuPopup = m_FloatingWndmenu.GetSubMenu(0);
	if (menuPopup.m_hMenu == NULL)
	{
		ATLTRACE(_T("Submenu was not retrieved successfully!\n"));
		return 0;
	}
	// Display the shortcut menu
 	//if (!menuPopup.TrackPopupMenu(TPM_LEFTALIGN|TPM_TOPALIGN|TPM_LEFTBUTTON, rc.left ,rc.bottom, m_hWnd))
	if (!menuPopup.TrackPopupMenu(TPM_LEFTALIGN|TPM_TOPALIGN|TPM_LEFTBUTTON, pt.x ,pt.y, m_hWnd))
	{
		ATLTRACE(_T("Context menu was not displayed successfully!\n"));
		return 0;
	}
	// Destroy the menu and free any memory that the menu occupies
	menuPopup.DestroyMenu();
	m_FloatingWndmenu.DestroyMenu();
	m_FloatingWndmenu.m_hMenu = NULL;
	return 0;
}