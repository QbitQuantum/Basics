HINSTANCE HookWindow(HWND hWnd, DWORD dwProcessId, int data)
{
   const int cbCodeSize = ((LPBYTE)AfterRemoteStartup - (LPBYTE)RemoteStartup);
	const DWORD cbMemSize = cbCodeSize + sizeof(RemoteStartupArgs) + 3;
   HANDLE hProcess;
	HINSTANCE hinstKrnl = GetModuleHandle("Kernel32");
	PDWORD pdwCodeRemote = NULL;
   RemoteStartupArgs args;
   RemoteStartupArgs * pArgsRemote;
	DWORD dwNumBytesXferred = 0;
	HANDLE hThread = NULL;
   DWORD dwOldProtect;
   HINSTANCE res;

   hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
   if (!hProcess)
      return NULL;

   //Allocate some memory for our function and its argument
	pdwCodeRemote = (PDWORD) AllocProcessMemory(hProcess, cbMemSize);
	if (!pdwCodeRemote)
   {
      CloseHandle(hProcess);
      return NULL;
   }

	// Change the page protection of the allocated memory to executable, read, and write.
	if (!VirtualProtectEx(hProcess, pdwCodeRemote, cbMemSize, PAGE_EXECUTE_READWRITE, &dwOldProtect))
   {
      FreeProcessMemory(hProcess, pdwCodeRemote);
      CloseHandle(hProcess);
      return NULL;
   }

	// Write a copy of the function to the remote process.
   if (!WriteProcessMemory(hProcess, pdwCodeRemote, (LPVOID)RemoteStartup, cbCodeSize, &dwNumBytesXferred))
   {
      FreeProcessMemory(hProcess, pdwCodeRemote);
      CloseHandle(hProcess);
      return NULL;
   }

   // Initialize the arguments
   args.fnLoadLibrary = (HINSTANCE (WINAPI *)(LPCTSTR))
                          GetProcAddress(hinstKrnl, "LoadLibraryA");
   args.fnFreeLibrary = (BOOL (WINAPI *)(HINSTANCE))
                          GetProcAddress(hinstKrnl, "FreeLibrary");
   args.fnGetProcAddress = (FARPROC (WINAPI *)(HINSTANCE,LPCSTR))GetProcAddress(hinstKrnl, "GetProcAddress");
   args.hWnd = hWnd;
   args.data = data;
   args.fnIndex = 0x1;
   DWORD result = SearchPathA(NULL, "HookDLL.dll", NULL, MAX_PATH, args.pbLibFile, NULL);
   if ((result < 0) || (result > MAX_PATH))
   {
      FreeProcessMemory(hProcess, pdwCodeRemote);
      CloseHandle(hProcess);
      return NULL;
   }

	// Write a copy of the arguments to the remote process (the structure MUST start on a 32-bit bourdary)
   pArgsRemote = (RemoteStartupArgs*)(pdwCodeRemote + ((cbCodeSize + 4) & ~3));
   if (!WriteProcessMemory(hProcess, pArgsRemote,	&args, sizeof(args), &dwNumBytesXferred))
   {
      FreeProcessMemory(hProcess, pdwCodeRemote);
      CloseHandle(hProcess);
      return NULL;
   }

   //Run the remote function
	hThread = CreateRemoteThread(hProcess, NULL, 10000, (LPTHREAD_START_ROUTINE)pdwCodeRemote, pArgsRemote, 0, NULL);
	if (hThread == NULL)
   {
      FreeProcessMemory(hProcess, pdwCodeRemote);
      CloseHandle(hProcess);
      return NULL;
   }

   //Wait till it returns, then get the result
	WaitForSingleObject(hThread, INFINITE);
   GetExitCodeThread(hThread, (PDWORD) &res);
	
   //Do some cleanup
   CloseHandle(hThread);
   FreeProcessMemory(hProcess, pdwCodeRemote);
   CloseHandle(hProcess);

   return res;
}