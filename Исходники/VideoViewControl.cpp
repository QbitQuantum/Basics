LRESULT CVideoViewControl::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps = { 0 };
	CDCHandle cdc(BeginPaint(&ps));

	if (m_bPlayerStarted && m_strLastErrorMsg.IsEmpty())
	{
		::SendMessage(m_hWndPlayer, WM_PLAYER_UPDATE, 0, 0);
	}
	else
	{
		CRect rect;
		GetClientRect(&rect);

		static DWORD dwBrushColor = 0;
		static DWORD dwTextColor = 0;
		if (!dwBrushColor)
		{
			CComPtr<IThemeColorMap> pThemeColorMap;
			ASSERT_IF_FAILED(m_pTheme->GetColorMap(&pThemeColorMap));
			ASSERT_IF_FAILED(pThemeColorMap->GetColor(Twitter::Metadata::Drawing::BrushBackground, &dwBrushColor));
			ASSERT_IF_FAILED(pThemeColorMap->GetColor(Twitter::Metadata::Drawing::PictureWindowText, &dwTextColor));
		}

		cdc.SetBkMode(TRANSPARENT);
		cdc.SetTextColor(dwTextColor);

		cdc.FillSolidRect(&rect, dwBrushColor);

		CComBSTR str = L"Launching video player...";
		if (!m_strLastErrorMsg.IsEmpty())
			str = m_strLastErrorMsg;

		CSize size;
		CRect rect1 = rect;
		cdc.DrawTextEx(str, str.Length(), &rect1, DT_WORDBREAK | DT_CENTER | DT_CALCRECT, NULL);
		size.cx = rect1.Width();
		size.cy = rect1.Height();

		auto x = (rect.right - rect.left) / 2 - (size.cx / 2);
		auto y = (rect.bottom - rect.top) / 2 - (size.cy / 2);

		CRect rectText(x, y, x + size.cx, y + size.cy);
		DrawRoundedRect(cdc, rectText, false);
		cdc.DrawTextEx(str, str.Length(), &rectText, DT_WORDBREAK | DT_CENTER, NULL);
	}
	EndPaint(&ps);
	return 0;
}