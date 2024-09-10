void Eject()
{
	HANDLE hth = NULL;
	HANDLE hProcess = NULL;
	HANDLE hThread = NULL;

	__try
	{
		HWND hWnd = GetForegroundWindow();
		char buffer[256];
		GetWindowText(hWnd, buffer, 255);
		printf("当前窗口: %s\n", buffer);

		DWORD pid = 0;
		GetWindowThreadProcessId(hWnd, &pid);
		printf("进程ID: %x\n", pid);

		hth = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
		if(!hth)
		{
			printf("创建SnapShot失败。\n");
			__leave;
		}
		
		MODULEENTRY32 me = {sizeof(me)};
		BOOL ff = FALSE;
		for(BOOL fm = Module32First(hth, &me); fm; fm = Module32Next(hth, &me))
		{
			ff = (lstrcmpi(me.szExePath, g_dllName) == 0 || lstrcmpi(me.szModule, g_dllName) == 0);
			if(ff) break;
		}
		if(!ff)
		{
			printf("没有发现这个进程有DLL注入。\n");
			__leave;
		}

		hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE,
			FALSE, pid);
		if(!hProcess)
		{
			printf("打开进程失败。\n");
			__leave;
		}

		PTHREAD_START_ROUTINE pfn = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("Kernel32"), 
			"FreeLibrary");
		if(!pfn)
		{
			printf("获取FreeLibrary地址失败。\n");
			__leave;
		}

		hThread = CreateRemoteThread(hProcess, NULL, 0, pfn, me.modBaseAddr, 0, NULL);
		if(!hThread)
		{
			printf("创建远程线程失败。\n");
			__leave;
		}

		WaitForSingleObject(hThread, INFINITE);
	}
	__finally
	{
		if(hth) CloseHandle(hth);
		if(hThread) CloseHandle(hThread);
		if(hProcess) CloseHandle(hProcess);
	}
}