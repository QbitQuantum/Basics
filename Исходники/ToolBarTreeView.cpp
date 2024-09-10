void CToolBarTreeView::Draw()
{
	const int& cx = m_mdc.cx;
	const int& cy = m_mdc.cy;

	if (IsAppThemed())
	{
		HTHEME hTheme = OpenThemeData(m_hWnd, L"TREEVIEW");
		ASSERT(hTheme);
		RECT rc = {0, 0, cx, cy};
		DrawThemeBackground(hTheme, m_mdc, LBCP_BORDER_NOSCROLL, LBPSN_NORMAL, &rc, NULL);
		CloseThemeData(hTheme);

		// TODO: detect size of border (check for high DPI)
		DrawRect(m_mdc, 1, 1, cx - 2, SCY(24), GetSysColor(COLOR_BTNFACE), 96);
		DrawRect(m_mdc, 1, 1 + SCY(24) - 1, cx - 2, 1, GetSysColor(COLOR_BTNFACE), 192);
	}
	else
	{
		RECT rc = {0, 0, cx, cy};
		FillSolidRect(m_mdc, &rc, GetSysColor(COLOR_WINDOW));
		FillSolidRect(m_mdc, 1, 1, cx - 2, SCY(24), GetSysColor(COLOR_BTNFACE));
		DrawEdge(m_mdc, &rc, EDGE_SUNKEN, BF_RECT);
	}
}