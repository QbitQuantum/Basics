static BOOL CALLBACK TabProcHook (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_INITDIALOG) {
		EnableThemeDialogTexture (hWnd, ETDT_ENABLETAB);
		SetWindowLong (hWnd, GWL_USERDATA, lParam);
		((TabPage*)lParam)->hTab = hWnd;
	}
	TabPage *pTab = (TabPage*)GetWindowLong (hWnd, GWL_USERDATA);
	if (pTab) return pTab->DlgProc (hWnd, uMsg, wParam, lParam);
	else      return FALSE;
}