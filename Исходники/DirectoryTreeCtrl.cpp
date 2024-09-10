void CDirectoryTreeCtrl::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CPoint ptMenu(-1, -1);
	if (point.x != -1 && point.y != -1)
	{
		ptMenu = point;
		ScreenToClient(&point);
	}
	else
	{
		HTREEITEM hSel = GetNextItem(TVI_ROOT, TVGN_CARET);
		if (hSel)
		{
			CRect rcItem;
			if (GetItemRect(hSel, &rcItem, TRUE))
			{
				ptMenu.x = rcItem.left;
				ptMenu.y = rcItem.top;
				ClientToScreen(&ptMenu);
			}
		}
		else
			ClientToScreen(&(ptMenu = (0, 0)));
	}

	HTREEITEM hItem = HitTest(point);

	// create the menu
	CTitleMenu SharedMenu;
	SharedMenu.CreatePopupMenu();
	SharedMenu.AddMenuTitle(GetResString(IDS_SHAREDFOLDERS));
	bool bMenuIsEmpty = true;

	// add all shared directories
	int iCnt = 0;
	for (POSITION pos = m_lstShared.GetHeadPosition(); pos != NULL; iCnt++)
	{
		CString strDisplayPath(m_lstShared.GetNext(pos));
		PathRemoveBackslash(strDisplayPath.GetBuffer(strDisplayPath.GetLength()));
		strDisplayPath.ReleaseBuffer();
		SharedMenu.AppendMenu(MF_STRING,MP_SHAREDFOLDERS_FIRST+iCnt, GetResString(IDS_VIEW1) + strDisplayPath);
		bMenuIsEmpty = false;
	}

	// add right clicked folder, if any
	if (hItem)
	{
		m_strLastRightClicked = GetFullPath(hItem);
		if (!IsShared(m_strLastRightClicked))
		{
			CString strDisplayPath(m_strLastRightClicked);
			PathRemoveBackslash(strDisplayPath.GetBuffer(strDisplayPath.GetLength()));
			strDisplayPath.ReleaseBuffer();
			if (!bMenuIsEmpty)
				SharedMenu.AppendMenu(MF_SEPARATOR);
			SharedMenu.AppendMenu(MF_STRING, MP_SHAREDFOLDERS_FIRST-1, GetResString(IDS_VIEW1) + strDisplayPath + GetResString(IDS_VIEW2));
			bMenuIsEmpty = false;
		}
	}

	// display menu
	if (!bMenuIsEmpty)
		SharedMenu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, ptMenu.x, ptMenu.y, this);
	VERIFY( SharedMenu.DestroyMenu() );
}