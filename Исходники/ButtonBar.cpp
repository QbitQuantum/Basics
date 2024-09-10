void CButtonBar::Create(HWND hParent, const RECT &rect)
{
	WNDCLASSA wndclass;
	if (FALSE == GetClassInfoA(genDll.m_hInstance, CLASSNAME, &wndclass))
	{
		memset(&wndclass, 0, sizeof(wndclass));
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.hInstance = genDll.m_hInstance;
		wndclass.lpfnWndProc = WindowProc;
		wndclass.lpszClassName = CLASSNAME;
		wndclass.lpszMenuName = 0;
		wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_SAVEBITS;

		if (false == RegisterClassA(&wndclass))
		{
			DWORD dwError = GetLastError();
			char str[30];
			sprintf_s(str, 30, "Error 0x%x", dwError);
			MessageBoxA(hParent, str, "Fatal Error!", MB_ICONERROR);
#ifdef _DEBUG
			DebugBreak();
#endif
			PostQuitMessage(-1);
		}
	}

		m_hWnd = CreateWindowA(CLASSNAME, "", WS_CHILD | WS_VISIBLE, rect.left, rect.top, 
			rect.right - rect.left + 1, rect.bottom - rect.top + 1, hParent, 0, genDll.m_hInstance, 0);
		if (m_hWnd == 0)
		{
			DWORD dwError = GetLastError();
			char str[30];
			sprintf_s(str, 30, "Error 0x%x", dwError);
			MessageBoxA(hParent, str, "Fatal Error!", MB_ICONERROR);
#ifdef _DEBUG
			DebugBreak();
#endif
			PostQuitMessage(-1);
		}

		GetClientRect(m_hWnd, &m_rClient);

		m_hbFBack = LoadBitmap(genDll.m_hInstance, MAKEINTRESOURCE(IDB_FBACK));
		m_hbFFar = LoadBitmap(genDll.m_hInstance, MAKEINTRESOURCE(IDB_FFAR));
		m_hbPlay = LoadBitmap(genDll.m_hInstance, MAKEINTRESOURCE(IDB_PLAY));
		m_hbPause = LoadBitmap(genDll.m_hInstance, MAKEINTRESOURCE(IDB_PAUSE));
		m_hbStop = LoadBitmap(genDll.m_hInstance, MAKEINTRESOURCE(IDB_STOP));

		m_hbFBack2 = LoadBitmap(genDll.m_hInstance, MAKEINTRESOURCE(IDB_FBACK2));
		m_hbFFar2 = LoadBitmap(genDll.m_hInstance, MAKEINTRESOURCE(IDB_FFAR2));
		m_hbPlay2 = LoadBitmap(genDll.m_hInstance, MAKEINTRESOURCE(IDB_PLAY2));
		m_hbPause2 = LoadBitmap(genDll.m_hInstance, MAKEINTRESOURCE(IDB_PAUSE2));
		m_hbStop2 = LoadBitmap(genDll.m_hInstance, MAKEINTRESOURCE(IDB_STOP2));

		SetWindowLongPtrA(m_hWnd, GWL_USERDATA, (LONG_PTR)this);
}