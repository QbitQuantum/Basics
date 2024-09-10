BOOL
InitCOMAccess ()
/*++

Routine Description:

    Register COM interfaces with WCT.  This allows WCT to provide wait
    information if a thread is blocked on a COM call.

--*/
{
    HMODULE               ModuleHandle = NULL;
    PCOGETCALLSTATE       CallStateCallback;
    PCOGETACTIVATIONSTATE ActivationStateCallback;

    // Get a handle to OLE32.DLL.  We need to keep this handle around
    // for the life time for any WCT session.
    g_Ole32Hnd = LoadLibrary(L"ole32.dll");
    if (!g_Ole32Hnd)
    {
        printf("ERROR: GetModuleHandle failed: 0x%X\n", GetLastError());
        return FALSE;
    }

    // Retrieve the function addresses for the COM helper APIs.
    CallStateCallback = (PCOGETCALLSTATE)
        GetProcAddress(g_Ole32Hnd, "CoGetCallState");
    if (!CallStateCallback)
    {
        printf("ERROR: GetProcAddress failed: 0x%X\n", GetLastError());
        return FALSE;
    }

    ActivationStateCallback = (PCOGETACTIVATIONSTATE)
        GetProcAddress(g_Ole32Hnd, "CoGetActivationState");
    if (!ActivationStateCallback)
    {
        printf("ERROR: GetProcAddress failed: 0x%X\n", GetLastError());
        return FALSE;
    }

    // Register these functions with WCT.
    RegisterWaitChainCOMCallback(CallStateCallback,
                                 ActivationStateCallback);
    return TRUE;
}