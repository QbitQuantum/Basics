STDMETHODIMP CMyDevicePropertySheet::QueryInterface(__in REFIID riid, __deref_out void **ppv)
{
    static const QITAB qit[] =
    {
        QITABENT(CMyDevicePropertySheet, IShellExtInit),
        QITABENT(CMyDevicePropertySheet, IShellPropSheetExt),
        { 0 },
    };

    return QISearch(this, qit, riid, ppv);

} //*** CMyDevicePropertySheet::QueryInterface