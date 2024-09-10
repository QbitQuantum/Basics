void TreePropertySheet::addTree()
{
	// Insert the space to the left
	CRect rcWindow,rcPage;

	HWND page = IndexToHwnd(0);
	::GetWindowRect(page, &rcPage);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rcPage, 2);

	CRect rc(SPACE_LEFT, rcPage.top, TREE_WIDTH, rcPage.bottom);
	ctrlTree.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_DISABLEDRAGDROP | TVS_TRACKSELECT, WS_EX_CLIENTEDGE, IDC_PAGE);
	
	if(BOOLSETTING(USE_EXPLORER_THEME) &&
		((WinUtil::getOsMajor() >= 5 && WinUtil::getOsMinor() >= 1) //WinXP & WinSvr2003
		|| (WinUtil::getOsMajor() >= 6))) //Vista & Win7
	{
	SetWindowTheme(ctrlTree.m_hWnd, L"explorer", NULL);
	}
	
	ctrlTree.SetImageList(tree_icons, TVSIL_NORMAL);
}