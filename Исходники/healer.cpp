void
CreateInterfaces(void)
{
    SYSTEM_INFO SysInfo;
    
    // For purposes of keeping this example simple the
    // code only works on x86 machines.  There's no reason
    // that it couldn't be made to work on all processors, though.
    GetSystemInfo(&SysInfo);
    if (SysInfo.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_INTEL)
    {
        Exit(1, "This program only runs on x86 machines.\n");
    }

    // Get default version information.
    g_OsVer.dwOSVersionInfoSize = sizeof(g_OsVer);
    if (!GetVersionEx(&g_OsVer))
    {
        Exit(1, "GetVersionEx failed, %d\n", GetLastError());
    }

    HRESULT Status;

    // Start things off by getting an initial interface from
    // the engine.  This can be any engine interface but is
    // generally IDebugClient as the client interface is
    // where sessions are started.
    if ((Status = DebugCreate(__uuidof(IDebugClient),
                              (void**)&g_Client)) != S_OK)
    {
        Exit(1, "DebugCreate failed, 0x%X\n", Status);
    }

    // Query for some other interfaces that we'll need.
    if ((Status = g_Client->QueryInterface(__uuidof(IDebugControl),
                                           (void**)&g_Control)) != S_OK ||
        (Status = g_Client->QueryInterface(__uuidof(IDebugDataSpaces),
                                           (void**)&g_Data)) != S_OK ||
        (Status = g_Client->QueryInterface(__uuidof(IDebugRegisters),
                                           (void**)&g_Registers)) != S_OK ||
        (Status = g_Client->QueryInterface(__uuidof(IDebugSymbols),
                                           (void**)&g_Symbols)) != S_OK)
    {
        Exit(1, "QueryInterface failed, 0x%X\n", Status);
    }
}