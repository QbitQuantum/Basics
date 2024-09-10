void CMainFrame::OnContextMenu(HWND /*hWnd*/, CPoint pos)
{
	int selectedItemData;

	// get selectedItemData
	CRect rect;
	CPoint posInView;
	HTREEITEM hItemSelected;

	// if clicked on tree, we need to change selection
	if (m_viewTreeList.GetWindowRect( rect ) && rect.PtInRect(pos) )
	{
		CTreeViewCtrlEx ctrlTree = m_viewTreeList.GetTreeControl();
		CHeaderCtrl ctrlHeader = m_viewTreeList.GetHeaderControl();

		CRect rectHeader;
		ctrlHeader.GetClientRect(rectHeader);

		// clicked point is inside the tree control
		// Change screen coordinates to client coordinates
		posInView = pos - rect.TopLeft();
		posInView.y -= rectHeader.Height();

		if(hItemSelected = ctrlTree.HitTest(posInView, NULL))
		{
			ctrlTree.SelectItem(hItemSelected);
		}
	}

	CNBDevice *pDevice = m_viewTreeList.GetSelectedDevice();

	if(!pDevice)
		return;

	CMenu menu;
	CMenuHandle subMenu;

	menu.LoadMenu(IDR_MAINFRAME);
	subMenu = menu.GetSubMenu(1); // Tool
	
	subMenu.TrackPopupMenu(
		TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
		pos.x, 
		pos.y, 
		m_hWnd
		);
	
	return;

}