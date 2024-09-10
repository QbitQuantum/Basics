LRESULT CVGMFileListView::OnContextMenu(HWND hwndCtrl, CPoint ptClick )
{
	//bHandled = TRUE;
	//CTreeViewCtrlEx* treeview = (CTreeViewCtrlEx*)hwndCtrl;

	// if Shift-F10
	if (ptClick.x == -1 && ptClick.y == -1)
		ptClick = (CPoint) GetMessagePos();

	ScreenToClient(&ptClick);

	UINT uFlags;
	//HTREEITEM htItem = GetTreeCtrl().HitTest( ptMousePos, &uFlags );
	int iItem = HitTest( ptClick, &uFlags );

	if( iItem == -1 )
		return 0;

	vector<VGMFile*> vgmfiles;
	UINT selectedCount = GetSelectedCount();
	if (selectedCount > 1)
	{
		iItem = -1;
		for (UINT i = 0; i < selectedCount; i++)
		{
			iItem = GetNextItem(iItem, LVNI_SELECTED);
			ATLASSERT(iItem != -1);
			vgmfiles.push_back((VGMFile*)GetItemData(iItem));
		}
	}
	else
	{
		vgmfiles.push_back((VGMFile*)GetItemData(iItem));
	}

	if (vgmfiles.size() > 1)
	{
		CMenu mnuContext;
		mnuContext.LoadMenu(IDR_RAWFILE);
		CMenuHandle pPopup = mnuContext.GetSubMenu(0);
		ClientToScreen(&ptClick);
		pPopup.TrackPopupMenu( TPM_LEFTALIGN, ptClick.x, ptClick.y, hwndCtrl );
	}
	else
	{
		VGMFile* pvgmfile = vgmfiles[0];
		ClientToScreen(&ptClick);
		ItemContextMenu(hwndCtrl, ptClick, pvgmfile);
	}

	return NULL;
}