HRESULT
CALLBACK
DebugExtensionInitialize(PULONG Version, PULONG Flags)
{
    HRESULT hRes=S_OK;
    IDebugClient *DebugClient;
    PDEBUG_CONTROL DebugControl;

    *Version = DEBUG_EXTENSION_VERSION(EXT_MAJOR_VER, EXT_MINOR_VER);
    *Flags = 0;

    if (FAILED(hRes=DebugCreate(__uuidof(IDebugClient), (void **)&DebugClient)))
        return hRes;

    if (SUCCEEDED(hRes=DebugClient->QueryInterface(__uuidof(IDebugControl),  (void **)&DebugControl)))
    {
        // Get the windbg-style extension APIS
        ExtensionApis.nSize = sizeof (ExtensionApis);
        hRes = DebugControl->GetWindbgExtensionApis64(&ExtensionApis);
        DebugControl->Release();
        dprintf("[sync] DebugExtensionInitialize, ExtensionApis loaded\n");
    }

    DebugClient->Release();
    g_ExtClient = NULL;
    g_Synchronized = FALSE;

    g_hPollCompleteEvent = CreateEvent(NULL, true, false, NULL);
    if (g_hPollCompleteEvent == NULL)
    {
        dprintf("[sync] Command polling feature init failed\n");
        return E_FAIL;
    }

    InitializeCriticalSection(&g_CritSectPollRelease);

    if(SUCCEEDED(LoadConfigurationFile()))
        dprintf("[sync] Configuration file loaded\n       -> set HOST to %s:%s\n", g_DefaultHost, g_DefaultPort);

    return hRes;
}