void WinClass::CreateToolBar(HWND _hMain)
{
	TBBUTTON ToolBtn[8]={
		//bReserved, dwData, fsState, fsStyle, iBitmap, idCommand, iString
		{0,OBJECT,TBSTATE_ENABLED | TBSTATE_CHECKED,TBSTYLE_CHECKGROUP,0,0,0,0},
		{1,TERRAIN,TBSTATE_ENABLED,TBSTYLE_CHECKGROUP,0,0,0,1},
		//{2,12,TBSTATE_ENABLED,TBSTYLE_CHECKGROUP,0,0,0,2},
		//{3,13,TBSTATE_ENABLED,TBSTYLE_CHECKGROUP,0,0,0,3}
	};

	TCHAR *szString=L"TEXTURE\0OBJECT\0";
	
	INITCOMMONCONTROLSEX InitCtrlEx;
	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC = ICC_BAR_CLASSES;

	InitCommonControlsEx(&InitCtrlEx);
	m_WC().m_hToolBar=CreateToolbarEx(_hMain, WS_CHILD | WS_VISIBLE | WS_BORDER,
		//| TBSTYLE_FLAT | TBSTYLE_TOOLTIPS,
		ID_TOOLBAR, 2, m_WC().m_Inst, 0, ToolBtn, 2,
		16,16,16,16,sizeof(TBBUTTON));
	SendMessage(m_WC().m_hToolBar,TB_ADDSTRING,NULL,(LPARAM)szString);
	
	
	TBREPLACEBITMAP rb;
	int bx, by;
	rb.hInstOld = rb.hInstNew = HINST_COMMCTRL;
	bx = 60; by = 0;
	rb.nButtons = 3;
	
	SendMessage(m_WC().m_hToolBar, TB_REPLACEBITMAP, 0, (LPARAM)&rb);
	SendMessage(m_WC().m_hToolBar, TB_SETBITMAPSIZE, 0, (LPARAM)MAKELONG(bx,by));
	SendMessage(m_WC().m_hToolBar,TB_AUTOSIZE,0,0);
}