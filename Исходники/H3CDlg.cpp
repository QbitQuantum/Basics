LRESULT CH3CDlg::OnTray(WPARAM wParam,LPARAM lParam)
{
	UINT uID=(UINT) wParam; 
	UINT uMouseMsg=(UINT) lParam; 
	CMenu menu;
	CMenu *pMenu;
	POINT pt;

	if(uMouseMsg==WM_LBUTTONDBLCLK)//如果是左键双击 
	{ 
		switch(uID) 
		{ 
		case IDR_MAINFRAME: 
		case IDI_DISCON:
			if(isShown==false) 
			{
				//显示主窗口 
				//ModifyStyle(WS_POPUP,WS_OVERLAPPEDWINDOW);  
				//ModifyStyleEx(WS_EX_TOOLWINDOW,WS_EX_TOPMOST); 
				ShowDialog();
			} 
			else 
			{
				HideDialog();
			}
			return 0;
			break; 
		default: 
			break; 
		} 
	} 

	if(uMouseMsg==WM_RBUTTONDOWN || uMouseMsg==WM_LBUTTONDOWN)//如果是单击左右键 
	{ 
		switch(uID) 
		{ 
		case IDR_MAINFRAME://如果是我们的图标 
		case IDI_DISCON:
			GetCursorPos(&pt);//取得鼠标位置 
			//执行相应操作 
			menu.LoadMenu(IDR_MENU1); 
			pMenu=menu.GetSubMenu(0); 
			ASSERT(pMenu!=0);
			::SetForegroundWindow(this->m_hWnd);
			pMenu->TrackPopupMenu (0,pt.x,pt.y,this); 
			break; 
		default: 
			break; 
		} 
	}

	return 0;

}