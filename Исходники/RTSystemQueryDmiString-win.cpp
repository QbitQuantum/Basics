/**
 * Connect to the DMI server.
 *
 * @returns COM status code.
 * @param   pLocator            The locator.
 * @param   pszServer           The server name.
 * @param   ppServices          Where to return the services interface.
 */
static HRESULT rtSystemDmiWinConnectToServer(IWbemLocator *pLocator, const char *pszServer, IWbemServices **ppServices)
{
    AssertPtr(pLocator);
    AssertPtrNull(pszServer);
    AssertPtr(ppServices);

    BSTR pBStrServer = rtSystemWinBstrFromUtf8(pszServer);
    if (!pBStrServer)
        return E_OUTOFMEMORY;

    HRESULT hrc = pLocator->ConnectServer(pBStrServer,
                                          NULL,
                                          NULL,
                                          0,
                                          NULL,
                                          0,
                                          0,
                                          ppServices);
    if (SUCCEEDED(hrc))
    {
        hrc = CoSetProxyBlanket(*ppServices,
                                RPC_C_AUTHN_WINNT,
                                RPC_C_AUTHZ_NONE,
                                NULL,
                                RPC_C_AUTHN_LEVEL_CALL,
                                RPC_C_IMP_LEVEL_IMPERSONATE,
                                NULL,
                                EOAC_NONE);
        if (FAILED(hrc))
            (*ppServices)->Release();
    }
    SysFreeString(pBStrServer);
    return hrc;
}