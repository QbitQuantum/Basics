void CMonitorSessionDlg::OnNMRClickSessionList(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint cp;
	GetCursorPos(&cp);
	m_list.ScreenToClient(&cp);
	
	CMenu menu;
	menu.LoadMenuW(IDR_MONITORLIST_MENU);

	int nItem=m_list.HitTest(cp);
	m_list.ClientToScreen(&cp);

	if(nItem>=0){
		m_list.SetHotItem(nItem);
		CMenu* pMenu=menu.GetSubMenu(0);
		pMenu->TrackPopupMenu(0,cp.x,cp.y,this);

	}
	else{
		CMenu* pMenu=menu.GetSubMenu(1);
		pMenu->TrackPopupMenu(0,cp.x,cp.y,this);
	}


	*pResult = 0;
}