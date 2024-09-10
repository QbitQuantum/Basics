BOOL WINAPI OnReadConsoleInputW(HANDLE hConsoleInput, PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead)
{
	//typedef BOOL (WINAPI* OnReadConsoleInputW_t)(HANDLE hConsoleInput, PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead);
	SUPPRESSORIGINALSHOWCALL;
	ORIGINAL_KRNL(ReadConsoleInputW);
	//if (gpFarInfo && bMainThread)
	//	TouchReadPeekConsoleInputs(0);
	BOOL lbRc = FALSE;

	// To minimize startup duration and possible problems
	// hook server will start on first 'user interaction'
	CheckHookServer();

	if (ph && ph->PreCallBack)
	{
		SETARGS4(&lbRc,hConsoleInput,lpBuffer,nLength,lpNumberOfEventsRead);

		// Если функция возвращает FALSE - реальное чтение не будет вызвано
		if (!ph->PreCallBack(&args))
			return lbRc;
	}

	CESERVER_CONSOLE_APP_MAPPING* pAppMap = NULL;
	PreReadConsoleInput(hConsoleInput, rcif_Unicode|rcif_LLInput, &pAppMap);

	//#ifdef USE_INPUT_SEMAPHORE
	//DWORD nSemaphore = ghConInSemaphore ? WaitForSingleObject(ghConInSemaphore, INSEMTIMEOUT_READ) : 1;
	//_ASSERTE(nSemaphore<=1);
	//#endif

	#if 0
	// get-help Get-ChildItem -full | out-host -paging
	HANDLE hInTest;
	HANDLE hTestHandle = NULL;
	DWORD nInMode, nArgMode;
	BOOL bInTest = FALSE, bArgTest = FALSE;
	if (gbPowerShellMonitorProgress)
	{
		hInTest = GetStdHandle(STD_INPUT_HANDLE);
		#ifdef _DEBUG
		bInTest = GetConsoleMode(hInTest, &nInMode);
		bArgTest = GetConsoleMode(hConsoleInput, &nArgMode);
		hTestHandle = CreateFile(L"CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (hTestHandle != INVALID_HANDLE_VALUE)
			CloseHandle(hTestHandle);
		#endif
	}
	#endif

	if (gFarMode.bFarHookMode && USE_INTERNAL_QUEUE) // ecompl speed-up
	{
		#ifdef _DEBUG
		DWORD nDbgReadReal = countof(gir_Real), nDbgReadVirtual = countof(gir_Virtual);
		BOOL bReadReal = PeekConsoleInputW(hConsoleInput, gir_Real, nDbgReadReal, &nDbgReadReal);
		BOOL bReadVirt = gInQueue.ReadInputQueue(gir_Virtual, &nDbgReadVirtual, TRUE);
		#endif

		if ((!lbRc || !(lpNumberOfEventsRead && *lpNumberOfEventsRead)) && !gInQueue.IsInputQueueEmpty())
		{
			DWORD n = nLength;
			lbRc = gInQueue.ReadInputQueue(lpBuffer, &n, FALSE);
			if (lpNumberOfEventsRead)
				*lpNumberOfEventsRead = lbRc ? n : 0;
		}
		else
		{
			lbRc = F(ReadConsoleInputW)(hConsoleInput, lpBuffer, nLength, lpNumberOfEventsRead);
		}
	}
	else
	{
		lbRc = F(ReadConsoleInputW)(hConsoleInput, lpBuffer, nLength, lpNumberOfEventsRead);
	}

	// cygwin/msys shells prompt
	if (lbRc && CEAnsi::ghAnsiLogFile
		&& (nLength == 1) && (*lpNumberOfEventsRead == 1) && (lpBuffer->EventType == KEY_EVENT)
		&& lpBuffer->Event.KeyEvent.bKeyDown && (lpBuffer->Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
		)
	{
		CEAnsi::AnsiLogEnterPressed();
	}

	PostReadConsoleInput(hConsoleInput, rcif_Unicode|rcif_LLInput, pAppMap);

	//#ifdef USE_INPUT_SEMAPHORE
	//if ((nSemaphore == WAIT_OBJECT_0) && ghConInSemaphore) ReleaseSemaphore(ghConInSemaphore, 1, NULL);
	//#endif

	if (ph && ph->PostCallBack)
	{
		SETARGS4(&lbRc,hConsoleInput,lpBuffer,nLength,lpNumberOfEventsRead);
		ph->PostCallBack(&args);
	}

	if (lbRc && lpNumberOfEventsRead && *lpNumberOfEventsRead && lpBuffer)
	{
		OnPeekReadConsoleInput('R', 'W', hConsoleInput, lpBuffer, *lpNumberOfEventsRead);
	}

	return lbRc;
}