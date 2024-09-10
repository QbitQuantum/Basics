void CTabCtrlSSL::OnSelChange (NMHDR* pNMHDR, LRESULT* pResult) {
	int nIndex = GetCurSel ();
	if (nIndex == -1)
		return;

	// Show the new page.
    TabDelete tabDelete = m_tabs[nIndex];
    CTabPageSSL* pDialog = tabDelete.pTabPage;

	if (pDialog != NULL) {
		::SetFocus (m_hFocusWnd[nIndex]);
		CRect rect;
		GetClientRect (&rect);
		ResizeDialog (nIndex, rect.Width (), rect.Height ());
		pDialog->ShowWindow (SW_SHOW);
	}

	// Notify derived classes that the selection has changed.
	OnActivatePage (nIndex, m_nPageIDs[nIndex]);
	*pResult = 0;
}