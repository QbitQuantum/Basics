void CUIDialog::windowGetText(HWND hDlg, int controlId, std::string &text)
{
	text.resize(SendDlgItemMessageA(hDlg, controlId, WM_GETTEXTLENGTH, 0,
		0));
	SendDlgItemMessageA(hDlg, controlId, WM_GETTEXT,
		(WPARAM)text.size() + 1, (LPARAM)&text[0]);
}