int CShellWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_ShellTreeCtrl.Create(WS_CHILD|WS_VISIBLE|TVS_SHOWSELALWAYS|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT|TVS_TRACKSELECT,
		CRect(0,0,0,0), this, 100);
	m_ShellTreeCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	// bring the tooltips to front
	CWnd* pTT = m_ShellTreeCtrl.FromHandle((HWND) m_ShellTreeCtrl.SendMessage(TVM_GETTOOLTIPS));
    if (pTT != NULL)
		pTT->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0,
			SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);

	if (!m_fType.Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWN|CBS_LOWERCASE, CRect(0,0,0,0), this, ID_SHELLWND_COMBO))
	{
		return -1;      // fail to create
	}
	//m_fType.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	CFont* font = m_ShellTreeCtrl.GetFont();
	m_fType.SetFont(font);
	m_fType.AddString("*.htm;*.html;*.shtm;*.shtml;*.mht;*.txt;");
	m_fType.AddString("*.txt;");
	m_fType.AddString("*.htm;*.html;");
	m_fType.AddString("*.c;*.cpp;*.h;");
	m_fType.AddString("*.bmp;*.jpg;*.gif;*.png;");
	m_fType.AddString("*.*");
	//
	CImageList img;
	m_wndRef.CreateEx(this);
	img.Create(13, 15, ILC_COLORDDB|ILC_MASK, 1, 1);
	HBITMAP hbmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_REFRESH));
	ImageList_AddMasked(img.GetSafeHandle(), hbmp, RGB(255,0,255));
	DeleteObject(hbmp);
	m_wndRef.GetToolBarCtrl().SetImageList(&img);
	img.Detach();

	m_wndRef.ModifyStyle(0, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT|TBSTYLE_TOOLTIPS  );
	m_wndRef.SetButtonInfo(0, IDOK, TBSTYLE_BUTTON, 0);
	m_wndRef.GetToolBarCtrl().GetToolTips()->UpdateTipText(IDS_REFRESH, this, IDOK);

	return 0;
}