int printer(void *dlg, int argc, char **argv, char**azColName) {
	int i, offset;
	wchar_t msg[512];
	memset(msg, 0, 512);
	Cexcxx_wce_sqlDlg *dialog = (Cexcxx_wce_sqlDlg *)dlg;
	for (i = 0; i < argc; i++) {
		dialog->GetDlgItemText(IDC_TEXT_OUT, msg, 512);
		offset = wcslen(msg);
		StringCbPrintfW(msg + offset, 512 - offset,
		    _T("%hs%hs = %hs%hs"), i == 0 ? "" : ", ", azColName[i], 
		    argv[i] ? argv[i] : "NULL", (i + 1 == argc) ? "\r\n" : "");
		dialog->SetDlgItemText(IDC_TEXT_OUT, msg);
	}
	return (0);
}