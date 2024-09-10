void COpenDlg::AutoCompleteOn(int controlId)
{
	HWND hwnd;
	GetDlgItem(controlId, &hwnd);
	if (hwnd)
		SHAutoComplete(hwnd, SHACF_AUTOSUGGEST_FORCE_ON | SHACF_AUTOAPPEND_FORCE_ON | SHACF_FILESYSTEM);
}