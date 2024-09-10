void CXTPPropertyPage::OnNcPaint()
{
	Default();

	if (!m_pSheet)
		return;

	CWindowDC dc(this);
	CXTPWindowRect rcPage(this);
	rcPage.OffsetRect(-rcPage.TopLeft());

	if (m_pSheet->GetPageBorderStyle() == xtpPageBorderFrame)
	{
		BOOL bFrame = FALSE;
		CXTPWinThemeWrapper wrpTreeView;
		wrpTreeView.OpenTheme(0, L"LISTBOX");
		if (wrpTreeView.IsAppThemed())
		{
			COLORREF clr;
			if (SUCCEEDED(wrpTreeView.GetThemeColor(0, 0, TMT_BORDERCOLOR, &clr)))
			{
				dc.Draw3dRect(rcPage, clr, clr);
				rcPage.DeflateRect(1, 1);
				dc.Draw3dRect(rcPage, GetXtremeColor(COLOR_WINDOW), GetXtremeColor(COLOR_WINDOW));
				rcPage.DeflateRect(1, 1);
				bFrame = TRUE;
			}
		}
		if (!bFrame)
		{
			dc.DrawEdge(rcPage, EDGE_SUNKEN, BF_RECT);
			rcPage.DeflateRect(2, 2);
		}
	}
	else if (m_pSheet->GetPageBorderStyle() == xtpPageBorderBottomLine)
	{
		dc.FillSolidRect(rcPage.left, rcPage.bottom - 2, rcPage.Width(), 1, GetXtremeColor(COLOR_BTNSHADOW));
		dc.FillSolidRect(rcPage.left, rcPage.bottom - 1, rcPage.Width(), 1, GetXtremeColor(COLOR_BTNHIGHLIGHT));
		rcPage.DeflateRect(0, 0, 0, 2);
	}

	if ((GetStyle() & (WS_HSCROLL | WS_VSCROLL)) == (WS_HSCROLL | WS_VSCROLL))
	{
		CRect rcSizeIcon(rcPage.right - GetSystemMetrics(SM_CXVSCROLL),
			rcPage.bottom - GetSystemMetrics(SM_CYHSCROLL), rcPage.right, rcPage.bottom);

		HBRUSH hBrush = m_pSheet->GetNavigator()->GetPageBrush(&dc, this);
		if (hBrush)
		{
			CXTPClientRect rc(this);
			::FillRect(dc, rcSizeIcon, hBrush);
		}
		else
		{
			dc.FillSolidRect(rcSizeIcon, GetXtremeColor(COLOR_3DFACE));
		}

	}
}