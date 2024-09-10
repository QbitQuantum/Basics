void CXTPEditListBoxToolBar::OnNcPaint()
{
	CXTPWinThemeWrapper wrpTreeView;
	wrpTreeView.OpenTheme(0, L"LISTBOX");
	if (wrpTreeView.IsAppThemed() && wrpTreeView.IsAppThemeReady() && (GetOwner()->GetExStyle() & WS_EX_CLIENTEDGE))
	{
		CXTPWindowRect rc(this);
		CXTPClientRect rcClient(this);

		COLORREF clr = GetXtremeColor(COLOR_BTNSHADOW);
		if (rc.Width() == rcClient.Width() + 2 &&
			SUCCEEDED(wrpTreeView.GetThemeColor(0, 0, TMT_BORDERCOLOR, &clr)))
		{
			CWindowDC dc(this);

			dc.FillSolidRect(0, 0, rc.Width(), 1, clr);
			dc.FillSolidRect(0, 0, 1, rc.Height(), clr);
			dc.FillSolidRect(rc.Width() - 1, 0, 1, rc.Height(), clr);
			dc.FillSolidRect(1, rc.Height() - 1, rc.Width() - 2, 1, GetXtremeColor(COLOR_3DFACE));
			return;
		}
	}

	Default();
}