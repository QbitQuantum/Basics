void EditIconHint_Subclass(HWND hDlg, HWND hRootDlg /*= NULL*/)
{
	if (!hRootDlg)
		hRootDlg = hDlg;

	EnumChildWindows(hDlg, EditIconHint_Enum, (LPARAM)hRootDlg);
}