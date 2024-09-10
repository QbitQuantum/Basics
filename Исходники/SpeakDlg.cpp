void CSpeakDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (::IsWindow(m_wndSpeak.GetSafeHwnd())) {
		CRect rcSpeakWnd;
		m_wndSpeak.GetWindowRect(&rcSpeakWnd);
		ScreenToClient(&rcSpeakWnd);

		rcSpeakWnd.right = cx;
		rcSpeakWnd.bottom = cy;
		m_wndSpeak.MoveWindow(rcSpeakWnd);
	}
	
	CWnd* pBtn = GetDlgItem(ID_BTN_OK);
	if (pBtn && ::IsWindow(pBtn->GetSafeHwnd()))
	{
		CRect rcBtn;
		pBtn->GetWindowRect(&rcBtn);
		ScreenToClient(&rcBtn);
		int nWidth = rcBtn.Width();

		rcBtn.right = cx - m_nBtnHMargin;
		rcBtn.left = rcBtn.right - nWidth;
		
		pBtn->MoveWindow(rcBtn);
	}
}