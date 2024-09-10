void CWindowListDlg::OnContextMenu(CWnd*, CPoint point) 
{
	CPoint ptClient(point);
	m_ctlWindowList.ScreenToClient(&ptClient);

	TCHITTESTINFO info;
	info.flags = TCHT_ONITEM;
	info.pt = ptClient;

	int nIndex = m_ctlWindowList.HitTest(&info);

	CWnd* pWnd = NULL;
	if (nIndex != -1)
	{
		CMenu menu;
		menu.LoadMenu(IDR_WNDLIST_RCLICK);
		CMenu *pMenu = menu.GetSubMenu(0);
		ASSERT(pMenu != NULL);

		WINDOWPLACEMENT placement = { sizeof(WINDOWPLACEMENT) };
		pWnd = GetWnd(nIndex);
		pWnd->GetWindowPlacement(&placement);

		if (placement.showCmd == SW_HIDE)
		{
			menu.EnableMenuItem(ID_WNDLIST_CLOSE, MF_BYCOMMAND | MF_GRAYED);
		}
		else if (placement.showCmd == SW_SHOWMAXIMIZED)
		{
			menu.EnableMenuItem(ID_WNDLIST_MAX,   MF_BYCOMMAND | MF_GRAYED);
		}
		else if (placement.showCmd == SW_SHOWMINIMIZED)
		{
			menu.EnableMenuItem(ID_WNDLIST_MIN,   MF_BYCOMMAND | MF_GRAYED);
		}
		else if (m_ctlWindowList.GetCurSel() == nIndex)
		{
			menu.EnableMenuItem(ID_WNDLIST_SHOW,  MF_BYCOMMAND | MF_GRAYED);
		}
		pWnd->GetWindowPlacement(&placement);

		int res = pMenu->TrackPopupMenu( (TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD),
					 point.x, point.y, this);

		switch(res)
		{
		case ID_WNDLIST_CLOSE:
			pWnd->PostMessage(WM_CLOSE);
			break;
		case ID_WNDLIST_MAX:
			placement.showCmd = SW_SHOWMAXIMIZED;
			pWnd->SetWindowPlacement(&placement);
			break;
		case ID_WNDLIST_MIN:
			placement.showCmd = SW_SHOWMINIMIZED;
			pWnd->SetWindowPlacement(&placement);
			break;
		case ID_WNDLIST_SHOW:
			pWnd->ShowWindow(SW_SHOWNORMAL);
			pWnd->BringWindowToTop();
			break;
		}
	}
}