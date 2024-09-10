LRESULT CSaveArgs::OnNameChanged(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CEdit name = GetDlgItem(IDC_FILENAME);
	CButton ok = GetDlgItem(IDOK);
	ok.EnableWindow(name.GetWindowTextLength() > 0);
	return 0;
}