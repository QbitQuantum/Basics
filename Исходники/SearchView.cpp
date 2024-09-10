BOOL CSearchView::GetControlInfo(CWnd* pWnd, CWnd** pSafeWnd, CRect* pRect)
{
	HWND hwd=pWnd->GetSafeHwnd();
	*pSafeWnd = CWnd::FromHandle(hwd);
	CAddNewItem* pDlg = (CAddNewItem*) (*pSafeWnd)->GetParent();
	if (pDlg)
	{
		(*pSafeWnd)->GetWindowRect(*pRect);
		pDlg->ScreenToClient(*pRect);
		return TRUE;
	}
	return FALSE;
}