// CIR_OK=0 - OK, CIR_AlreadyInjected=1 - Already injected, иначе - ошибка
// Здесь вызывается CreateRemoteThread
CINFILTRATE_EXIT_CODES InjectRemote(DWORD nRemotePID, bool abDefTermOnly /*= false */)
{
	CINFILTRATE_EXIT_CODES iRc = CIR_GeneralError/*-1*/;
	bool lbWin64 = WIN3264TEST((IsWindows64()!=0),true);
	bool is32bit;
	int  nBits;
	DWORD nWrapperWait = (DWORD)-1, nWrapperResult = (DWORD)-1;
	HANDLE hProc = NULL;
	wchar_t szSelf[MAX_PATH+16], szHooks[MAX_PATH+16];
	wchar_t *pszNamePtr, szArgs[32];
	wchar_t szName[64];
	HANDLE hEvent = NULL;
	HANDLE hDefTermReady = NULL;
	bool bAlreadyHooked = false;
	HANDLE hSnap = NULL;
	MODULEENTRY32 mi = {sizeof(mi)};
	HMODULE ptrOuterKernel = NULL;

	if (!GetModuleFileName(NULL, szSelf, MAX_PATH))
	{
		iRc = CIR_GetModuleFileName/*-200*/;
		goto wrap;
	}
	wcscpy_c(szHooks, szSelf);
	pszNamePtr = (wchar_t*)PointToName(szHooks);
	if (!pszNamePtr)
	{
		iRc = CIR_GetModuleFileName/*-200*/;
		goto wrap;
	}


	// Hey, may be ConEmuHk.dll is already loaded?
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, nRemotePID);
	if (!hSnap || (hSnap == INVALID_HANDLE_VALUE))
	{
		iRc = CIR_SnapshotCantBeOpened/*-113*/;
		goto wrap;
	}
	else if (hSnap && Module32First(hSnap, &mi))
	{
		// 130829 - Let load newer(!) ConEmuHk.dll into target process.
		// 141201 - Also we need to be sure in kernel32.dll address

		LPCWSTR pszConEmuHk = WIN3264TEST(L"conemuhk.", L"conemuhk64.");
		size_t nDllNameLen = lstrlen(pszConEmuHk);
		// Out preferred module name
		wchar_t szOurName[40] = {};
		wchar_t szMinor[8] = L""; lstrcpyn(szMinor, _CRT_WIDE(MVV_4a), countof(szMinor));
		_wsprintf(szOurName, SKIPLEN(countof(szOurName))
			CEDEFTERMDLLFORMAT /*L"ConEmuHk%s.%02u%02u%02u%s.dll"*/,
			WIN3264TEST(L"",L"64"), MVV_1, MVV_2, MVV_3, szMinor);
		CharLowerBuff(szOurName, lstrlen(szOurName));

		// Go to enumeration
		wchar_t szName[64];
		do {
			LPCWSTR pszName = PointToName(mi.szModule);

			// Name of ConEmuHk*.*.dll module may be changed (copied to %APPDATA%)
			if (!pszName || !*pszName)
				continue;

			lstrcpyn(szName, pszName, countof(szName));
			CharLowerBuff(szName, lstrlen(szName));

			if (!ptrOuterKernel
				&& (lstrcmp(szName, L"kernel32.dll") == 0))
			{
				ptrOuterKernel = mi.hModule;
			}

			// ConEmuHk*.*.dll?
			if (!bAlreadyHooked
				&& (wmemcmp(szName, pszConEmuHk, nDllNameLen) == 0)
				&& (wmemcmp(szName+lstrlen(szName)-4, L".dll", 4) == 0))
			{
				// Yes! ConEmuHk.dll already loaded into nRemotePID!
				// But what is the version? Let don't downgrade loaded version!
				if (lstrcmp(szName, szOurName) >= 0)
				{
					// OK, szName is newer or equal to our build
					bAlreadyHooked = true;
				}
			}

			// Stop enumeration?
			if (bAlreadyHooked && ptrOuterKernel)
				break;
		} while (Module32Next(hSnap, &mi));

		// Check done
	}
	SafeCloseHandle(hSnap);


	// Already hooked?
	if (bAlreadyHooked)
	{
		iRc = CIR_AlreadyInjected/*1*/;
		goto wrap;
	}


	if (!ptrOuterKernel)
	{
		iRc = CIR_OuterKernelAddr/*-112*/;
		goto wrap;
	}


	// Check, if we can access that process
	hProc = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ, FALSE, nRemotePID);
	if (hProc == NULL)
	{
		iRc = CIR_OpenProcess/*-201*/;
		goto wrap;
	}


	// Go to hook

	// Preparing Events
	_wsprintf(szName, SKIPLEN(countof(szName)) CEDEFAULTTERMHOOK, nRemotePID);
	if (!abDefTermOnly)
	{
		// When running in normal mode (NOT set up as default terminal)
		// we need full initialization procedure, not a light one when hooking explorer.exe
		hEvent = OpenEvent(EVENT_MODIFY_STATE|SYNCHRONIZE, FALSE, szName);
		if (hEvent)
		{
			ResetEvent(hEvent);
			CloseHandle(hEvent);
		}
	}
	else
	{
		hEvent = CreateEvent(LocalSecurity(), FALSE, FALSE, szName);
		SetEvent(hEvent);

		_wsprintf(szName, SKIPLEN(countof(szName)) CEDEFAULTTERMHOOKOK, nRemotePID);
		hDefTermReady = CreateEvent(LocalSecurity(), FALSE, FALSE, szName);
		ResetEvent(hDefTermReady);
	}

	// Creating as remote thread.
	// Resetting this event notify ConEmuHk about
	// 1) need to determine MainThreadId
	// 2) need to start pipe server
	_wsprintf(szName, SKIPLEN(countof(szName)) CECONEMUROOTTHREAD, nRemotePID);
	hEvent = OpenEvent(EVENT_MODIFY_STATE|SYNCHRONIZE, FALSE, szName);
	if (hEvent)
	{
		ResetEvent(hEvent);
		CloseHandle(hEvent);
	}


	// Определить битность процесса, Если он 32битный, а текущий - ConEmuC64.exe
	// Перезапустить 32битную версию ConEmuC.exe
	nBits = GetProcessBits(nRemotePID, hProc);
	if (nBits == 0)
	{
		// Do not even expected, ConEmu GUI must run ConEmuC elevated if required.
		iRc = CIR_GetProcessBits/*-204*/;
		goto wrap;
	}

	is32bit = (nBits == 32);

	if (is32bit != WIN3264TEST(true,false))
	{
		// По идее, такого быть не должно. ConEmu должен был запустить соответствующий conemuC*.exe
		_ASSERTE(is32bit == WIN3264TEST(true,false));
		PROCESS_INFORMATION pi = {};
		STARTUPINFO si = {sizeof(si)};

		_wcscpy_c(pszNamePtr, 16, is32bit ? L"ConEmuC.exe" : L"ConEmuC64.exe");
		_wsprintf(szArgs, SKIPLEN(countof(szArgs)) L" /INJECT=%u", nRemotePID);

		if (!CreateProcess(szHooks, szArgs, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
		{
			iRc = CIR_CreateProcess/*-202*/;
			goto wrap;
		}
		nWrapperWait = WaitForSingleObject(pi.hProcess, INFINITE);
		GetExitCodeProcess(pi.hProcess, &nWrapperResult);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		if ((nWrapperResult != CERR_HOOKS_WAS_SET) && (nWrapperResult != CERR_HOOKS_WAS_ALREADY_SET))
		{
			iRc = CIR_WrapperResult/*-203*/;
			SetLastError(nWrapperResult);
			goto wrap;
		}
		// Значит всю работу сделал враппер
		iRc = CIR_OK/*0*/;
		goto wrap;
	}

	// Поехали
	_wcscpy_c(pszNamePtr, 16, is32bit ? L"ConEmuHk.dll" : L"ConEmuHk64.dll");
	if (!FileExists(szHooks))
	{
		iRc = CIR_ConEmuHkNotFound/*-250*/;
		goto wrap;
	}

	if (abDefTermOnly)
	{
		CINFILTRATE_EXIT_CODES iFRc = PrepareHookModule(szHooks);
		if (iFRc != 0)
		{
			iRc = iFRc;
			goto wrap;
		}
	}

	iRc = InfiltrateDll(hProc, ptrOuterKernel, szHooks);

	// Если создавали временную копию - запланировать ее удаление
	if (abDefTermOnly && (lstrcmpi(szHooks, szSelf) != 0))
	{
		MoveFileEx(szHooks, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
	}
wrap:
	if (hProc != NULL)
		CloseHandle(hProc);
	// But check the result of the operation

	//_ASSERTE(FALSE && "WaitForSingleObject(hDefTermReady)");

	if ((iRc == 0) && hDefTermReady)
	{
		_ASSERTE(abDefTermOnly);
		DWORD nWaitReady = WaitForSingleObject(hDefTermReady, CEDEFAULTTERMHOOKWAIT/*==0*/);
		if (nWaitReady == WAIT_TIMEOUT)
		{
			iRc = CIR_DefTermWaitingFailed/*-300*/; // Failed to start hooking thread in remote process
		}
	}
	return iRc;
}