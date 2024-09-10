void CReBar::Draw()
{
	int cx, cy;
	VERIFY(m_mdc.GetDimensions(&cx, &cy));

	// Draw background

	if (m_bBackgrWinDefault)
	{
		if (IsAppThemed())
		{
			HTHEME hTheme = OpenThemeData(m_hWnd, L"REBAR");
			RECT rc = {0, 0, cx, cy};
			DrawThemeBackground(hTheme, m_mdc, RP_BACKGROUND, 0, &rc, NULL);
			CloseThemeData(hTheme);
		}
		else
		{
			DrawRect(m_mdc, 0, 0, cx, cy, GetSysColor(COLOR_3DFACE));
			DrawRect(m_mdc, 0, cy - SCY(1), cx, SCY(1), GetSysColor(COLOR_3DSHADOW));
		}
	}
	else
	{
		DrawRectGradientV(m_mdc, 0, 0, cx, cy - SCY(1), m_clrBackgrT, m_clrBackgrB);
		DrawRect(m_mdc, 0, cy - SCY(1), cx, SCY(1), m_clrBackgrLine);
	}

	// Draw rounded background and border around search box

	m_sprSearchBox.Draw(m_mdc, cx - SCX(320), SCY(4), SCX(199), SCY(23), true);
	//m_sprSearchBox.Draw(m_mdc, cx - SCX(259), SCY(4), SCX(199), SCY(23), true);

	Invalidate(m_hWnd);
	PostMessage(m_hWnd, WM_PAINT);
}