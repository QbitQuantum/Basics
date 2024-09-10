void CNewRandom::Initialize()
{
	++g_dwNewRandomInstanceCounter;

	DWORD dw;
	dw = timeGetTime();
	AddRandomObject(&dw, 4);

	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	AddRandomObject(&li, sizeof(LARGE_INTEGER));

	SYSTEMTIME st;
	ZeroMemory(&st, sizeof(SYSTEMTIME));
	GetLocalTime(&st);
	AddRandomObject(&st, sizeof(SYSTEMTIME));

	POINT pt;
	GetCursorPos(&pt);
	AddRandomObject(&pt, sizeof(POINT));

	WORD ww;
	ww = (WORD)(rand());
	AddRandomObject(&ww, 2);
	ww = (WORD)(rand());
	AddRandomObject(&ww, 2);
	ww = (WORD)(rand());
	AddRandomObject(&ww, 2);

	GetCaretPos(&pt);
	AddRandomObject(&pt, sizeof(POINT));

	MEMORYSTATUS ms;
	GlobalMemoryStatus(&ms);
	AddRandomObject(&ms, sizeof(MEMORYSTATUS));

	dw = (DWORD)(UINT_PTR)GetActiveWindow();
	AddRandomObject(&dw, 4);

	dw = (DWORD)(UINT_PTR)GetCapture();
	AddRandomObject(&dw, 4);

	dw = (DWORD)(UINT_PTR)GetClipboardOwner();
	AddRandomObject(&dw, 4);

#ifndef _WIN32_WCE
	// No support under Windows CE
	dw = (DWORD)(UINT_PTR)GetClipboardViewer();
	AddRandomObject(&dw, 4);
#endif

	dw = GetCurrentProcessId();
	AddRandomObject(&dw, 4);

	dw = (DWORD)(UINT_PTR)GetCurrentProcess();
	AddRandomObject(&dw, 4);

	dw = (DWORD)(UINT_PTR)GetActiveWindow();
	AddRandomObject(&dw, 4);

	dw = GetCurrentThreadId();
	AddRandomObject(&dw, 4);

	dw = (DWORD)(UINT_PTR)GetCurrentThread();
	AddRandomObject(&dw, 4);

	dw = (DWORD)(UINT_PTR)GetDesktopWindow();
	AddRandomObject(&dw, 4);

	dw = (DWORD)(UINT_PTR)GetFocus();
	AddRandomObject(&dw, 4);

	dw = (DWORD)(UINT_PTR)GetForegroundWindow();
	AddRandomObject(&dw, 4);

#ifndef _WIN32_WCE
	dw = (DWORD)GetInputState();
	AddRandomObject(&dw, 4); 
#endif

	dw = GetMessagePos();
	AddRandomObject(&dw, 4);

#ifndef _WIN32_WCE
	dw = (DWORD)GetMessageTime();
	AddRandomObject(&dw, 4);
#endif

	dw = (DWORD)(UINT_PTR)GetOpenClipboardWindow();
	AddRandomObject(&dw, 4);

	dw = (DWORD)(UINT_PTR)GetProcessHeap();
	AddRandomObject(&dw, 4);

	SYSTEM_INFO si;
	GetSystemInfo(&si);
	AddRandomObject(&si, sizeof(SYSTEM_INFO));

	dw = (DWORD)randXorShift();
	AddRandomObject(&dw, 4);

#ifndef _WIN32_WCE
	STARTUPINFO sui;
	GetStartupInfo(&sui);
	AddRandomObject(&sui, sizeof(STARTUPINFO));
#endif

	GUID guid;
	VERIFY(CoCreateGuid(&guid) == S_OK);
	AddRandomObject(&guid, sizeof(GUID));

	BYTE pbCrypt[64];
	CNewRandom::SysCryptGetRandom(&pbCrypt[0], 64);
	AddRandomObject(&pbCrypt[0], 64);

	AddRandomObject(&g_dwNewRandomInstanceCounter, 4);
}