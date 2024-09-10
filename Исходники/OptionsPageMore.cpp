INT_PTR CALLBACK OptionsPageMore::aboutBoxDialogProc(
	HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_INITDIALOG)
	{
		int iconSize = LOWORD(GetDialogBaseUnits()) * 24 / 4;
		auto appIcon = LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_A),
			IMAGE_ICON, iconSize, iconSize, LR_DEFAULTCOLOR);
		Static_SetIcon(GetDlgItem(hwnd, IDC_ABOUT_ICON), appIcon);
		SetDlgItemText(hwnd, IDC_ABOUT_VERSION, L"Version: " APP_VERSION);
		SetDlgItemText(hwnd, IDC_ABOUT_DATE, L"Compiled on: " APP_DATE);
		return TRUE;
	}
	if (uMsg == WM_NOTIFY)
	{
		auto pHdr = (const PNMLINK) lParam;
		if (pHdr->hdr.code == NM_CLICK || pHdr->hdr.code == NM_RETURN)
		{
			ShellExecute(NULL, L"open", pHdr->item.szUrl, NULL, NULL, SW_SHOW);
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	else if (uMsg == WM_COMMAND && HIWORD(wParam) == BN_CLICKED)
	{
		DestroyIcon(Static_GetIcon(GetDlgItem(hwnd, IDC_ABOUT_ICON), 0));
		EndDialog(hwnd, IDOK);
		return TRUE;
	}
	else {
		return FALSE;
	}
}