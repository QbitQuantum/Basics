BOOL CPropPageFrameDefault::OnEraseBkgnd(CDC* pDC)
{
	if (IsAppThemed())
	{
		HTHEME hTheme = OpenThemeData(m_hWnd, L"TREEVIEW");
		if (hTheme)
		{
			CRect	rect;
			GetClientRect(rect);
			DrawThemeBackground(hTheme, pDC->m_hDC, 0, 0, rect, nullptr);
			CloseThemeData(hTheme);
		}
		return TRUE;
	}
	else
	{
		return CWnd::OnEraseBkgnd(pDC);
	}
}