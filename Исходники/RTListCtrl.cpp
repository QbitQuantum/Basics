void CRTListCtrl::OnContextMenu(CWnd *, CPoint point)
{
	CMenu menu;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

		if (point.x == -1 && point.y == -1){
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5,5);
		}
		else
		{
			ClientToScreen(&point);//.Offset(50, 146);
		}
	
		menu.DestroyMenu();
		VERIFY(menu.LoadMenu(IDR_POPUP_RT_SET));


//		InitMenu(0 ,type, del_flag);

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		//pPopup->EnableMenuItem(AFX_ID_BLOWUP,MF_GRAYED);

	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,pWndPopupOwner);

}