bool windows_tray_notification::create_tray_icon()
{
	// getting handle to a 32x32 icon, contained in "WESNOTH_ICON" icon group of wesnoth.exe resources
	const HMODULE wesnoth_exe = GetModuleHandle(NULL);
	if (wesnoth_exe == NULL) {
		return false;
	}

	const HRSRC group_icon_info = FindResource(wesnoth_exe, L"WESNOTH_ICON", RT_GROUP_ICON);
	if (group_icon_info == NULL) {
		return false;
	}

	HGLOBAL hGlobal = LoadResource(wesnoth_exe, group_icon_info);
	if (hGlobal == NULL) {
		return false;
	}

	const PBYTE group_icon_res = static_cast<PBYTE>(LockResource(hGlobal));
	if (group_icon_res == NULL) {
		return false;
	}

	const int nID = LookupIconIdFromDirectoryEx(group_icon_res, TRUE, 32, 32, LR_DEFAULTCOLOR);
	if (nID == 0) {
		return false;
	}

	const HRSRC icon_info = FindResource(wesnoth_exe, MAKEINTRESOURCE(nID), MAKEINTRESOURCE(3));
	if (icon_info == NULL) {
		return false;
	}

	hGlobal = LoadResource(wesnoth_exe, icon_info);
	if (hGlobal == NULL) {
		return false;
	}

	const PBYTE icon_res = static_cast<PBYTE>(LockResource(hGlobal));
	if (icon_res == NULL) {
		return false;
	}

	const HICON icon = CreateIconFromResource(icon_res, SizeofResource(wesnoth_exe, icon_info), TRUE, 0x00030000);
	if (icon == NULL) {
		return false;
	}

	const HWND window = get_window_hanlde();
	if (window == NULL) {
		return false;
	}

	// filling notification structure
	nid = new NOTIFYICONDATA;
	memset(nid, 0, sizeof(&nid));
	nid->cbSize = NOTIFYICONDATA_V2_SIZE;
	nid->hWnd = window;
	nid->uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid->dwInfoFlags = NIIF_USER;
	nid->uVersion = NOTIFYICON_VERSION;
	nid->uCallbackMessage = WM_TRAYNOTIFY;
	nid->uID = ICON_ID;
	nid->hIcon = icon;
#if _WIN32_WINNT >= 0x600
	nid->hBalloonIcon = icon;
#endif
	lstrcpy(nid->szTip, L"The Battle For Wesnoth");

	// creating icon notification
	return Shell_NotifyIcon(NIM_ADD, nid) != FALSE;
}