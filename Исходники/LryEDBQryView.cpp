void CLryEDBQryView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CMenu Menu;	
	CMenu *pMenu;
	Menu.LoadMenu(IDR_POPUP_E_DATABASE);
	pMenu = Menu.GetSubMenu(0);

	if(pReportdlg.m_hWnd==NULL)
	{
		pMenu->EnableMenuItem(ID_FILE_PRINT_PREVIEW,MF_DISABLED|MF_GRAYED|MF_BYCOMMAND);
		pMenu->EnableMenuItem(ID_PRINT_REPORT_SETTING,MF_DISABLED|MF_GRAYED|MF_BYCOMMAND);
		pMenu->EnableMenuItem(ID_FILE_PRINT_PREVIEW,MF_DISABLED|MF_GRAYED|MF_BYCOMMAND);	
	} 
	CRect rect;
	CPoint pt;
	GetClientRect(&rect);
	pt = point;
	ScreenToClient(&pt);

	CWnd *pOwner = this;

	while(pOwner->GetStyle()&WS_CHILD)
	{
		pOwner = pOwner->GetParent();
	}

	if(PtInRect(rect,pt))
		pMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pOwner); 
		//弹出自己的右键菜单
	else
		CXTListView::OnContextMenu(pWnd,point); //弹出默认的滚动条菜单		
}