INT_PTR CALLBACK AssignProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
	case WM_INITDIALOG:
		g_bCtrlDown = FALSE;
		g_bAltDown = FALSE;
		g_OrigButtonProc = (WNDPROC)LongToPtr(SetWindowLong(GetDlgItem(hwndDlg, IDC_DUMMY), GWL_WNDPROC, PtrToLong(SubclassedButtonProc)));
		break;
    default:
        return FALSE;
        break;
    }
    return TRUE;
}