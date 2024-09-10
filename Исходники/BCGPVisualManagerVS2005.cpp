void CBCGPVisualManagerVS2005::OnUpdateSystemColors ()
{
	BOOL bDefaultWinXPColors = m_bDefaultWinXPColors;

	m_clrPressedButtonBorder = (COLORREF)-1;

	m_CurrAppTheme = GetStandardWinXPTheme ();

	if (m_CurrAppTheme != WinXpTheme_Silver)
	{
		m_bDefaultWinXPColors = FALSE;
	}

	CBCGPVisualManager2003::OnUpdateSystemColors ();

	if (!bDefaultWinXPColors)
	{
		return;
	}

	COLORREF clrMenuButtonDroppedDown = m_clrBarBkgnd;
	COLORREF clrMenuItemCheckedHighlight = m_clrHighlightDn;

	if (m_hThemeComboBox == NULL ||
		m_pfGetThemeColor == NULL ||
		(*m_pfGetThemeColor) (m_hThemeComboBox, 5, 0, 3801, &m_colorActiveTabBorder) != S_OK)
	{
		m_colorActiveTabBorder = (COLORREF)-1;
	}

	if (globalData.m_nBitsPerPixel > 8 && !globalData.IsHighContastMode ())
	{
		m_clrCustomizeButtonGradientLight = CBCGPDrawManager::SmartMixColors (
			m_clrCustomizeButtonGradientDark,
			globalData.clrBarFace, 1.5, 1, 1);

		if (m_CurrAppTheme == WinXpTheme_Blue ||
			m_CurrAppTheme == WinXpTheme_Olive)
		{
			m_clrToolBarGradientDark = CBCGPDrawManager::PixelAlpha (
				m_clrToolBarGradientDark, 83);

			m_clrToolBarGradientLight = CBCGPDrawManager::SmartMixColors (
				GetBaseThemeColor (), 
				GetThemeColor (m_hThemeWindow, COLOR_WINDOW),
				1., 3, 2);
		}
		else if (!m_bIsStandardWinXPTheme)
		{
			m_clrToolBarGradientLight = CBCGPDrawManager::SmartMixColors (
				m_clrToolBarGradientLight, 
				globalData.clrBarHilite,
				1.05, 1, 1);
		}

		if (m_CurrAppTheme == WinXpTheme_Blue)
		{
			m_clrCustomizeButtonGradientDark = CBCGPDrawManager::PixelAlpha (
				m_clrCustomizeButtonGradientDark, 90);

			m_clrCustomizeButtonGradientLight = CBCGPDrawManager::PixelAlpha (
				m_clrCustomizeButtonGradientLight, 115);

			m_clrToolBarBottomLine = CBCGPDrawManager::PixelAlpha (
				m_clrToolBarBottomLine, 85);
		}
		else if (m_CurrAppTheme == WinXpTheme_Olive)
		{
			m_clrToolBarBottomLine = CBCGPDrawManager::PixelAlpha (
				m_clrToolBarBottomLine, 110);

			m_clrCustomizeButtonGradientDark = m_clrToolBarBottomLine;

			m_clrCustomizeButtonGradientLight = CBCGPDrawManager::PixelAlpha (
				m_clrCustomizeButtonGradientLight, 120);

			m_clrHighlightDn = globalData.clrHilite;

			m_clrHighlight = CBCGPDrawManager::PixelAlpha (
				m_clrHighlightDn, 124);

			m_clrHighlightChecked = CBCGPDrawManager::PixelAlpha (
				GetThemeColor (m_hThemeWindow, 27 /*COLOR_GRADIENTACTIVECAPTION*/), 98);

			m_brHighlight.DeleteObject ();
			m_brHighlightDn.DeleteObject ();

			m_brHighlight.CreateSolidBrush (m_clrHighlight);
			m_brHighlightDn.CreateSolidBrush (m_clrHighlightDn);

			m_brHighlightChecked.DeleteObject ();
			m_brHighlightChecked.CreateSolidBrush (m_clrHighlightChecked);

			m_clrHighlightGradientDark = m_clrHighlightChecked;
			m_clrHighlightGradientLight = CBCGPDrawManager::PixelAlpha (
				m_clrHighlightGradientDark, 120);
		}
		else if (m_CurrAppTheme != WinXpTheme_Silver)
		{
			m_clrToolBarBottomLine = m_clrToolBarGradientDark;
		}

		clrMenuButtonDroppedDown = CBCGPDrawManager::PixelAlpha (
			m_clrBarBkgnd, 107);

		clrMenuItemCheckedHighlight = GetThemeColor (m_hThemeWindow, COLOR_HIGHLIGHT);

		if (m_CurrAppTheme == WinXpTheme_Blue ||
			m_CurrAppTheme == WinXpTheme_Olive)
		{
			m_clrBarGradientLight = CBCGPDrawManager::PixelAlpha (
					m_clrToolBarGradientLight, 95);

			m_clrBarGradientDark = CBCGPDrawManager::PixelAlpha (
				m_clrBarGradientDark, 97);
		}

		m_clrToolbarDisabled = CBCGPDrawManager::SmartMixColors (
			m_clrToolBarGradientDark, m_clrToolBarGradientLight, 
			.92, 1, 2);

		m_clrPressedButtonBorder = CBCGPDrawManager::SmartMixColors (
				m_clrMenuItemBorder, 
				globalData.clrBarDkShadow,
				.8, 1, 2);
	}

	m_brMenuButtonDroppedDown.DeleteObject ();
	m_brMenuButtonDroppedDown.CreateSolidBrush (clrMenuButtonDroppedDown);

	m_brMenuItemCheckedHighlight.DeleteObject ();
	m_brMenuItemCheckedHighlight.CreateSolidBrush (clrMenuItemCheckedHighlight);

	m_penActiveTabBorder.DeleteObject ();

	if (m_colorActiveTabBorder != (COLORREF)-1)
	{
		m_penActiveTabBorder.CreatePen (PS_SOLID, 1, m_colorActiveTabBorder);
	}

	m_bDefaultWinXPColors = bDefaultWinXPColors;

	m_clrInactiveTabText = globalData.clrBtnDkShadow;

	if (globalData.m_nBitsPerPixel > 8 && !globalData.IsHighContastMode ())
	{
		m_penSeparator.DeleteObject ();

		COLORREF clrSeparator = CBCGPDrawManager::PixelAlpha (
			globalData.clrBarFace, 84);

		m_penSeparator.CreatePen (PS_SOLID, 1, clrSeparator);
	}
}