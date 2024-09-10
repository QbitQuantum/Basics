void StormGETURLBox::OnBnClickedAdd()
{	
	CWnd* pwnd = AfxGetMainWnd(); // Pointer to main window
	HWND hWnd = pwnd->GetSafeHwnd();

	CListCtrl* m_FileQueue = (CListCtrl*)pwnd->GetDlgItem(IDC_LIST3);
	CSliderCtrl* m_Connections = (CSliderCtrl*)pwnd->GetDlgItem(IDC_SLIDER1);
	CString FileURLs;

	this->GetDlgItemTextW(IDC_LIST,FileURLs);

	while (!FileURLs.IsEmpty()) {
		LVITEM lvItem;

		int nItem = m_FileQueue->GetItemCount();

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = nItem;
		nItem++;
		lvItem.iSubItem = 0;

		lvItem.pszText = L"Queued";
		nItem = m_FileQueue->InsertItem(&lvItem);

		CString connPos;
		connPos.Format(L"%i", m_Connections->GetPos());

		m_FileQueue->SetItemText(nItem, 1, connPos);
		m_FileQueue->SetItemText(nItem, 2, GetLine(FileURLs));
	}
}