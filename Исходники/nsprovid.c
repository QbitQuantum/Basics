DWORD
WSAAPI
WsNpInitialize(IN PNS_PROVIDER Provider,
               IN LPWSTR DllName,
               IN LPGUID ProviderId)
{
    INT ErrorCode = ERROR_SUCCESS;
    LPNSPSTARTUP NSPStartupProc;
    CHAR AnsiPath[MAX_PATH], ExpandedDllPath[MAX_PATH];
    
    /* Convert the path to ANSI */
    WideCharToMultiByte(CP_ACP,
                        0,
                        DllName,
                        -1,
                        AnsiPath,
                        MAX_PATH,
                        NULL,
                        NULL);

    /* Expand the DLL Path */
    ExpandEnvironmentStringsA(AnsiPath,
                              ExpandedDllPath,
                              MAX_PATH);

    /* Load the DLL */
    Provider->DllHandle = LoadLibraryA(ExpandedDllPath);
    if (!Provider->DllHandle)
    {
        /* Fail */
        ErrorCode = WSAEPROVIDERFAILEDINIT;
        goto Fail;
    }

    /* Get the pointer to NSPStartup */
    NSPStartupProc = (LPNSPSTARTUP)GetProcAddress(Provider->DllHandle,
                                                  "NSPStartup");
    if (!NSPStartupProc)
    {
        /* Fail */
        ErrorCode = WSAEPROVIDERFAILEDINIT;
        goto Fail;
    }

    /* Call it */
    (*NSPStartupProc)(ProviderId, (LPNSP_ROUTINE)&Provider->Service.cbSize);

    /* Save the provider ID */
    Provider->ProviderId = *ProviderId;
    return ErrorCode;

Fail:
    /* Bail out */
    if (Provider->DllHandle) FreeLibrary(Provider->DllHandle);
    return ErrorCode;
}