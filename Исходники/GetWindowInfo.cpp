int _tmain(int argc, _TCHAR* argv[])
{
	printf("*GetWindowInfo*\n");
	printf("You can monitoring the window inforamtion and its process inforamtion that pointed by your mouse cursor\n");
	printf("If you press any key, start monitoring.\n");
	WCHAR wchtemp;
	scanf_s("%c", &wchtemp);

	HMODULE hmodule = GetModuleHandle(L"ntdll.dll");
	if (NULL == hmodule) hmodule = LoadLibraryW(L"ntdll.dll");
	if (NULL == hmodule)
	{
		printf("ntdll load failed with %d", ::GetLastError());
		return -1;
	}

	NtQueryInformationProcess = (PFNtQueryInformationProcess)::GetProcAddress(hmodule, "NtQueryInformationProcess");
	POINT p = { 0, };
	HWND prevhwnd = NULL;
	HWND curhwnd = NULL;
	while (GetCursorPos(&p))
	{
		if ((curhwnd = WindowFromPoint(p)) != prevhwnd)
		{
			WCHAR wchClass[MAX_NAME_LENGTH];
			memset(wchClass, 0, MAX_NAME_LENGTH*sizeof(WCHAR));
			GetClassNameW(curhwnd, wchClass, MAX_NAME_LENGTH);

			WCHAR wchWindow[MAX_NAME_LENGTH];
			memset(wchWindow, 0, MAX_NAME_LENGTH*sizeof(WCHAR));
			GetWindowTextW(curhwnd, wchWindow, MAX_NAME_LENGTH);

			DWORD dwPid = 0;
			DWORD dwTid = 0;
			dwTid = GetWindowThreadProcessId(curhwnd, &dwPid);

			printf("===============================================================================\n");
			printf("GetCursorPos : p.x-%d, p.y-%d\n", p.x, p.y);
			printf("-------------------------------------------------------------------------------\n");
			printf("Window Information\n");
			printf("-------------------------------------------------------------------------------\n");
			printf("Current Hwnd : 0x%x\n", (DWORD)curhwnd);
			printf("ClssName : %ws\n", wchClass);
			printf("WindowTitle : %ws\n", wchWindow);
			printf("-------------------------------------------------------------------------------\n");
			printf("Process Information\n");
			printf("-------------------------------------------------------------------------------\n");
			printf("Pid : %d\n", dwPid);
			printf("Tid : %d\n", dwTid);

			WCHAR wchstr[MAX_COMMANDLINE_LENGTH];
			memset(wchstr, 0, MAX_COMMANDLINE_LENGTH* sizeof(WCHAR));
			if (GetCommandLine(dwPid, wchstr))
			{
				printf("CommandLine : %ws\n", wchstr);
			}
			prevhwnd = curhwnd;
			printf("===============================================================================\n");
			printf("\n\n");
		}
	}

	return 0;
}