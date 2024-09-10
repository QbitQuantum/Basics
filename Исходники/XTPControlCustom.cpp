CWnd* CXTPControlCustom::FindChildWindow(CXTPCommandBars* pCommandBars, UINT nID)
{
	CWnd* pWndSite = pCommandBars->GetSite();

	if (pWndSite->GetDlgItem(nID) != NULL)
		return pWndSite->GetDlgItem(nID);

	for (int i = 0; i < pCommandBars->GetCount(); i++)
	{
		CXTPToolBar* pToolBar = pCommandBars->GetAt(i);

		if (pToolBar->GetDlgItem(nID) != NULL)
			return pToolBar->GetDlgItem(nID);
	}


	return NULL;
}