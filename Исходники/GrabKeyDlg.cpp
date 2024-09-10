void CGrabKeyDlg::OnDestroy() {
	for (int i = 0xc1; i <= 0xcf; i++) {
		UnregisterHotKey(GetSafeHwnd(), i);
	}

	CDialog::OnDestroy();
}