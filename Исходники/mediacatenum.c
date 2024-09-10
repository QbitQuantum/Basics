static HRESULT WINAPI DEVENUM_IPropertyBag_Write(
    LPPROPERTYBAG iface,
    LPCOLESTR pszPropName,
    VARIANT* pVar)
{
    RegPropBagImpl *This = impl_from_IPropertyBag(iface);
    LPVOID lpData = NULL;
    DWORD cbData = 0;
    DWORD dwType = 0;
    HRESULT res = S_OK;

    TRACE("(%p)->(%s, %p)\n", This, debugstr_w(pszPropName), pVar);

    switch (V_VT(pVar))
    {
    case VT_BSTR:
    case VT_LPWSTR:
        TRACE("writing %s\n", debugstr_w(V_UNION(pVar, bstrVal)));
        lpData = V_UNION(pVar, bstrVal);
        dwType = REG_SZ;
        cbData = (lstrlenW(V_UNION(pVar, bstrVal)) + 1) * sizeof(WCHAR);
        break;
    case VT_I4:
    case VT_UI4:
        TRACE("writing %u\n", V_UNION(pVar, ulVal));
        lpData = &V_UNION(pVar, ulVal);
        dwType = REG_DWORD;
        cbData = sizeof(DWORD);
        break;
    case VT_ARRAY | VT_UI1:
    {
        LONG lUbound = 0;
        LONG lLbound = 0;
        dwType = REG_BINARY;
        res = SafeArrayGetLBound(V_UNION(pVar, parray), 1, &lLbound);
        res = SafeArrayGetUBound(V_UNION(pVar, parray), 1, &lUbound);
        cbData = (lUbound - lLbound + 1) /* * sizeof(BYTE)*/;
        TRACE("cbData: %d\n", cbData);
        res = SafeArrayAccessData(V_UNION(pVar, parray), &lpData);
        break;
    }
    default:
        FIXME("Variant type %d not handled\n", V_VT(pVar));
        return E_FAIL;
    }

    if (RegSetValueExW(This->hkey,
                       pszPropName, 0,
                       dwType, lpData, cbData) != ERROR_SUCCESS)
        res = E_FAIL;

    if (V_VT(pVar) & VT_ARRAY)
        res = SafeArrayUnaccessData(V_UNION(pVar, parray));

    return res;
}