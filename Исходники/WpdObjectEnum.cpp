HRESULT WpdObjectEnumerator::CreateEnumContext(
    __inout         ContextMap*         pContextMap,
    __in            LPCWSTR             pszParentID,
    __deref_out_opt LPWSTR*             ppszEnumContext)
{

    HRESULT         hr              = S_OK;
    GUID            guidContext     = GUID_NULL;
    CComBSTR        bstrContext;
    EnumContext*    pContext        = NULL;

    if((pContextMap     == NULL) ||
       (pszParentID     == NULL) ||
       (ppszEnumContext == NULL))
    {
        hr = E_POINTER;
        CHECK_HR(hr, "Cannot have NULL parameter");
        return hr;
    }

    *ppszEnumContext = NULL;

    hr = CoCreateGuid(&guidContext);
    if (hr == S_OK)
    {
        bstrContext = guidContext;
        if(bstrContext.Length() == 0)
        {
            hr = E_OUTOFMEMORY;
            CHECK_HR(hr, "Failed to create BSTR from GUID");
        }
    }

    if (hr == S_OK)
    {
        pContext = new EnumContext();
        if(pContext != NULL)
        {
            CAtlStringW strKey = bstrContext;
            pContext->ParentID = pszParentID;

            hr = pContextMap->Add(strKey, pContext);
            CHECK_HR(hr, "Failed to add enumeration context to client context map");

            pContext->Release();
        }
        else
        {
            hr = E_OUTOFMEMORY;
            CHECK_HR(hr, "Failed to allocate enumeration context");
        }
    }

    if (hr == S_OK)
    {
        *ppszEnumContext = AtlAllocTaskWideString(bstrContext);
    }

    return hr;
}