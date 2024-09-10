BOOL CXTabCtrl::SelectTab(int iIndex)
{
	ASSERT(iIndex < m_arrayStatusTab.GetSize());

	if (GetCurSel() == iIndex)
		return TRUE;

	//** check if the tab is enabled --------
	if (m_arrayStatusTab[iIndex])
	{
		TCITEM item;
		CWnd* pWnd;
		item.mask = TCIF_PARAM;

		GetItem(GetCurSel(), &item);
		pWnd = reinterpret_cast<CWnd*> (item.lParam);
		ASSERT_VALID(pWnd);
		pWnd->ShowWindow(SW_HIDE);

		SetCurSel(iIndex);
		GetItem(iIndex, &item);
		pWnd = reinterpret_cast<CWnd*> (item.lParam);
		ASSERT_VALID(pWnd);
		pWnd->ShowWindow(SW_SHOW);

		return TRUE;
	}

	return FALSE;
}