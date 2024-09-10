int MyAssertProc(const wchar_t* pszFile, int nLine, const wchar_t* pszTest, bool abNoPipe)
{
	HooksUnlocker;

	#ifdef _DEBUG
	if (MyAssertSkip(pszFile, nLine, pszTest, abNoPipe))
		return 1;
	#endif

	MyAssertDumpToFile(pszFile, nLine, pszTest);

	HANDLE hHeap = GetProcessHeap();
	MyAssertInfo* pa = (MyAssertInfo*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, sizeof(MyAssertInfo));
	if (!pa)
		return -1;
	wchar_t *szExeName = (wchar_t*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, (MAX_PATH+1)*sizeof(wchar_t));
	if (szExeName && !GetModuleFileNameW(NULL, szExeName, MAX_PATH+1)) szExeName[0] = 0;
	pa->bNoPipe = abNoPipe;
	msprintf(pa->szTitle, countof(pa->szTitle), L"CEAssert PID=%u TID=%u", GetCurrentProcessId(), GetCurrentThreadId());
	wchar_t szVer4[2] = WSTRING(MVV_4a);
	msprintf(pa->szDebugInfo, countof(pa->szDebugInfo), L"Assertion in %s [%02u%02u%02u%s]\n%s\n\n%s: %i\n\nPress 'Retry' to trap.",
	                szExeName ? szExeName : L"<HeapAllocFailed>",
					MVV_1, MVV_2, MVV_3, szVer4,
					pszTest ? pszTest : L"", pszFile, nLine);
	DWORD dwCode = 0;

	if (gAllowAssertThread == am_Thread)
	{
		DWORD dwTID;
		HANDLE hThread = apiCreateThread(MyAssertThread, pa, &dwTID, "MyAssertThread");

		if (hThread == NULL)
		{
			dwCode = IDRETRY;
			goto wrap;
		}

		WaitForSingleObject(hThread, INFINITE);
		GetExitCodeThread(hThread, &dwCode);
		CloseHandle(hThread);
		goto wrap;
	}
	
#ifdef ASSERT_PIPE_ALLOWED
#ifdef _DEBUG
	if (!abNoPipe && (gAllowAssertThread == am_Pipe))
	{
		HWND hConWnd = GetConEmuHWND(2);
		HWND hGuiWnd = ghConEmuWnd;

		// -- искать - нельзя. Если мы НЕ в ConEmu - нельзя стучаться в другие копии!!!
		//#ifndef CONEMU_MINIMAL
		//if (hGuiWnd == NULL)
		//{
		//	hGuiWnd = FindWindowEx(NULL, NULL, VirtualConsoleClassMain, NULL);
		//}
		//#endif

		if (hGuiWnd && gnInMyAssertTrap <= 0)
		{
			InterlockedIncrement(&gnInMyAssertTrap);
			InterlockedIncrement(&gnInMyAssertPipe);
			gnInMyAssertThread = GetCurrentThreadId();
			ResetEvent(ghInMyAssertTrap);
			
			dwCode = GuiMessageBox(abNoPipe ? NULL : hGuiWnd, pa->szDebugInfo, pa->szTitle, MB_SETFOREGROUND|MB_SYSTEMMODAL|MB_RETRYCANCEL);
			InterlockedDecrement(&gnInMyAssertTrap);
			InterlockedDecrement(&gnInMyAssertPipe);
			SetEvent(ghInMyAssertTrap);
			gnInMyAssertThread = 0;
			goto wrap;
		}
	}

	while (gnInMyAssertPipe>0 && (gnInMyAssertThread != GetCurrentThreadId()))
	{
		Sleep(250);
	}
#endif
#endif

	// В консольных приложениях попытка запустить CreateThread(MyAssertThread) может зависать
	dwCode = MyAssertThread(pa);

wrap:
	if (pa)
		HeapFree(hHeap, 0, pa);
	if (szExeName)
		HeapFree(hHeap, 0, szExeName);
	return (dwCode == IDRETRY) ? -1 : 1;
}