LONG _declspec(dllexport) EnableTopMost(LONG bEnable) {
	HWND hTop = NULL;
	DWORD dwThreadID;

	dwThreadID = GetCurrentThreadId();
	EnumThreadWindows(dwThreadID, FindWindowProc, (LPARAM)&hTop);

	if(hTop) {
		if (bEnable == 0) {
			SetWindowPos(hTop, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		}else{
			SetWindowPos(hTop, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		}
	}
	return GetLastError();
}