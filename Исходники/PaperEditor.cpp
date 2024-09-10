BOOL CALLBACK EnumWindowsProc(HWND hwnd/*当前找到的窗口句柄*/, LPARAM lParam/*自定义参数*/)  //枚举当前窗口
{
	TCHAR tcClass[256];
	LPWSTR  pStr = (LPWSTR)lParam;
	HWND htmpWnd = NULL;
	::GetClassName(hwnd, tcClass, 255);

	DWORD dwProcessID;
	TCHAR szProcessName[260] = { 0 };
	GetWindowThreadProcessId(hwnd, &dwProcessID);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessID);

	GetModuleFileNameEx(hProcess, NULL, szProcessName, MAX_PATH);

	if (strstr(szProcessName, _T("\\PaperEditor.exe")) != NULL)
	{
		CWnd * pWndPrev = CWnd::FromHandle(hwnd);
		pWndPrev = pWndPrev->GetParent();
		if (pWndPrev != NULL)
		{
			CWnd * pWndChild = pWndPrev->GetLastActivePopup();
			if (pWndPrev->IsIconic())
				pWndPrev->ShowWindow(SW_RESTORE);
			pWndChild->SetForegroundWindow();
		}
	}
	return TRUE;
}