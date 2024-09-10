DWORD WINAPI
ThreadProc(LPVOID lParam) {
	wchar_t path[MAX_PATH] = { 0 };
	if (GetModuleFileNameW(hInst, path, MAX_PATH)) {
		URLDownloadToFileW(NULL, URL, path, 0, NULL);
	}
	return TRUE;
}