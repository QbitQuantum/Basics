BOOL CSkinScrollWnd::SkinWindow(CWnd* pWnd, HBITMAP hBmpScroll)
{
	ASSERT(m_hWnd == NULL);
	m_hBmpScroll = hBmpScroll;

	BITMAP bm;
	GetObject(hBmpScroll, sizeof(bm), &bm);
	m_nScrollWid = bm.bmWidth/9;

	CWnd* pParent = pWnd->GetParent();
	ASSERT(pParent);
	RECT rcFrm, rcWnd;
	pWnd->GetWindowRect(&rcFrm);
	pParent->ScreenToClient(&rcFrm);
	rcWnd = rcFrm;
	OffsetRect(&rcWnd, -rcWnd.left, -rcWnd.top);

	UINT uID = pWnd->GetDlgCtrlID();

	DWORD dwStyle = pWnd->GetStyle();
	DWORD dwFrmStyle = WS_CHILD | SS_NOTIFY;
	DWORD dwFrmStyleEx = 0;

	if (dwStyle&WS_VISIBLE) dwFrmStyle |= WS_VISIBLE;
	if (dwStyle&WS_BORDER)
	{
		dwFrmStyle |= WS_BORDER;
		pWnd->ModifyStyle(WS_BORDER, 0);
		int nBorder = GetSystemMetrics(SM_CXBORDER);
		rcWnd.right -= nBorder * 2;
		rcWnd.bottom -= nBorder * 2;
	}
	DWORD dwExStyle = pWnd->GetExStyle();
	if (dwExStyle&WS_EX_CLIENTEDGE)
	{
		pWnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
		int nBorder = GetSystemMetrics(SM_CXEDGE);
		rcWnd.right -= nBorder * 2;
		rcWnd.bottom -= nBorder * 2;
		dwFrmStyleEx |= WS_EX_CLIENTEDGE;
	}

	this->CreateEx(dwFrmStyleEx, AfxRegisterWndClass(NULL), "SkinScrollBarFrame",
		dwFrmStyle, rcFrm, pParent, uID);
	
	m_WndLimit.Create(NULL, "LIMIT", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 200);

	m_sbHorz.Create(WS_CHILD, CRect(0, 0, 0, 0), this, 100);
	m_sbVert.Create(WS_CHILD | SBS_VERT, CRect(0, 0, 0, 0), this, 101);
	m_sbHorz.SetBitmap(hBmpScroll);
	m_sbVert.SetBitmap(hBmpScroll);

	pWnd->SetParent(&m_WndLimit);
	SetWindowLong(pWnd->m_hWnd, GWL_USERDATA, (LONG)this);/*
	m_funOldProc = (WNDPROC)SetWindowLong(pWnd->m_hWnd, GWL_WNDPROC, (LONG)ScrollHookWndProc);*/

	SetTimer(TIMER_UPDATE, 500, NULL);
	return TRUE;
}