void MBMessageBoxImpl::resizeControls() {

	CRect okrect,cancelrect,crect,mrect;
	if (!::IsWindow(m_hWnd)) { return; }
	GetClientRect(crect);
	CWnd * wok = GetDlgItem(IDC_MESSAGEBOX_OK);
	if (!wok) { return; }
	CWnd * wc = GetDlgItem(IDC_MESSAGEBOX_CANCEL);
	if (!wc) { return; }
	if (!::IsWindow(wok->m_hWnd)) { return; }
	if (!::IsWindow(wc->m_hWnd)) { return; }
	wok->GetClientRect(okrect);

	wc->GetClientRect(cancelrect);
	int x,y;
	x = (crect.Width() / 2) - (okrect.Width() + 20);
	y = crect.Height() - (okrect.Height() + 10);

	wok->MoveWindow(x,y,okrect.Width(),okrect.Height());

	x = (crect.Width() / 2) + (20);
	wc->MoveWindow(x,y,okrect.Width(),okrect.Height());
	wok->GetWindowRect(okrect);
	ScreenToClient(okrect);

	mrect.left = 10;
	mrect.right = crect.Width() - 10;
	mrect.top = 20;
	mrect.bottom = crect.bottom - (okrect.Height() + 10);
	mrect.bottom = okrect.top - 20;
	m_MessageBox.MoveWindow(mrect);
	m_MessageBox2.MoveWindow(mrect);

	int numlines = m_MessageBox.GetLineCount();

	CRect calcRect;
	CalcMsgRect(calcRect);

	if (calcRect.Height() > mrect.Height()
			|| calcRect.Width() > mrect.Width()) {
		m_MessageBoxPtr = &m_MessageBox;
		m_MessageBox.ShowWindow(SW_NORMAL);
		m_MessageBox2.ShowWindow(SW_HIDE);
	} else {
		m_MessageBoxPtr = &m_MessageBox2;
		m_MessageBox.ShowWindow(SW_HIDE);
		m_MessageBox2.ShowWindow(SW_NORMAL);
	}

}