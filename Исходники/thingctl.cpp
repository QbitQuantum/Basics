void CThingTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// find out where we clicked (on a thing, a module, or what)

	CMenu menu;
	CPoint temppoint;
	HTREEITEM hParent, hNextParent;
	HTREEITEM hItem = NULL;
	UINT uFlags = 0;
	
	// save the point for later
	temppoint = point;

	// tree uses client points
	m_treeCtrl.ScreenToClient(&temppoint);

	// now do a hittest on the tree
	hItem = m_treeCtrl.HitTest(temppoint, &uFlags);

	if (!hItem)
		return;

	// only select if we clicked on the icon or the label
//	if(!(uFlags & TVHT_ONITEM))
		// we arent right clicking on anything so return
//		return;

	m_treeCtrl.SelectItem(hItem);

	hParent = hItem;
	hNextParent = m_treeCtrl.GetParentItem( hItem );
	while (hNextParent != NULL)
	{
		hParent = hNextParent;
		hNextParent = m_treeCtrl.GetParentItem( hParent );
	}

	if (hParent == m_hRoom)
	{
		VERIFY(menu.LoadMenu(IDR_ROOM_MENU));
	}
	else if (hParent == m_hModules)
	{
		VERIFY(menu.LoadMenu(IDR_MODULE_MENU));
	}
	else
		return;

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

}