LRESULT MagnetDlg::onInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) {
	// zombies.
	SetWindowText(CTSTRING(MAGNET_DLG_TITLE));
	CenterWindow(GetParent());

	// fill in dialog bits
	SetDlgItemText(IDC_MAGNET_HASH, CTSTRING(MAGNET_DLG_HASH));
	SetDlgItemText(IDC_MAGNET_NAME, CTSTRING(MAGNET_DLG_FILE));
	SetDlgItemText(IDC_MAGNET_SIZE, CTSTRING(MAGNET_DLG_SIZE));
	SetDlgItemText(IDC_MAGNET_QUEUE, CTSTRING(MAGNET_DLG_QUEUE));
	SetDlgItemText(IDC_MAGNET_SEARCH, CTSTRING(MAGNET_DLG_SEARCH));
	SetDlgItemText(IDC_MAGNET_NOTHING, CTSTRING(MAGNET_DLG_NOTHING));
	SetDlgItemText(IDC_MAGNET_REMEMBER, CTSTRING(MAGNET_DLG_REMEMBER));
        SetDlgItemText(IDC_MAGNET_SAVEAS, CTSTRING(MAGNET_DLG_SAVEAS)); // !SMT!-UI
#ifdef MAGNET_DIALOG
	if(mSize <= 0 || mFileName.length() <= 0) {
		::ShowWindow(GetDlgItem(IDC_MAGNET_QUEUE), false);
		::ShowWindow(GetDlgItem(IDC_MAGNET_REMEMBER), false);
	}
#else
        ::ShowWindow(GetDlgItem(IDC_MAGNET_REMEMBER), false);
#endif
	SetDlgItemText(IDC_MAGNET_TEXT, CTSTRING(MAGNET_DLG_TEXT_GOOD));

	// file details
	SetDlgItemText(IDC_MAGNET_DISP_HASH, mHash.c_str());

	SetDlgItemText(IDC_MAGNET_DISP_NAME, mFileName.length() > 0 ? mFileName.c_str() : _T("Не известно"));
	char buf[32];
	_i64toa_s(mSize, buf, sizeof(buf), 10);
	SetDlgItemText(IDC_MAGNET_DISP_SIZE, mSize > 0 ? Text::toT(buf).c_str() : _T("Не известен"));
		//search->minFileSize > 0 ? _i64toa(search->minFileSize, buf, 10) : ""

	// radio button
	CheckRadioButton(IDC_MAGNET_QUEUE, IDC_MAGNET_NOTHING, IDC_MAGNET_SEARCH);

	// focus
	GetDlgItem(IDC_MAGNET_SEARCH).SetFocus();

	::EnableWindow(GetDlgItem(IDC_MAGNET_SAVEAS), IsDlgButtonChecked(IDC_MAGNET_QUEUE) == BST_CHECKED); // !SMT!-UI
	::EnableWindow(GetDlgItem(IDC_MAGNET_REMEMBER), FALSE); // !SMT!-UI
	return 0;
}