//--------------------------------------------------------------------------------------
VOID WDBGAPI WinDbgExtensionDllInit(
    PWINDBG_EXTENSION_APIS lpExtensionApis, 
    USHORT usMajorVersion, USHORT usMinorVersion)
{
    if (g_RefCount > 0)
    {
        // extension is allready initialized
        return;
    }

    HRESULT Hr = DebugCreate(__uuidof(IDebugClient), (void **)&g_Client);
    if (Hr != S_OK)
    {
        MessageBoxA(0, "DebugCreate() fails", __FUNCTION__, MB_ICONERROR);
        return;
    }

    Hr = g_Client->QueryInterface(__uuidof(IDebugControl), (void **)&g_Control);
    if (Hr != S_OK)
    {    
        MessageBoxA(
            0, 
            "DebugClient::QueryInterface(IDebugControl) fails", 
            __FUNCTION__, MB_ICONERROR
        );

        ExitProcess(0);
    }

    ULONG TargetMachine = 0;
    Hr = g_Control->GetActualProcessorType(&TargetMachine);
    if (Hr == S_OK)
    {                                                     
        switch (TargetMachine)
        {
        case IMAGE_FILE_MACHINE_I386:
            
            g_bIs64 = FALSE;
            g_RegPtrType = DEBUG_VALUE_INT32;
            break;


        case IMAGE_FILE_MACHINE_AMD64:

            g_bIs64 = TRUE;
            g_RegPtrType = DEBUG_VALUE_INT64;
            break;

        default:

            MessageBoxA(
                0, 
                "Target architecture is not supported", 
                __FUNCTION__, MB_ICONERROR
            );

            ExitProcess(0);

            break;
        }
    }
    else
    {
        MessageBoxA(
            0, 
            "DebugControl::GetActualProcessorType() fails", 
            __FUNCTION__, MB_ICONERROR
        );

        ExitProcess(0);
    }

    Hr = g_Client->QueryInterface(__uuidof(IDebugSymbols3), (void **)&g_Symbols);
    if (Hr != S_OK)
    {    
        MessageBoxA(
            0, 
            "DebugClient::QueryInterface(IDebugSymbols3) fails", 
            __FUNCTION__, MB_ICONERROR
        );

        ExitProcess(0);
    }

    Hr = g_Client->QueryInterface(__uuidof(IDebugSystemObjects), (void **)&g_SystemObjects);
    if (Hr != S_OK)
    {    
        MessageBoxA(
            0, 
            "DebugClient::QueryInterface(IDebugSystemObjects) fails", 
            __FUNCTION__, MB_ICONERROR
        );

        ExitProcess(0);
    }

    Hr = g_Client->QueryInterface(__uuidof(IDebugRegisters), (void **)&g_Registers);
    if (Hr != S_OK)
    {    
        MessageBoxA(
            0, 
            "DebugClient::QueryInterface(IDebugRegisters) fails", 
            __FUNCTION__, MB_ICONERROR
        );

        ExitProcess(0);
    }

    Hr = g_Client->QueryInterface(__uuidof(IDebugDataSpaces), (void **)&g_DataSpaces);
    if (Hr != S_OK)
    {    
        MessageBoxA(
            0, 
            "DebugClient::QueryInterface(IDebugDataSpaces) fails", 
            __FUNCTION__, MB_ICONERROR
        );

        ExitProcess(0);
    }

    char *lpszEip = "eip", *lpszEax = "eax", *lpszEcx = "ecx";
    if (g_bIs64)
    {
        // use 64-bit registers for parameter and return value
        lpszEip = "rip";
        lpszEax = "rax";
        lpszEcx = "rcx";
    }

    // Find the register index for eip/rip
    Hr = g_Registers->GetIndexByName(lpszEip, &g_EipIndex);
    if (Hr != S_OK)
    {
        MessageBoxA(
            0, 
            "DebugRegisters::GetIndexByName() fails", 
            __FUNCTION__, MB_ICONERROR
        );

        ExitProcess(0);
    }    

    // Find the register index for eax/rax
    Hr = g_Registers->GetIndexByName(lpszEax, &g_EaxIndex);
    if (Hr != S_OK)
    {
        MessageBoxA(
            0, 
            "DebugRegisters::GetIndexByName() fails", 
            __FUNCTION__, MB_ICONERROR
        );

        ExitProcess(0);
    }    

    // Find the register index for ecx/rcx
    Hr = g_Registers->GetIndexByName(lpszEcx, &g_EcxIndex);
    if (Hr != S_OK)
    {
        MessageBoxA(
            0, 
            "DebugRegisters::GetIndexByName() fails", 
            __FUNCTION__, MB_ICONERROR
        );

        ExitProcess(0);
    }

    // Find the register index for edx
    Hr = g_Registers->GetIndexByName("edx", &g_EdxIndex);
    if (Hr != S_OK)
    {
        MessageBoxA(
            0, 
            "DebugRegisters::GetIndexByName() fails", 
            __FUNCTION__, MB_ICONERROR
        );

        ExitProcess(0);
    }

    // Register our event callbacks.
    Hr = g_Client->SetEventCallbacks(&g_EventCb);
    if (Hr != S_OK)
    {
        MessageBoxA(
            0, 
            "DebugClient::SetEventCallbacks() fails", 
            __FUNCTION__, MB_ICONERROR
        );

        ExitProcess(0);
    }

    ExtOut("<col fg=\"srckw\">" __FUNCTION__"(): Initialized (x64: %s)</col>\n", g_bIs64 ? "Yes" : "No");
}