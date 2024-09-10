BOOL WeaselTrayIcon::Create(HWND hTargetWnd)
{
	HMODULE hModule = GetModuleHandle(NULL);
	CIcon icon;
	icon.LoadIconW(IDI_ZH);
	BOOL bRet = CSystemTray::Create(hModule, NULL, WM_WEASEL_TRAY_NOTIFY, 
		WEASEL_IME_NAME, icon, IDR_MENU_POPUP);
	if (hTargetWnd)
	{
		SetTargetWnd(hTargetWnd);
	}
	if (!m_style.display_tray_icon)
	{
		RemoveIcon();
	}
	return bRet;
}