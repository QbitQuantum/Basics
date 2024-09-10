void ContainerNode::AddTooltip(HWND hChild, HINSTANCE hInstance, std::string szTip) {
	if (!m_hTooltipWnd)
		return;
	TOOLINFOA ti;
	ZeroMemory(&ti,sizeof(TOOLINFOA));
	ti.cbSize=sizeof(TOOLINFOA);
	ti.uFlags=TTF_SUBCLASS;
	ti.hinst=hInstance;
	ti.uId=GetNextFreeCommand();
	ti.lpszText=(LPSTR)szTip.c_str();
	char szClassName[64];
	if (!GetClassNameA(hChild,szClassName,64))
		strcpy(szClassName,"");
	if (strcmpi(szClassName,"STATIC")==0 && GetPropA(hChild,"OriginalStaticProc")==0) {
		SetPropA(hChild,"OriginalStaticProc",(HANDLE)SetWindowLong(hChild,GWL_WNDPROC,(LONG)StaticHookProc));
	}

	ti.hwnd=hChild;
	RECT rcClient;
	GetClientRect(hChild,&rcClient);
	CopyRect(&ti.rect,&rcClient);
	SendMessage(m_hTooltipWnd,TTM_ADDTOOLA,0,(WPARAM)&ti);
}