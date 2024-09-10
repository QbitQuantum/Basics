//**********************************************************************
void CBCGPRibbonCustomizeRibbonPage::CreateRibbonTree(CStatic& wndPlaceHolder, CBCGPRibbonTreeCtrl& wndTree)
{
	CRect rectGrid;
	wndPlaceHolder.GetClientRect (&rectGrid);
	wndPlaceHolder.MapWindowPoints (this, &rectGrid);

#ifndef BCGP_EXCLUDE_GRID_CTRL
	wndTree.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);

	wndTree.EnableColumnAutoSize (TRUE);
	wndTree.SetSingleSel ();
	wndTree.EnableGroupByBox (FALSE);
	wndTree.SetReadOnly ();
	wndTree.SetWholeRowSel ();
	wndTree.EnableHeader (FALSE, 0);
	wndTree.EnableGridLines(FALSE);
	wndTree.SetRowMarker(FALSE);

	// Set grid tab order (first):
	wndTree.SetWindowPos (&CWnd::wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

	// Set grid colors
	CBCGPGridColors colors;
	colors.m_LeftOffsetColors.m_clrBackground = globalData.clrWindow;
	colors.m_SelColors.m_clrBackground = ::GetSysColor(COLOR_HIGHLIGHT);
	colors.m_SelColors.m_clrText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
	colors.m_SelColorsInactive.m_clrBackground = ::GetSysColor(COLOR_BTNFACE);
	colors.m_SelColorsInactive.m_clrText = ::GetSysColor(COLOR_BTNTEXT);

	wndTree.SetColorTheme (colors);
	
	wndTree.InsertColumn (0, _T("Name"), 80);
#else
	wndTree.Create(_T("Please un-comment BCGP_EXCLUDE_GRID_CTRL in BCGCBProConfig.h"), WS_CHILD | WS_VISIBLE | WS_BORDER, rectGrid, this);
	wndTree.SetFont(GetFont());
#endif
}