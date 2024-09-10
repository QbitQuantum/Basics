BOOL CMemStat::Init()
{
    HRESULT status  = S_OK;
    status = CoInitializeEx(NULL,
                            COINIT_MULTITHREADED);
    if (FAILED(status)) {
        PrintMessage("Cannot initialize COM");
        return status;
    }
    initialized = TRUE;

    status = CoInitializeSecurity(
                             NULL,
                             -1,
                             NULL,
                             NULL,
                             RPC_C_AUTHN_LEVEL_PKT,
                             RPC_C_IMP_LEVEL_IMPERSONATE,
                             NULL,
                             EOAC_NONE,
                             0
                             );

    if (FAILED(status)) {
        PrintMessage("Cannot initialize security");
        return FALSE;
    }

    status = CoCreateInstance(
                             CLSID_WbemLocator,
                             NULL,
                             CLSCTX_INPROC_SERVER,
                             IID_IWbemLocator,
                             reinterpret_cast< void** >( &locator )
                             );

    if (FAILED(status)) {
        PrintMessage("Cannot create instance");
        return FALSE;
    }

    status = locator->ConnectServer(
                             L"root\\cimv2",
                             NULL,
                             NULL,
                             0L,
                             0L,
                             NULL,
                             NULL,
                             &service
                             );
    if (FAILED(status)) {
        PrintMessage("Cannot connect to wmi server");
        return FALSE;
    }

    status = CoSetProxyBlanket(service,
                             RPC_C_AUTHN_WINNT,
                             RPC_C_AUTHZ_NONE,
                             NULL,
                             RPC_C_AUTHN_LEVEL_CALL,
                             RPC_C_IMP_LEVEL_IMPERSONATE,
                             NULL,
                             EOAC_NONE
                             );
    if (FAILED(status)) {
        PrintMessage("Cannot set proxy blanket");
        return FALSE;
    }
    return TRUE;
}