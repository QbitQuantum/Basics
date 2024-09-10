void FillCombo(HWND hwnd, int id, int indexSettings)
{
	HKL saved = SettingsGlobal().hkl_lay[indexSettings];
	bool found = false;
	for (int i = 0; i < g_laySize; i++)
	{
		HKL cur = g_laylist[i];
		WORD langid = LOWORD(cur);
		TCHAR buf[512]; buf[0] = 0;
		int flag = IsWindowsVistaOrGreater() ? LOCALE_SNAME : LOCALE_SLANGUAGE;
		int len = GetLocaleInfo(MAKELCID(langid, SORT_DEFAULT), flag, buf, 512);
		SW_WINBOOL_LOG(len != 0);
		SendDlgItemMessage(hwnd, id, CB_ADDSTRING, 0, (LPARAM)buf);
		if (saved == cur)
		{
			found = true;
			SendDlgItemMessage(hwnd, id, CB_SETCURSEL, (WPARAM)i, (LPARAM)0);
		}
	}
	if(!found)
	{
		SendDlgItemMessage(hwnd, id, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
	}

	

}