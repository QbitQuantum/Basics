void Inject(HANDLE process, LPCSTR modulePath)
{
	if(!FileExists(modulePath))
	{
		MessageBox(0, modulePath, "File Not Found", 0);
		return;
	}

    LPVOID address = nullptr;
    BOOL success = FALSE;
    HMODULE kernel32 = nullptr;
    HANDLE thread = nullptr;

    __try
    {
        // Inject the dll path into the target process
	    address = VirtualAllocEx(process, NULL, strlen(modulePath), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	    printf("Address allocated : %X\n", address);
        success = WriteProcessMemory(process, (LPVOID)address, modulePath, strlen(modulePath), NULL);
	    printf("WriteProcessMemory : %s\n", success? "successed":"failed");

        // Invoke LoadLibrary via CreateRemoteThread
	    kernel32 = GetModuleHandle("kernel32.dll");
	    printf("Kernel32 : %X\n", kernel32);
	    thread = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(kernel32, "LoadLibraryA"), (LPVOID)address, 0, NULL);
	    printf("Remote thread handle : %X\n", thread);
    }
    __finally
    {
	    if(thread) CloseHandle(thread);
	    if(kernel32) FreeLibrary(kernel32);
	    if(address) VirtualFreeEx(process, NULL, (size_t)strlen(modulePath), MEM_RESERVE|MEM_COMMIT);
    }
}