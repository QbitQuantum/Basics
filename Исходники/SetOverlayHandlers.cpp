void CSetOverlayHandlers::OnBnClickedRegedt()
{
	PWSTR pszPath = nullptr;
	if (SHGetKnownFolderPath(FOLDERID_Windows, KF_FLAG_CREATE, nullptr, &pszPath) == S_OK)
	{
		CString path = pszPath;
		CoTaskMemFree(pszPath);
		path += L"\\regedit.exe";

		// regedit stores the key it showed last in
		// HKEY_Current_User\Software\Microsoft\Windows\CurrentVersion\Applets\Regedit\LastKey
		// we set that here to
		// HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers
		// so when we start regedit, it will show that key on start
		CRegString regLastKey(L"Software\\Microsoft\\Windows\\CurrentVersion\\Applets\\Regedit\\LastKey");
		regLastKey = L"HKEY_Local_Machine\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ShellIconOverlayIdentifiers";

		SHELLEXECUTEINFO si = { sizeof(SHELLEXECUTEINFO) };
		si.hwnd = GetSafeHwnd();
		si.lpVerb = L"open";
		si.lpFile = path;
		si.nShow = SW_SHOW;
		ShellExecuteEx(&si);
	}
}