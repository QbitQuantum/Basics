IWbemServices * WbemServices::GetPtr()
{
    if (services_) {
        return services_.p;
    }

    HRESULT retval;
    CComPtr<IWbemLocator> locator_;

    retval = CoCreateInstance(
        CLSID_WbemLocator,             
        0, 
        CLSCTX_INPROC_SERVER, 
        IID_IWbemLocator, (LPVOID *) &locator_);

    if (FAILED(retval))	{
        return NULL;
    }

    retval = locator_->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),
        NULL,
        NULL,
        0,
        NULL,
        0,
        0,
        &services_
        );

    if (FAILED(retval)) {
        return NULL;
    }

    CoSetProxyBlanket(
        services_,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE
        );

    return services_.p;
}