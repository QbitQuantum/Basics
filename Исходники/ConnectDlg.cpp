// 리스트박스에서 오른쪽버튼눌렀을시
void CConnectDlg::OnRclickListServer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(this->m_nClient == 0){	// 클라이언트 선택시에만
		NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
		int intNum = pNMListView->iItem;
		/**
		if(intNum == -1){
			return;
		}
		**/
		m_nListIndex = intNum;	// 현재 선택되었다면 현재의 위치저장

		// TrackPopupMenu
		CMenu obMenu;
		obMenu.LoadMenu(IDR_MENU_SERVER_LIBRARY);
		CMenu *pPopupMenu = obMenu.GetSubMenu(0);
		ASSERT(pPopupMenu);
		CPoint obCursorPoint = (0, 0);
		GetCursorPos(&obCursorPoint);
		if(0 >= m_listServer.GetSelectedCount()){
			pPopupMenu->EnableMenuItem(ID_SERVER_LIBRARY_DELETE, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		}else{
			pPopupMenu->EnableMenuItem(ID_SERVER_LIBRARY_DELETE, MF_BYCOMMAND | MF_ENABLED);
		}
		pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, obCursorPoint.x, obCursorPoint.y, this);
		
	}
	*pResult = 0;
}