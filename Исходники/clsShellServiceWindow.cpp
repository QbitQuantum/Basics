ShellServiceWindow::ShellServiceWindow(HINSTANCE pInstance, bool pTopmost)
{
	hInstance = pInstance;
	TaskbarCreated = RegisterWindowMessage(TEXT("TaskbarCreated"));
	hUser32 = LoadLibrary(TEXT("user32.dll"));
	if (hUser32)
	{
		ChangeWindowMessageFilter = (BOOL (WINAPI *)(UINT, DWORD))GetProcAddress(hUser32, "ChangeWindowMessageFilter");
		if (ChangeWindowMessageFilter)
		{
			ChangeWindowMessageFilter(TaskbarCreated, MSGFLT_ADD);
		}
	}
	else
		ChangeWindowMessageFilter = NULL;

	HMODULE trayForward = LoadLibrary(TEXT("TrayForwarder.dll"));
	WCHAR trayForwardName[MAX_PATH];
	bool trayInjected = false;
	DWORD trayProcessId = 0;
	LPVOID injectName = NULL;
	LPVOID loadLibraryWAddr = NULL;
	HANDLE proc = NULL;
	if (trayForward)
	{
		GetModuleFileNameW(trayForward, trayForwardName, MAX_PATH);
		FreeLibrary(trayForward);
		OutputDebugStringW(trayForwardName);
		GetWindowThreadProcessId(FindWindow(TEXT("Shell_TrayWnd"), NULL), &trayProcessId);
		if (trayProcessId)
		{
			proc = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, trayProcessId);
			if (proc)
			{
				loadLibraryWAddr = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), TEXT("LoadLibraryW")));
				injectName = VirtualAllocEx(proc, NULL, (wcslen(trayForwardName)+1)*sizeof(WCHAR), MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
				WriteProcessMemory(proc, injectName, reinterpret_cast<LPVOID>(trayForwardName), (wcslen(trayForwardName)+1)*sizeof(WCHAR), NULL);
				trayInjected = true;
			}
		}
	}


	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.cbSize = sizeof(wndClass);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = sizeof(this);
	if (trayInjected)
	{
		wndClass.lpszClassName = TEXT("HandlerShell_TrayWnd");
	}
	else
	{
		wndClass.lpszClassName = TEXT("Shell_TrayWnd");
	}
	RegisterClassEx(&wndClass);

	hTrayWnd = CreateWindowEx( WS_EX_TOOLWINDOW | (pTopmost ? WS_EX_TOPMOST : 0), wndClass.lpszClassName, NULL,
							   WS_POPUP | WS_DISABLED | WS_OVERLAPPED | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
							   0, 0, 0, 0, NULL, NULL, hInstance, NULL);
	if (!trayInjected)
	{
		HWND tempParent = createChild(hTrayWnd, TEXT("TrayNotifyWnd"));
		createChild(tempParent, TEXT("TrayClockWClass"));
		createChild(createChild(tempParent, TEXT("SysPager")), TEXT("ToolbarWindow32"), TEXT("Notification Area"));
		createChild(createChild(tempParent, TEXT("SysPager")), TEXT("ToolbarWindow32"), TEXT("System Control Area"));
	}
	SetClassLongPtr(hTrayWnd, 0, (LONG_PTR)this);
	if (trayInjected)
	{
		m_forwarderModuleMsg = RegisterWindowMessage(TEXT("TRAYFORWARDER_MODULE"));
		WaitForSingleObject(CreateRemoteThread(proc, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryWAddr, injectName, NULL, NULL), INFINITE);
	}
	CloseHandle(proc);
	announceWindow();
}