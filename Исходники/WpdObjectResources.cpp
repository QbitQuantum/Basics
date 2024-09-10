HRESULT WpdObjectResources::CreateResourceContext(
    __inout         ContextMap*     pContextMap,
    __in            LPCWSTR         pszObjectID,
    __in            REFPROPERTYKEY  ResourceKey,
    __in            BOOL            bCreateRequest,
    __deref_out_opt LPWSTR*         ppszResourceContext)
{

    HRESULT         hr              = S_OK;
    GUID            guidContext     = GUID_NULL;
    ResourceContext* pContext       = NULL;

    if((pContextMap         == NULL) ||
       (pszObjectID         == NULL) ||
       (ppszResourceContext == NULL))
    {
        hr = E_POINTER;
        CHECK_HR(hr, "Cannot have NULL parameter");
        return hr;
    }

    *ppszResourceContext = NULL;

    if (hr == S_OK)
    {
        hr = CoCreateGuid(&guidContext);
        CHECK_HR(hr, "Failed to CoCreateGuid used for identifying the resource context");
    }

    if (hr == S_OK)
    {
        pContext = new ResourceContext();
        if(pContext == NULL)
        {
            hr = E_OUTOFMEMORY;
            CHECK_HR(hr, "Failed to allocate new resource context");
        }
    }

    if (hr == S_OK)
    {
        pContext->ObjectID      = pszObjectID;
        pContext->Key           = ResourceKey;
        pContext->CreateRequest = bCreateRequest;

        CAtlStringW strKey = CComBSTR(guidContext);
        hr = pContextMap->Add(strKey, pContext);
        CHECK_HR(hr, "Failed to insert bulk property operation context into our context Map");
    }

    if (hr == S_OK)
    {
        hr = StringFromCLSID(guidContext, ppszResourceContext);
        CHECK_HR(hr, "Failed to allocate string from GUID for resource context");
    }

    SAFE_RELEASE(pContext);

    return hr;
}