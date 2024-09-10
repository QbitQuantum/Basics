int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASSEXW wc;
	HWND hWnd;
	WSADATA wsaData;
	PSECURITY_DESCRIPTOR psd;
	SECURITY_ATTRIBUTES sa;

	_wsetlocale(LC_ALL, L"JPN");

	CreateConfigPath();

	if(ConvertStringSecurityDescriptorToSecurityDescriptorW(krnlobjsddl, SDDL_REVISION_1, &psd, NULL))
	{
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = psd;
		sa.bInheritHandle = FALSE;

		hMutex = CreateMutexW(&sa, FALSE, mgrmutexname);
		if(hMutex == NULL || GetLastError() == ERROR_ALREADY_EXISTS)
		{
			LocalFree(psd);
			return 0;
		}

		LocalFree(psd);
	}
	else
	{
		return 0;
	}

	WSAStartup(WINSOCK_VERSION, &wsaData);

	ZeroMemory(&ftConfig, sizeof(ftConfig));
	if(IsFileUpdated(pathconfigxml, &ftConfig))
	{
		LoadConfig();
	}

	ZeroMemory(&ftSKKDic, sizeof(ftSKKDic));
	if(IsFileUpdated(pathskkdic, &ftSKKDic))
	{
		MakeSKKDicPos();
	}

	InitLua();

	hInst = hInstance;

	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = DictionaryManagerClass;
	RegisterClassExW(&wc);

#ifdef _DEBUG
	hWnd = CreateWindowW(DictionaryManagerClass, TextServiceDesc,
		WS_OVERLAPPEDWINDOW, 0, 0, 600, 800, NULL, NULL, hInst, NULL);
#else
	hWnd = CreateWindowW(DictionaryManagerClass, TextServiceDesc,
		WS_POPUP, 0, 0, 0, 0, NULL, NULL, hInst, NULL);
#endif

	if(!hWnd)
	{
		UninitLua();
		WSACleanup();
		return 0;
	}

#ifdef _DEBUG
	ShowWindow(hWnd, SW_MINIMIZE);
#else
	ShowWindow(hWnd, SW_HIDE);
#endif
	UpdateWindow(hWnd);

	while(GetMessageW(&msg, NULL, 0, 0))
	{
		if(!TranslateAcceleratorW(msg.hwnd, NULL, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	UninitLua();
	WSACleanup();

	return (int) msg.wParam;
}