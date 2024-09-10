static
RPC_STATUS
DsSetupBind(
    LPWSTR lpServerName,
    handle_t *hBinding)
{
    LPWSTR pszStringBinding;
    RPC_STATUS status;

    TRACE("DsSetupBind() called\n");

    *hBinding = NULL;

    status = RpcStringBindingComposeW(NULL,
                                      L"ncacn_np",
                                      lpServerName,
                                      L"\\pipe\\lsarpc",
                                      NULL,
                                      &pszStringBinding);
    if (status)
    {
        TRACE("RpcStringBindingCompose returned 0x%x\n", status);
        return status;
    }

    /* Set the binding handle that will be used to bind to the server. */
    status = RpcBindingFromStringBindingW(pszStringBinding,
                                          hBinding);
    if (status)
    {
        TRACE("RpcBindingFromStringBinding returned 0x%x\n", status);
    }

    status = RpcStringFreeW(&pszStringBinding);
    if (status)
    {
        TRACE("RpcStringFree returned 0x%x\n", status);
    }

    return status;
}