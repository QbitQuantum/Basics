bool COwnerVstEditor::SetSize(int contentWidth, int contentHeight)
//----------------------------------------------------------------
{
	if(contentWidth < 0 || contentHeight < 0 || !m_hWnd)
	{
		return false;
	}

	CRect rcWnd, rcClient;

	// Get border / menu size.
	GetWindowRect(&rcWnd);
	GetClientRect(&rcClient);

	MENUBARINFO mbi;
	MemsetZero(mbi);
	mbi.cbSize = sizeof(mbi);
	GetMenuBarInfo(m_hWnd, OBJID_MENU, 0, &mbi);
	int menuHeight = mbi.rcBar.bottom - mbi.rcBar.top;

	// Preliminary setup, which might have to be adjusted for small (narrow) plugin GUIs again,
	// since the menu might be two lines high...
	const int windowWidth = rcWnd.Width() - rcClient.Width() + contentWidth;
	const int windowHeight = rcWnd.Height() - rcClient.Height() + contentHeight;
	SetWindowPos(NULL, 0, 0,
		windowWidth, windowHeight,
		SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
	m_plugWindow.SetWindowPos(NULL, 0, 0,
		contentWidth, contentHeight,
		SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

	// Check if the height of the menu bar has changed.
	GetMenuBarInfo(m_hWnd, OBJID_MENU, 0, &mbi);

	const int menuHeightDiff = (mbi.rcBar.bottom - mbi.rcBar.top) - menuHeight;

	if(menuHeightDiff != 0)
	{
		// Menu height changed, resize window so that the whole content area can be viewed again.
		SetWindowPos(NULL, 0, 0,
			windowWidth, windowHeight + menuHeightDiff,
			SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
	}

	return true;
}