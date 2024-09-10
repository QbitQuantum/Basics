void IH_GetImportTableAddresses() //Retrieve basic import data
{
    HINSTANCE kernel32; 						// Handle to kernel32
    unsigned int VirtualProtect_Addr; 			// VirtualProtect Address
    unsigned int OutputDebugStringA_Addr; 		// OutputDebugStringA Address
    unsigned int WriteProcessMemory_Addr; 		// WriteProcessMemory Address
    unsigned int GetEnvironmentVariableA_Addr; 	// GetEnvironmentVariableA Address
    unsigned int SetEnvironmentVariableA_Addr; 	// SetEnvironmentVariableA Address
    unsigned int LoadLibraryA_Addr; 			// LoadLibraryA Address
    unsigned int GetProcAddress_Addr; 			// GetProcAddress address

    DeleteFile("loaded_binary.mem");
    DumpProcess(IH_fdProcessInfo->hProcess, (void*)g_fdImageBase, (char*)"loaded_binary.mem", g_fdEntryPoint);
    kernel32=GetModuleHandleA("kernel32");

    VirtualProtect_Addr=ImporterGetRemoteAPIAddress(IH_fdProcessInfo->hProcess, (unsigned int)GetProcAddress(kernel32, "VirtualProtect"));
    OutputDebugStringA_Addr=ImporterGetRemoteAPIAddress(IH_fdProcessInfo->hProcess, (unsigned int)GetProcAddress(kernel32, "OutputDebugStringA"));
    GetEnvironmentVariableA_Addr=ImporterGetRemoteAPIAddress(IH_fdProcessInfo->hProcess, (unsigned int)GetProcAddress(kernel32, "GetEnvironmentVariableA"));
    SetEnvironmentVariableA_Addr=ImporterGetRemoteAPIAddress(IH_fdProcessInfo->hProcess, (unsigned int)GetProcAddress(kernel32, "SetEnvironmentVariableA"));
    LoadLibraryA_Addr=ImporterGetRemoteAPIAddress(IH_fdProcessInfo->hProcess, (unsigned int)GetProcAddress(kernel32, "LoadLibraryA"));
    GetProcAddress_Addr=ImporterGetRemoteAPIAddress(IH_fdProcessInfo->hProcess, (unsigned int)GetProcAddress(kernel32, "GetProcAddress"));
    WriteProcessMemory_Addr=ImporterGetRemoteAPIAddress(IH_fdProcessInfo->hProcess, (unsigned int)GetProcAddress(kernel32, "WriteProcessMemory"));

    HANDLE hFile=CreateFileA("loaded_binary.mem", GENERIC_ALL, 0, 0, OPEN_EXISTING, 0, 0);
    DWORD high=0,filesize=GetFileSize(hFile, &high);
    BYTE* dump_addr=(BYTE*)VirtualAlloc(VirtualAlloc(0, filesize+0x1000, MEM_RESERVE, PAGE_EXECUTE_READWRITE), filesize+0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    ReadFile(hFile, dump_addr, filesize, &high, 0);
    CloseHandle(hFile);
    unsigned int result_addr=0;

    // Find VirtualProtect address
    result_addr=FindDwordInMemory(dump_addr, VirtualProtect_Addr, filesize);
    if(result_addr)
        VirtualProtect_Addr=(unsigned int)(result_addr+g_fdImageBase);
    else
        VirtualProtect_Addr=0;

    g_PtrTargetData->VirtualProtect_Addr=VirtualProtect_Addr;


    // Find OutputDebugStringA address
    result_addr=FindDwordInMemory(dump_addr, OutputDebugStringA_Addr, filesize);
    if(result_addr)
        OutputDebugStringA_Addr=(unsigned int)(result_addr+g_fdImageBase);
    else
        OutputDebugStringA_Addr=0;

    g_PtrTargetData->OutputDebugStringA_Addr=OutputDebugStringA_Addr;


    // Find GetEnvironmentVariableA address
    result_addr=FindDwordInMemory(dump_addr, GetEnvironmentVariableA_Addr, filesize);
    if(result_addr)
        GetEnvironmentVariableA_Addr=(unsigned int)(result_addr+g_fdImageBase);
    else
        GetEnvironmentVariableA_Addr=0;

    g_PtrTargetData->GetEnvironmentVariableA_Addr=GetEnvironmentVariableA_Addr;


    // Find SetEnvironmentVariableA address
    result_addr=FindDwordInMemory(dump_addr, SetEnvironmentVariableA_Addr, filesize);
    if(result_addr)
        SetEnvironmentVariableA_Addr=(unsigned int)(result_addr+g_fdImageBase);
    else
        SetEnvironmentVariableA_Addr=0;

    g_PtrTargetData->SetEnvironmentVariableA_Addr=SetEnvironmentVariableA_Addr;


    // Find LoadLibraryA address
    result_addr=FindDwordInMemory(dump_addr, LoadLibraryA_Addr, filesize);
    if(result_addr)
        LoadLibraryA_Addr=(unsigned int)(result_addr+g_fdImageBase);
    else
        LoadLibraryA_Addr=0;

    g_PtrTargetData->LoadLibraryA_Addr=LoadLibraryA_Addr;


    // Find GetProcAddress address
    result_addr=FindDwordInMemory(dump_addr, GetProcAddress_Addr, filesize);
    if(result_addr)
        GetProcAddress_Addr=(unsigned int)(result_addr+g_fdImageBase);
    else
        GetProcAddress_Addr=0;

    g_PtrTargetData->GetProcAddress_Addr=GetProcAddress_Addr;


    // Find WriteProcessMemory address
    result_addr=FindDwordInMemory(dump_addr, WriteProcessMemory_Addr, filesize);
    if(result_addr)
        WriteProcessMemory_Addr=(unsigned int)(result_addr+g_fdImageBase);
    else
        WriteProcessMemory_Addr=0;

    g_PtrTargetData->WriteProcessMemory_Addr=WriteProcessMemory_Addr;

    // Free the memory and close the handle
    VirtualFree(dump_addr, filesize+0x1000, MEM_DECOMMIT);
}