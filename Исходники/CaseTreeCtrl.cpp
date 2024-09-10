void CCaseTreeCtrl::OnContextMenu(CPoint point)
{
	HTREEITEM hTreeItem = NULL;

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项:
		CPoint ptTree = point;
		ScreenToClient(&ptTree);

		UINT flags = 0;
		hTreeItem = HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			SelectItem(hTreeItem);
		}
	}

	SetFocus();

	
	if(hTreeItem)
	{
		IpmiCmdItem* pItem = (IpmiCmdItem*)GetItemData(hTreeItem);

		CMenu menu;
		/*
		if(wcscmp(pItem->m_pName, L"Emmc") == 0)
		{
			if (menu.LoadMenu(IDR_MENU2))
			{
				CMenu* pPopup = menu.GetSubMenu(0);
				ENSURE(pPopup != NULL);

				pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,
									   point.x, point.y,
									   this); // route commands through main window,AfxGetMainWnd()
			}
		}
		else*/
		{
			if (menu.LoadMenu(IDR_MENU1))
			{
				CMenu* pPopup = menu.GetSubMenu(0);
				ENSURE(pPopup != NULL);

				pPopup->EnableMenuItem(ID_STOP, 0);
				pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,
									   point.x, point.y,
									   this); // route commands through main window,AfxGetMainWnd()
			}
		}
	}	
}