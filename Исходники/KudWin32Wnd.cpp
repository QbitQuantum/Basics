void KGUIWin32Wnd::InitDraw_Internal()
{
	RECT rcTemp;
	::GetWindowRect(m_hWnd, &rcTemp);
	m_RcWnd = rcTemp;
	OffsetRect(&m_RcWnd, -m_RcWnd.left, -m_RcWnd.top);
	SetRectEmpty(&m_RcMin);
	SetRectEmpty(&m_RcMax);
	SetRectEmpty(&m_RcClose);

	m_RcClose = m_RcWnd;
	m_RcClose.right -= KUDEET_SYS_BUTTON_RIGHT;
	m_RcClose.left = m_RcClose.right - KUDEET_SYS_BUTTON_SIZE;
	m_RcClose.top = KUDEET_TITLE_SIZE / 2 - KUDEET_SYS_BUTTON_SIZE / 2;
	m_RcClose.bottom = m_RcClose.top + KUDEET_SYS_BUTTON_SIZE;
	if (m_bCanMin)
	{
		m_RcMin = m_RcClose;
		m_RcMin.right = m_RcMin.left - KUDEET_SYS_BUTTON_SPACE;
		m_RcMin.left = m_RcMin.right - KUDEET_SYS_BUTTON_SIZE;
	}
}