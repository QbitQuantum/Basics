BOOL CBlendSelectWnd::Create(CRect rc, CWnd* pParentWnd, UINT nID, DWORD dwStyle)
{
	//if hwnd already exist - return TRUE;
	if (GetSafeHwnd())
		return TRUE;

	m_dwWidth = rc.Width();
	m_dwHeight = rc.Height();

	int nGap = 4;

	m_rcBtnClose.right = m_dwWidth - nGap;
	m_rcBtnClose.top = nGap;
	m_rcBtnClose.left = m_rcBtnClose.right - 16;
	m_rcBtnClose.bottom = m_rcBtnClose.top + 16;

	DWORD dwStyleEx = WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED;

	DWORD dwLayout;
	GetProcessDefaultLayout(&dwLayout);
	if (LAYOUT_RTL & dwLayout) {
		dwStyleEx |= WS_EX_LAYOUTRTL;
	}

	LPCTSTR pszClassName = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW);

	if (!CreateEx(dwStyleEx, pszClassName, NULL, dwStyle, rc, pParentWnd, nID))
		return FALSE;

	SetOwner(pParentWnd);

	return TRUE;
}