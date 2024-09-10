static HRESULT WINAPI RegistryPropertyBag_IPropertyBag_Read(IPropertyBag *iface,
    LPCOLESTR pwszPropName, VARIANT *pVar, IErrorLog *pErrorLog)
{
    RegistryPropertyBag *This = ADJUST_THIS(RegistryPropertyBag, IPropertyBag, iface);
    WCHAR *pwszValue;
    DWORD dwType, cbData;
    LONG res;
    VARTYPE vtDst = V_VT(pVar);
    HRESULT hr = S_OK;

    TRACE("(iface=%p, pwszPropName=%s, pVar=%p, pErrorLog=%p)\n", iface, debugstr_w(pwszPropName), 
          pVar, pErrorLog);

    res = RegQueryValueExW(This->m_hInitPropertyBagKey, pwszPropName, NULL, &dwType, NULL, &cbData);
    if (res != ERROR_SUCCESS) 
        return E_INVALIDARG;

    pwszValue = shdocvw_alloc(cbData);
    if (!pwszValue)
        return E_OUTOFMEMORY;
 
    res = RegQueryValueExW(This->m_hInitPropertyBagKey, pwszPropName, NULL, &dwType, 
                           (LPBYTE)pwszValue, &cbData);
    if (res != ERROR_SUCCESS) {
        shdocvw_free(pwszValue);
        return E_INVALIDARG;
    }

    V_VT(pVar) = VT_BSTR;
    V_BSTR(pVar) = SysAllocString(pwszValue);
    shdocvw_free(pwszValue);

    if (vtDst != VT_BSTR) {
        hr = VariantChangeTypeEx(pVar, pVar, LOCALE_SYSTEM_DEFAULT, 0, vtDst);
        if (FAILED(hr))
            SysFreeString(V_BSTR(pVar));
    }

    return hr;    
}