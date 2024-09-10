static HRESULT WINAPI PropertyBag_Read(IPropertyBag *iface, LPCOLESTR pszPropName, VARIANT *pVar, IErrorLog *pErrorLog)
{
    ok(!pErrorLog, "pErrorLog = %p\n", pErrorLog);

    if(!strcmp_wa(pszPropName, "FccHandler")) {
        CHECK_EXPECT(Read_FccHandler);
        V_VT(pVar) = VT_BSTR;
        V_BSTR(pVar) = a2bstr("mrle");
        return S_OK;
    }

    ok(0, "unexpected call: %s\n", wine_dbgstr_w(pszPropName));
    return E_NOTIMPL;
}