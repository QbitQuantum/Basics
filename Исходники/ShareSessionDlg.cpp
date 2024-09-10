void CShareSessionDlg::OnNMRClickSessionList(NMHDR* pNMHDR, LRESULT* pResult){

	CPoint cp;
	GetCursorPos(&cp);
	m_list.ScreenToClient(&cp);
	
	CMenu menu;
	menu.LoadMenuW(IDR_SHARELIST_MENU);

	int nItem=m_list.HitTest(cp);
	m_list.ClientToScreen(&cp);

	if(nItem>=0){


		m_list.SetHotItem(nItem);

		CString name=m_list.GetItemText(nItem,1);
		CShareSession* pShareSession=this->GetShareSessionBySharerName(name);
		BOOL bState=pShareSession->bStateOn;
		BOOL bLock=pShareSession->bLockMode;

		CMenu* pMenu=menu.GetSubMenu(0);

		CString sMenuItemText;
		if(bState){
			sMenuItemText.LoadString(IDS_SHARELIST_MENUTEXT_STOPSESSION);
			pMenu->ModifyMenu(0,MF_BYPOSITION,IDM_ITEM_STOP,sMenuItemText/*_T("停止会话")*/);
		}
		else{
			sMenuItemText.LoadString(IDS_SHARELIST_MENUTEXT_STARTSESSION);
			pMenu->ModifyMenu(0,MF_BYPOSITION,IDM_ITEM_START,sMenuItemText/*_T("启动会话")*/);	
		}
		if(bLock){
			pMenu->CheckMenuItem(IDM_ITEM_LOCK,MF_CHECKED);
		}
		else {
			pMenu->CheckMenuItem(IDM_ITEM_LOCK,MF_UNCHECKED);
		}


		pMenu->TrackPopupMenu(0,cp.x,cp.y,this);

	}
	else{
		CMenu* pMenu=menu.GetSubMenu(1);
		pMenu->TrackPopupMenu(0,cp.x,cp.y,this);
	}
}