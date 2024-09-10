void CDlgWingspanAdjacancyConstraints::RefreshLayout( int cx /*= -1*/, int cy /*= -1*/ )
{
	if (cx == -1 && cy == -1)
	{
		CRect rectClient;
		GetClientRect(&rectClient);
		cx = rectClient.Width();
		cy = rectClient.Height();
	}

	CWnd* pWndSave = GetDlgItem(IDC_BUTTON_SAVE);
	CWnd* pWndOK = GetDlgItem(IDOK);
	CWnd* pWndCancel = GetDlgItem(IDCANCEL);
	if (pWndSave == NULL || pWndOK == NULL || pWndCancel == NULL)
		return;

	CRect rcCancel;
	pWndCancel->GetClientRect(&rcCancel);
	pWndCancel->MoveWindow(cx - rcCancel.Width() - 10,
		cy - rcCancel.Height() - 10, 
		rcCancel.Width(), 
		rcCancel.Height());

	CRect rcOK;
	pWndOK->GetClientRect(&rcOK);
	pWndOK->MoveWindow(cx - rcCancel.Width() - rcOK.Width() - 20,
		cy - rcOK.Height() - 10, 
		rcOK.Width(),
		rcOK.Height());

	CRect rcSave;
	pWndSave->GetClientRect(&rcSave);
	pWndSave->MoveWindow(cx - rcCancel.Width() - rcOK.Width() - rcSave.Width() - 30,
		cy - rcSave.Height() - 10, 
		rcSave.Width(),
		rcSave.Height());

	CWnd* pGroupBox = GetDlgItem(IDC_STATIC_FRAME);
	if (pGroupBox == NULL)
		return;

	pGroupBox->MoveWindow(10, 5, cx - 20, cy - rcOK.Height() - 27);

	m_wndListCtrl.MoveWindow(10, 35, cx - 20, cy - rcOK.Height() - 57);

	if (!::IsWindow(m_wndToolBar.m_hWnd))
		return;
	m_wndToolBar.MoveWindow(11, 11, cx - 25, 22);

	Invalidate();
}