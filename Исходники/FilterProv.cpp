DWORD
PXEAPI
PxeProviderInitialize(
    __in HANDLE hProvider,
    __in HKEY hProviderKey
)
/*++

Routine Description:

    This function is called by WDS PXE to initialize Filter Provider.

Arguments:

    hProvider       -   Handle to Provider.
    hProviderKey    -   Handle to registry store where Provider should store
                        its configuration information.

Return Value:

    ERROR_SUCCESS on success. On failure appropriate Win32 Error Code is 
    returned.

--*/
{
    DWORD dwError = ERROR_SUCCESS;
    HRESULT hr = S_OK;
    ULONG uFilter = PXE_PROV_FILTER_PXE_ONLY;

    UNREFERENCED_PARAMETER(hProviderKey);

    //
    // Read Policy Settings.
    //
    dwError = InitializeConfiguration();
    W32_CLEANUP_ON_FAILURE(dwError, Cleanup);

    //
    // Register Shutdown Callback.
    //
    dwError = PxeRegisterCallback(hProvider,
                                  PXE_CALLBACK_SHUTDOWN,
                                  PxeProviderShutdown,
                                  NULL);
    W32_CLEANUP_ON_FAILURE(dwError, Cleanup);

    //
    // Register Request Processing Callback.
    //
    dwError = PxeRegisterCallback(hProvider,
                                  PXE_CALLBACK_RECV_REQUEST,
                                  PxeProviderRecvRequest,
                                  NULL);
    W32_CLEANUP_ON_FAILURE(dwError, Cleanup);
    
    //
    // Define filter to only receive requests which are valid Dhcp Packets and
    // contain Option 60 'PXEClient'.
    //
    dwError = PxeProviderSetAttribute(hProvider,
                                      PXE_PROV_ATTR_FILTER,
                                      &uFilter,
                                      sizeof(uFilter));
    W32_CLEANUP_ON_FAILURE(dwError, Cleanup);

    //
    // Save Provider Handle.
    //
    g_hFilterProvider = hProvider;
    
Cleanup:
    return dwError;
}