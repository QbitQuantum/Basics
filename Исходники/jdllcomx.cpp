STDMETHODIMP CJServer::GetTypeInfo(UINT itInfo, LCID lcid, ITypeInfo **ppITypeInfo)
{
    HRESULT     hr;
    ITypeLib   *pITypeLib;
    ITypeInfo **ppITI=NULL;

    if (0!=itInfo) return TYPE_E_ELEMENTNOTFOUND;

    if (NULL==ppITypeInfo) return E_POINTER;

    *ppITypeInfo=NULL;
    switch (PRIMARYLANGID(lcid))
    {
        case LANG_NEUTRAL:
        case LANG_ENGLISH:
            ppITI=&m_pITINeutral;
            break;

        default:
            return DISP_E_UNKNOWNLCID;
    }

    //Load a type lib if we don't have the information already.
    if (NULL==*ppITI)
    {
        hr=LoadRegTypeLib(jlibid, atoi(jversion), 0, PRIMARYLANGID(lcid), &pITypeLib);
        if (FAILED(hr)) return hr;

        //Got the type lib, get type info for the interface we want
        hr=pITypeLib->GetTypeInfoOfGuid(jiid, ppITI);
        pITypeLib->Release();
        if (FAILED(hr)) return hr;
	}

	// the type library is still loaded since we have an ITypeInfo from it.
    (*ppITI)->AddRef();
    *ppITypeInfo=*ppITI;
    return NOERROR;
}