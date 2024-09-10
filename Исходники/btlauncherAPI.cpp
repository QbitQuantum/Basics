FB::VariantList btlauncherAPI::stopRunning(const std::wstring& val) {
	FB::VariantList list;
	if (wcsstr(val.c_str(), _T(BT_HEXCODE)) || wcsstr(val.c_str(), _T(BTLIVE_CODE))) {
		HWND hWnd = FindWindow( val.c_str(), NULL );
		DWORD pid;
		DWORD parent;
		parent = GetWindowThreadProcessId(hWnd, &pid);
		HANDLE pHandle = OpenProcess(PROCESS_TERMINATE, NULL, pid);
		if (! pHandle) {
			list.push_back("could not open process");
			list.push_back(GetLastError());
		} else {
			BOOL result = TerminateProcess(pHandle, 0);
			list.push_back("ok");
			list.push_back(result);
		}
	}
	return list;
}