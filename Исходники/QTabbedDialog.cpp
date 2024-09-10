//-----------------------------------------------------------------------------/
void CQTabbedDialog::MoveDlgSheet(CPropertySheet* pSheet, CRect rcNewPos)
{
	TRACE("CQTabbedDialog::MoveDlgSheet(1)\n");
	ASSERT_VALID(pSheet);

	// 0 - get the currently active page and set redraw to false.  This
	// will keep the dialog box from flashing when it's resized
	int nCurrentPage = pSheet->GetActiveIndex();
	pSheet->SetRedraw(FALSE);

	// 1 - Get current coordinates of tab control
	// and property sheet window
	CTabCtrl* pTabCtrl = pSheet->GetTabControl();
	ASSERT(pTabCtrl != NULL);

	CRect rcTabCtrl;
	pTabCtrl->GetWindowRect(&rcTabCtrl);
	ScreenToClient(&rcTabCtrl);

	CRect rcPSheet;
	pSheet->GetWindowRect(&rcPSheet);
	ScreenToClient(&rcPSheet);

	// 2 - Calculate margin between property sheet
	// and tab control
	int dcx = rcPSheet.Width() - rcTabCtrl.Width();
	int dcy = rcPSheet.Height() - rcTabCtrl.Height();

	// 3 - Move and resize property sheet window
	// (also moves the tab window because it is a child
	// of the property sheet window)
	pSheet->MoveWindow(rcNewPos.left, rcNewPos.top, rcNewPos.Width(), rcNewPos.Height());

	// 4 - Resize tab control window to restore
	// right / bottom margins
	pTabCtrl->SetWindowPos(NULL,
	                       0, 0,
	                       rcNewPos.Width() - dcx, rcNewPos.Height() - dcy, 
	                       SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE );

	// 5 - turn the drawing back on now, and invalidate the whole dialog
	pSheet->SetRedraw(TRUE);
	Invalidate();

	// now reset the active page
	pSheet->SetActivePage(nCurrentPage);
}