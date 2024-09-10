// Creates a context menu
LRESULT CSearchList::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Retrieve the index of the currently selected item
	int nIndex = GetSelectedIndex();

	// Display the context menu
	if (nIndex != LB_ERR)
	{
		if (::IsMenu(m_menuSearch.m_hMenu))
		{
			ATLTRACE(_T("Menu is already displayed!\n"));
			return 0;
		}

		// Cursor's horizontal and vertical position
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		// Load the menu resource 
		if (!m_menuSearch.LoadMenu(IDR_DELETE_NOTE))
		{
			ATLTRACE(_T("Menu resource was not loaded successfully!\n"));
			return 0;
		}

		// TrackPopupMenu cannot display the menu bar so get 
		// a handle to the first shortcut menu. 
 		CMenuHandle menuPopup = m_menuSearch.GetSubMenu(0);
		if (menuPopup.m_hMenu == NULL)
		{
			ATLTRACE(_T("Submenu was not retrieved successfully!\n"));
			return 0;
		}

		// Display the shortcut menu
 		if (!menuPopup.TrackPopupMenu(TPM_LEFTALIGN|TPM_TOPALIGN|TPM_LEFTBUTTON,
								pt.x, pt.y, m_hWnd))
		{
			ATLTRACE(_T("Context menu was not displayed successfully!\n"));
			return 0;
		}		

		// Destroy the menu and free any memory that the menu occupies
		menuPopup.DestroyMenu();
		m_menuSearch.DestroyMenu();
		m_menuSearch.m_hMenu = NULL;
	}

	return 0;
}