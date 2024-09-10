void CFileAndFolder::resizeControls() {
	if (!IsWindow(m_hWnd)) return;

	CRect crect,trect,okrect,cancelrect,msgrect,refresh;
	GetClientRect(crect);
	if (!IsWindow(m_Tree.m_hWnd)) return;
	m_Tree.GetClientRect(trect);
	CWnd * wok = GetDlgItem(IDOK);
	CWnd * c*k = GetDlgItem(IDCANCEL);

	m_Msg.GetClientRect(msgrect);
	CWnd * wnd = GetDlgItem(IDC_REFRESH_DRIVES);
	wnd->GetClientRect(refresh);

	wok->GetClientRect(okrect);
	int okh = okrect.Height();
	int okw = okrect.Width();



	trect = crect;
	trect.top = trect.top + (msgrect.Height() + 10 + refresh.Height() + 10);
	trect.bottom -= (okh + 10);
	m_Tree.MoveWindow(trect,TRUE);

	int okx = ((crect.Width() - (okw * 3)) / 2);

	okrect.left = okx;
	okrect.right = okrect.left + okw;
	okrect.top = trect.bottom  + 5;
	okrect.bottom = okrect.top + okh;
	wok->MoveWindow(okrect,TRUE);

	cancelrect = okrect;
	cancelrect.left = okrect.left + (okrect.Width() * 2);
	cancelrect.right = cancelrect.left + okrect.Width();
	c*k->MoveWindow(cancelrect,TRUE);
}