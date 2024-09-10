DWORD64 WoW64dm::LoadLibrary64( const wchar_t* path )
{
    BOOL isWOW = FALSE;
    IsWow64Process(_hProcess, &isWOW);

    // Inject into x64
    if(isWOW == FALSE)
    {
        DWORD64 memptr = 0;

        VirtualAllocEx64(memptr, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

        if(memptr != 0)
        {
            DWORD size = 0;

            DWORD64 hKernel32 = GetModuleHandle64(L"Kernel32.dll", &size);
            DWORD64 pLoadLib  = GetProcAddress64(hKernel32, size, "LoadLibraryW");

            if(pLoadLib != 0 && WriteProcessMemory64(memptr, (LPVOID)path, (wcslen(path) + 1)*sizeof(wchar_t), 0) == STATUS_SUCCESS)
            {
                DWORD64 status = 0;

                if(CreateRemoteThread64(pLoadLib, memptr, status, true) != FALSE && status == STATUS_SUCCESS)
                {
                    VirtualFreeEx64(memptr, 0x1000, MEM_RELEASE);
                    return status;
                }
            }

            VirtualFreeEx64(memptr, 0x1000, MEM_FREE);
        }

        return FALSE;
    }
    // Inject into WOW64
    else
    {
        return LoadLibraryRemoteWOW64(path);
    }
}