void CImageTreeCtrl::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: Add your message handler code here

	
	CPoint pt(point);
	ScreenToClient(&pt);
	UINT flags;
	HTREEITEM hItem = HitTest(pt, &flags);
	bool bOnItem = (flags & TVHT_ONITEM) != 0;

	CMenu add;
	VERIFY(add.CreatePopupMenu());
	if(bOnItem) {
		if(CanInsertItem(GetParentItem(hItem)))
			VERIFY(add.AppendMenu(MF_STRING, ID_ADD_SIBLING, _T("New Sibling\tINS")));
		if(CanInsertItem(hItem))
			VERIFY(add.AppendMenu(MF_STRING, ID_ADD_CHILD, _T("New Child Item\tCtrl+INS")));
	}
	if(CanInsertItem(0))
		VERIFY(add.AppendMenu(MF_STRING, ID_ADD_ROOT, _T("New Root Item\tShift+INS")));

	CMenu sort;
	VERIFY(sort.CreatePopupMenu());
	VERIFY(sort.AppendMenu(MF_STRING, ID_SORT_LEVEL, _T("Current Level\tCtrl+S")));
	VERIFY(sort.AppendMenu(MF_STRING, ID_SORT_LEVELANDBELOW, _T("Current Level And Below\tCtrl+Shift+S")));

	CMenu menu;
	VERIFY(menu.CreatePopupMenu());
	if(bOnItem) {
		if(CanEditLabel(hItem))
			VERIFY(menu.AppendMenu(MF_STRING, ID_RENAME, _T("Rename\tF2")));
		if(CanDeleteItem(hItem))
			VERIFY(menu.AppendMenu(MF_STRING, ID_DELETE, _T("Delete\tDEL")));
	}
	if(add.GetMenuItemCount() > 0)
		VERIFY(menu.AppendMenu(MF_POPUP, UINT(add.GetSafeHmenu()), _T("Add")));
	if(bOnItem) {
		if(menu.GetMenuItemCount() > 0)
			VERIFY(menu.AppendMenu(MF_SEPARATOR));
		VERIFY(menu.AppendMenu(MF_POPUP, UINT(sort.GetSafeHmenu()), _T("Sort")));
	}

	

	// maybe the menu is empty...
	if(menu.GetMenuItemCount() > 0)
		menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	

}