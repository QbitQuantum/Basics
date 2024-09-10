void CEditViewDlg::OnSize(UINT nType, int cx, int cy) {
	CDialog::OnSize(nType, cx, cy);
	if (GetSafeHwnd() == NULL) {
		return;
	}
	CRect rect, crect;
	GetClientRect(rect);
	CWnd *wnd = GetDlgItem(IDC_BUTTON_OPEN);
	if (wnd == NULL || (wnd && wnd->GetSafeHwnd() == NULL)) {
		return;
	}
	wnd->GetWindowRect(crect);
	wnd->SetWindowPos(NULL, 4, 4, crect.Width(), crect.Height(), SWP_SHOWWINDOW);
	wnd = GetDlgItem(IDC_BUTTON_SAVE);
	int left = 8 + crect.Width();
	wnd->SetWindowPos(NULL, left, 4, crect.Width(), crect.Height(), SWP_SHOWWINDOW);
	wnd = GetDlgItem(IDOK);
	wnd->SetWindowPos(NULL, rect.Width() - crect.Width() - 4, 4, crect.Width(), crect.Height(), SWP_SHOWWINDOW);
	editInfo.SetWindowPos(NULL, 4, 8 + crect.Height(), rect.Width() - 8, rect.Height() - crect.Height() * 2 - 16, SWP_SHOWWINDOW);
	wnd = GetDlgItem(IDC_BUTTON_GOTO);
	wnd->SetWindowPos(NULL, 4, rect.Height() - 4 - crect.Height(), crect.Width(), crect.Height(), SWP_SHOWWINDOW);
	wnd = GetDlgItem(IDC_EDIT_GOTO);
	wnd->SetWindowPos(NULL, 8 + crect.Width(), rect.Height() - 3 - crect.Height(), crect.Width() + 8, crect.Height() - 3, SWP_SHOWWINDOW);
	wnd = GetDlgItem(IDC_STATIC_LINE);
	wnd->SetWindowPos(NULL, 30 + crect.Width() * 2, rect.Height() - crect.Height(), crect.Width() * 2, crect.Height(), SWP_SHOWWINDOW);
	wnd = GetDlgItem(IDC_EDIT_LINE);
	wnd->SetWindowPos(NULL, 40 + crect.Width() * 3, rect.Height() - crect.Height(), crect.Width() + 8, crect.Height(), SWP_SHOWWINDOW);
}