void CClosableTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CRect rect(lpDIS->rcItem);
	int nTabIndex = lpDIS->itemID;
	if (nTabIndex < 0)
		return;

	TCHAR szLabel[256];
	TC_ITEM tci;
	tci.mask = TCIF_TEXT | TCIF_IMAGE | TCIF_STATE;
	tci.pszText = szLabel;
	tci.cchTextMax = _countof(szLabel);
	tci.dwStateMask = TCIS_HIGHLIGHTED;
	if (!GetItem(nTabIndex, &tci))
		return;
	szLabel[_countof(szLabel) - 1] = _T('\0');
	//TRACE("CClosableTabCtrl::DrawItem: item=%u, state=%08x, color=%08x, rc=%3d,%3d,%3dx%3d\n", nTabIndex, tci.dwState, GetTextColor(lpDIS->hDC), lpDIS->rcItem.left, lpDIS->rcItem.top, lpDIS->rcItem.right - lpDIS->rcItem.left, lpDIS->rcItem.bottom - lpDIS->rcItem.top);

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	if (!pDC)
		return;

	CRect rcFullItem(lpDIS->rcItem);
	bool bSelected = (lpDIS->itemState & ODS_SELECTED) != 0;

	///////////////////////////////////////////////////////////////////////////////////////
	// Adding support for XP Styles (Vista Themes) for owner drawn tab controls simply
	// does *not* work under Vista. Maybe it works under XP (did not try), but that is
	// meaningless because under XP a owner drawn tab control is already rendered *with*
	// the proper XP Styles. So, for XP there is no need to care about the theme API at all.
	//
	// However, under Vista, a tab control which has the TCS_OWNERDRAWFIXED
	// style gets additional 3D-borders which are applied by Vista *after* WM_DRAWITEM
	// was processed. Thus, there is no known workaround available to prevent Vista from
	// adding those old fashioned 3D-borders. We can render the tab control items within
	// the WM_DRAWITEM handler in whatever style we want, but Vista will in each case
	// overwrite the borders of each tab control item with old fashioned 3D-borders...
	//
	// To complete this experience, tab controls also do not support NMCUSTOMDRAW. So, the
	// only known way to customize a tab control is by using TCS_OWNERDRAWFIXED which does
	// however not work properly under Vista.
	//
	// The "solution" which is currently implemented to prevent Vista from drawing those
	// 3D-borders is by using "ExcludeClipRect" to reduce the drawing area which is used
	// by Windows after WM_DRAWITEM was processed. This "solution" is very sensitive to
	// the used rectangles and offsets in general. Incrementing/Decrementing one of the
	// "rcItem", "rcFullItem", etc. rectangles makes the entire "solution" flawed again
	// because some borders would become visible again.
	//
	HTHEME hTheme = NULL;
	int iPartId = TABP_TABITEM;
	int iStateId = TIS_NORMAL;
	bool bVistaHotTracked = false;
	bool bVistaThemeActive = theApp.IsVistaThemeActive();
	if (bVistaThemeActive)
	{
		// To determine if the current item is in 'hot tracking' mode, we need to evaluate
		// the current foreground color - there is no flag which would indicate this state 
		// more safely. This applies only for Vista and for tab controls which have the
		// TCS_OWNERDRAWFIXED style.
		bVistaHotTracked = pDC->GetTextColor() == GetSysColor(COLOR_HOTLIGHT);

		hTheme = OpenThemeData(m_hWnd, L"TAB");
		if (hTheme)
		{
			if (bSelected) {
				// get the real tab item rect
				rcFullItem.left += 1;
				rcFullItem.right -= 1;
				rcFullItem.bottom -= 1;
			}
			else
				rcFullItem.InflateRect(2, 2); // get the real tab item rect

			CRect rcBk(rcFullItem);
			if (bSelected)
			{
				iStateId = TTIS_SELECTED;
				if (nTabIndex == 0) {
					// First item
					if (nTabIndex == GetItemCount() - 1)
						iPartId = TABP_TOPTABITEMBOTHEDGE; // First & Last item
					else
						iPartId = TABP_TOPTABITEMLEFTEDGE;
				}
				else if (nTabIndex == GetItemCount() - 1) {
					// Last item
					iPartId = TABP_TOPTABITEMRIGHTEDGE;
				}
				else {
					iPartId = TABP_TOPTABITEM;
				}
			}
			else
			{
				rcBk.top += 2;
				iStateId = bVistaHotTracked ? TIS_HOT : TIS_NORMAL;
				if (nTabIndex == 0) {
					// First item
					if (nTabIndex == GetItemCount() - 1)
						iPartId = TABP_TABITEMBOTHEDGE; // First & Last item
					else
						iPartId = TABP_TABITEMLEFTEDGE;
				}
				else if (nTabIndex == GetItemCount() - 1) {
					// Last item
					iPartId = TABP_TABITEMRIGHTEDGE;
				}
				else {
					iPartId = TABP_TABITEM;
				}
			}
			if (IsThemeBackgroundPartiallyTransparent(hTheme, iPartId, iStateId))
				DrawThemeParentBackground(m_hWnd, *pDC, &rcFullItem);
			DrawThemeBackground(hTheme, *pDC, iPartId, iStateId, &rcBk, NULL);
		}
	}

	// Following background clearing is needed for:
	//	WinXP/Vista (when used without an application theme)
	//	Vista (when used with an application theme but without a theme for the tab control)
	if (   (!IsThemeActive() || !IsAppThemed())
		|| (hTheme == NULL && bVistaThemeActive) )
		pDC->FillSolidRect(&lpDIS->rcItem, GetSysColor(COLOR_BTNFACE));

	int iOldBkMode = pDC->SetBkMode(TRANSPARENT);

	// Draw image on left side
	CImageList *piml = GetImageList();
	if (tci.iImage >= 0 && piml && piml->m_hImageList)
	{
		IMAGEINFO ii;
		piml->GetImageInfo(0, &ii);
		rect.left += bSelected ? 8 : 4;
		piml->Draw(pDC, tci.iImage, CPoint(rect.left, rect.top + 2), ILD_TRANSPARENT);
		rect.left += (ii.rcImage.right - ii.rcImage.left);
		if (!bSelected)
			rect.left += 4;
	}

	bool bCloseable = m_bCloseable;
	if (bCloseable && GetParent()->SendMessage(UM_QUERYTAB, nTabIndex))
		bCloseable = false;

	// Draw 'Close button' at right side
	if (bCloseable && m_ImgLstCloseButton.m_hImageList)
	{
		CRect rcCloseButton;
		GetCloseButtonRect(nTabIndex, rect, rcCloseButton, bSelected, bVistaThemeActive);

		HTHEME hThemeNC = bVistaThemeActive ? OpenThemeData(m_hWnd, _T("WINDOW")) : NULL;
		if (hThemeNC) {
			// Possible "Close" parts: WP_CLOSEBUTTON, WP_SMALLCLOSEBUTTON, WP_MDICLOSEBUTTON
			int iPartId = WP_SMALLCLOSEBUTTON;
			int iStateId = (bSelected || bVistaHotTracked) ? CBS_NORMAL : CBS_DISABLED;
			if (IsThemeBackgroundPartiallyTransparent(hTheme, iPartId, iStateId))
				DrawThemeParentBackground(m_hWnd, *pDC, &rcCloseButton);
			DrawThemeBackground(hThemeNC, *pDC, iPartId, iStateId, rcCloseButton, NULL);
			CloseThemeData(hThemeNC);
		}
		else {
			m_ImgLstCloseButton.Draw(pDC, (bSelected || bVistaHotTracked) ? 0 : 1, rcCloseButton.TopLeft(), ILD_TRANSPARENT);
		}

		rect.right = rcCloseButton.left - 2;
		if (bSelected)
			rect.left += hTheme ? 4 : 2;
	}

	COLORREF crOldColor = CLR_NONE;
	if (tci.dwState & TCIS_HIGHLIGHTED)
		crOldColor = pDC->SetTextColor(RGB(192, 0, 0));
	else if (bVistaHotTracked)
		crOldColor = pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT));

	rect.top += bSelected ? 4 : 3;
	// Vista: Tab control has troubles with determining the width of a tab if the
	// label contains one '&' character. To get around this, we use the old code which
	// replaces one '&' character with two '&' characters and we do not specify DT_NOPREFIX
	// here when drawing the text.
	//
	// Vista: "DrawThemeText" can not be used in case we need a certain foreground color. Thus we always us
	// "DrawText" to always get the same font and metrics (just for safety).
	pDC->DrawText(szLabel, rect, DT_SINGLELINE | DT_TOP | DT_CENTER /*| DT_NOPREFIX*/);

	if (crOldColor != CLR_NONE)
		pDC->SetTextColor(crOldColor);
	pDC->SetBkMode(iOldBkMode);

	if (hTheme)
	{
		CRect rcClip(rcFullItem);
		if (bSelected) {
			rcClip.left -= 2 + 1;
			rcClip.right += 2 + 1;
		}
		else {
			rcClip.top += 2;
		}
		pDC->ExcludeClipRect(&rcClip);
		CloseThemeData(hTheme);
	}
}