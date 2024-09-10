static void ErrorDump()
{
#if 0
    USES_CONVERSION;
    CDBErrorInfo einfo;
    BSTR bstrDescription;
    ULONG nRecords = 0;
    HRESULT hr = einfo.GetErrorRecords(&nRecords);
    if(SUCCEEDED(hr) && nRecords > 0)
    {
        LCID lcid = GetSystemDefaultLCID();
        for(ULONG nIndex = 0; nIndex < nRecords; nIndex++)
        {
            hr = einfo.GetAllErrorInfo(nIndex, lcid, &bstrDescription);
            if(SUCCEEDED(hr))
            {
                AfxMessageBox(OLE2T(bstrDescription));
                SysFreeString(bstrDescription);
            }
        }
    }
#endif
    USES_CONVERSION;
    CComPtr<IErrorInfo> pErrInfo;
    HRESULT hr = ::GetErrorInfo(0, &pErrInfo);
    if(SUCCEEDED(hr))
    {
        _bstr_t bstrErrDescription;
        pErrInfo->GetDescription((BSTR *) &bstrErrDescription);

        CString strDescription = W2T(bstrErrDescription);
        OutputDebugString(strDescription);

    }
}