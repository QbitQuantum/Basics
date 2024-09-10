void CViewStatistics::SizePropSheet(CWnd* pParent, CPropertySheet* pPSheet, CRect rcNewPos)
{
	ASSERT_VALID( pParent );
	ASSERT_VALID( pPSheet );

	CTabCtrl* pTabCtrl = pPSheet->GetTabControl();
	ASSERT(pTabCtrl != NULL);

	CRect rcTabCtrl;
	pTabCtrl->GetWindowRect(&rcTabCtrl);
	pParent->ScreenToClient(&rcTabCtrl);

	CRect rcPSheet;
	pPSheet->GetWindowRect(&rcPSheet);
	pParent->ScreenToClient(&rcPSheet);

	int dcx = rcPSheet.Width() - rcTabCtrl.Width();
	int dcy = rcPSheet.Height() - rcTabCtrl.Height();

	pPSheet->MoveWindow(rcNewPos.left, rcNewPos.top, rcNewPos.Width(), rcNewPos.Height());

	pTabCtrl->SetWindowPos(NULL, 0, 0, rcNewPos.Width() - dcx, rcNewPos.Height() - dcy, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

	int nCurrentPage = pPSheet->GetActiveIndex();
	//for(int i = 0; i < pPSheet->GetPageCount(); ++i)
	//	pPSheet->SetActivePage(i);

	pPSheet->SetActivePage(nCurrentPage);
}