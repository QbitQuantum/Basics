void InitDialogHotKey(HWND hwnd, LPARAM lparam)
{
	SW_TSTATUS_LOG(CenterWindow(g_dlgData.hwndMainMenu, hwnd));

	g_hkdata = (DlgHotKeyData*)lparam;

	g_hkdata->hwnd = hwnd;

	std::wstring sKeyRevert;
	g_hkdata->keyDefault.ToString(sKeyRevert);
	SetDlgItemText(hwnd, IDC_RADIO_DEFAULT, sKeyRevert.c_str());

	KeyToDlg(g_hkdata->keyRevert, IDC_EDIT_BREAK, hwnd);

	g_hkdata->oldEditBreakProc = (WNDPROC)SetWindowLongPtr(
		GetDlgItem(hwnd, IDC_EDIT_BREAK),
		GWLP_WNDPROC,
		(LONG_PTR)EditBreakProc);

	SW_WINBOOL_LOG(g_hkdata->oldEditBreakProc != NULL);
	g_hkdata->hwndEditRevert = GetDlgItem(hwnd, IDC_EDIT_BREAK);

	
	if(g_hkdata->keyRevert == g_hkdata->keyDefault)
	{
		SetRadio(IDC_RADIO_DEFAULT, hwnd);
	}
	else if (g_hkdata->keyRevert.IsEmpty())
	{
		SetRadio(IDC_RADIO_CLEAR, hwnd);
	}
	else
	{
		SetRadio(IDC_RADIO_TYPE, hwnd);
	}

	CheckDlgButton(hwnd, IDC_CHECK_LEFTRIGHT, g_hkdata->keyRevert.GetLeftRightMode() ? BST_CHECKED : BST_UNCHECKED);
	SetFocus(GetDlgItem(hwnd, IDC_EDIT_BREAK));
	

	CAutoHMODULE hModUser;
	if (!IsWindowsVistaOrGreater())
	{
		hModUser = LoadLibrary(L"user32.dll");
	}
	g_hkdata->hHookKeyGlobal = ntapi::SetWindowsHookEx(WH_KEYBOARD_LL, &LowLevelKeyboardProc, hModUser, 0);
	SW_WINBOOL_LOG(g_hkdata->hHookKeyGlobal.IsValid());
}