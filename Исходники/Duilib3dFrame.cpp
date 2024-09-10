LRESULT CDuilib3dFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	styleValue &= ~WS_THICKFRAME;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	HMENU hMenu = GetSystemMenu(m_hWnd,FALSE);
	if (hMenu != NULL)
	{
		DeleteMenu(hMenu,SC_MAXIMIZE,MF_BYCOMMAND);
	}

	//根据skin.xml创建程序界面
	m_PaintManager.Init(m_hWnd);

	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("skin.xml"), (UINT)0,  &cb, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");

	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);

	HICON hIcon = LoadIcon((HINSTANCE)GetWindowLong(m_hWnd,GWL_HINSTANCE),MAKEINTRESOURCE(IDI_ICON));
	m_tray.Create(m_hWnd,WM_USER+1021,_T("360安全卫士"),hIcon,NULL);

	return 0;
}