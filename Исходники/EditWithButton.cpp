void CEditWithButton_Base::DrawButton(CRect rectButton)
{
	CWindowDC dc(this);

	HTHEME hButtonTheme = OpenThemeData(m_hWnd, _T("Button"));
	if (hButtonTheme)
	{
		int ButtonState = GetButtonThemeState();

		// If necessary, first fill with the edit control's background color.
		if (IsThemeBackgroundPartiallyTransparent(hButtonTheme, BP_PUSHBUTTON, ButtonState))
		{
			HTHEME hEditTheme = OpenThemeDataEx(m_hWnd, _T("Edit"), OTD_NONCLIENT);

			COLORREF BgColor = RGB(0, 0, 0);
			BgColor = GetThemeSysColor(hEditTheme, (GetStyle() & (ES_READONLY | WS_DISABLED)) ? COLOR_3DFACE : COLOR_WINDOW);
			dc.FillSolidRect(rectButton, BgColor);

			CloseThemeData(hEditTheme);
		}

		DrawThemeBackground(hButtonTheme, dc, BP_PUSHBUTTON, ButtonState, rectButton, NULL);

		DrawButtonContent(dc, rectButton, hButtonTheme);

		CloseThemeData(hButtonTheme);
	}
	else
	{
		UINT uState = DFCS_BUTTONPUSH;
		if (GetStyle() & (ES_READONLY | WS_DISABLED))
			uState |= DFCS_INACTIVE;
		else if (m_IsButtonPressed)
			uState |= DFCS_PUSHED;
		dc.DrawFrameControl(rectButton, DFC_BUTTON, uState);

		// If the button is in a pressed state, then contents should move slightly as part of the "push" effect.
		if (m_IsButtonPressed)
			rectButton.OffsetRect(1, 1);

		DrawButtonContent(dc, rectButton, NULL);
	}
}