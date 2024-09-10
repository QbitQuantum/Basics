HRESULT
CALLBACK
DebugExtensionInitialize(PULONG Version, PULONG Flags)
{
    IDebugClient *DebugClient;
    PDEBUG_CONTROL DebugControl;
    HRESULT Hr;

    *Version = DEBUG_EXTENSION_VERSION(1, 0);
    *Flags = 0;

    if (g_Initialized)
    {
        return S_OK;
    }
    g_Initialized = true;

    if ((Hr = DebugCreate(__uuidof(IDebugClient),
                          (void **)&DebugClient)) != S_OK)
    {
        return Hr;
    }
    if ((Hr = DebugClient->QueryInterface(__uuidof(IDebugControl),
                                              (void **)&DebugControl)) != S_OK)
    {
        return Hr;
    }

    ExtensionApis.nSize = sizeof (ExtensionApis);
    if ((Hr = DebugControl->GetWindbgExtensionApis64(&ExtensionApis)) != S_OK)
    {
        return Hr;
    }
    
    // Fixes the "Unable to read dynamic function table entries" error messages by disabling the WinDbg security
    // feature that prevents the loading of unknown out of proc tack walkers.
    DebugControl->Execute(DEBUG_OUTCTL_IGNORE, ".settings set EngineInitialization.VerifyFunctionTableCallbacks=false", 
        DEBUG_EXECUTE_NOT_LOGGED | DEBUG_EXECUTE_NO_REPEAT);

    ExtQuery(DebugClient);
    if (IsMiniDumpFileNODAC())
    {
        ExtOut (
            "----------------------------------------------------------------------------\n"
            "The user dump currently examined is a minidump. Consequently, only a subset\n"
            "of sos.dll functionality will be available. If needed, attaching to the live\n"
            "process or debugging a full dump will allow access to sos.dll's full feature\n"
            "set.\n"
            "To create a full user dump use the command: .dump /ma <filename>\n"
            "----------------------------------------------------------------------------\n");
    }
    ExtRelease();
    
    OnUnloadTask::Register(CleanupEventCallbacks);
    g_pCallbacksClient = DebugClient;
    EventCallbacks* pCallbacksObj = new EventCallbacks(DebugClient);
    IDebugEventCallbacks* pCallbacks = NULL;
    pCallbacksObj->QueryInterface(__uuidof(IDebugEventCallbacks), (void**)&pCallbacks);
    pCallbacksObj->Release();

    if(FAILED(Hr = g_pCallbacksClient->SetEventCallbacks(pCallbacks)))
    {
        ExtOut ("SOS: Failed to register callback events\n");
        pCallbacks->Release();
        return Hr;
    }
    pCallbacks->Release();

#ifndef _ARM_
    // Make sure we do not tear down the debugger when a security function fails
    // Since we link statically against CRT this will only affect the SOS module.
    _set_invalid_parameter_handler(_SOS_invalid_parameter);
#endif
    
    DebugControl->Release();
    return S_OK;
}