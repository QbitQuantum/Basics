LRESULT SwitcherSettingsDialog::OnGetSchemata(WORD, WORD, HWND hWndCtl, BOOL&) {
	HKEY hKey;
	LSTATUS ret = RegOpenKey(HKEY_LOCAL_MACHINE, _T("Software\\Rime\\Weasel"), &hKey);
	if (ret == ERROR_SUCCESS) {
		WCHAR value[MAX_PATH];
		DWORD len = sizeof(value);
		DWORD type = 0;
		DWORD data = 0;
		ret = RegQueryValueExW(hKey, L"WeaselRoot", NULL, &type, (LPBYTE)value, &len);
		if (ret == ERROR_SUCCESS && type == REG_SZ) {
			WCHAR parameters[MAX_PATH + 37];
			wcscpy_s<_countof(parameters)>(parameters, (std::wstring(L"/k \"") + value + L"\\rime-install.bat\"").c_str());
			SHELLEXECUTEINFOW cmd = {
				sizeof(SHELLEXECUTEINFO),
				SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC,
				hWndCtl,
				L"open",
				L"cmd",
				parameters,
				NULL,
				SW_SHOW,
				NULL, NULL, NULL, NULL, NULL, NULL, NULL
			};
			ShellExecuteExW(&cmd);
			WaitForSingleObject(cmd.hProcess, INFINITE);
			CloseHandle(cmd.hProcess);
			api_->load_settings(reinterpret_cast<RimeCustomSettings *>(settings_));
			Populate();
		}
	}
	RegCloseKey(hKey);
	return 0;
}