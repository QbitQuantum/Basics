BOOL CResizableSheet::ArrangeLayoutCallback(LayoutInfo &layout)
{
	if (layout.nCallbackID != 1)	// we only added 1 callback
		return CResizableLayout::ArrangeLayoutCallback(layout);

	// set layout info for active page
	layout.hWnd = GetActivePage()->GetSafeHwnd();

	// set margins
	if (IsWizard())	// wizard mode
	{
		// use pre-calculated margins
		layout.sizeMarginTL = m_sizePageTL;
		layout.sizeMarginBR = m_sizePageBR;
	}
	else	// tab mode
	{
		CRect rectPage, rectSheet;
		GetTotalClientRect(&rectSheet);

		CTabCtrl* pTab = GetTabControl();
		pTab->GetWindowRect(&rectPage);
		pTab->AdjustRect(FALSE, &rectPage);
		ScreenToClient(&rectPage);

		// use tab control
		layout.sizeMarginTL = rectPage.TopLeft() - rectSheet.TopLeft();
		layout.sizeMarginBR = rectPage.BottomRight() - rectSheet.BottomRight();
	}

	// set anchor types
	layout.sizeTypeTL = TOP_LEFT;
	layout.sizeTypeBR = BOTTOM_RIGHT;

	// use this layout info
	return TRUE;
}