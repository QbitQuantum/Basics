//------------------------------------------------------------------------------
// CSimpleThermostatService::InitStdDispatch
//      Creates the standard dispatch object that will be used when IDispatch
//      is requested from this object. The UPnP device object will call this
//      function immediately after instantiation of this object.
//------------------------------------------------------------------------------
HRESULT CSimpleThermostatService::InitStdDispatch()
{
    HRESULT     hr          = S_OK;
    ITypeLib*   pTypeLib    = NULL;

    hr = LoadRegTypeLib(
        LIBID_SimpleThermostatDeviceLib,
        1,
        0,
        LANG_NEUTRAL,
        &pTypeLib
        );

    if( S_OK == hr )
    {
        hr = pTypeLib->GetTypeInfoOfGuid(
            __uuidof(ISimpleThermostat_UPnPService),
            &m_pTypeInfo
            );
        pTypeLib->Release();
    }

    if( S_OK == hr )
    {
        hr = CreateStdDispatch(
            reinterpret_cast<IUnknown*>(this),
            this,
            m_pTypeInfo,
            &m_pUnkStdDispatch
            );
    }

    return hr;
}// CSimpleThermostatService::InitStdDispatch