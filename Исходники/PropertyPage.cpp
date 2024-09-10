STDMETHODIMP C[!output Safe_root]PropPage::Apply(void)
{
    WCHAR   wszStr[MAXSTRING] = { 0 };
    double  fScaleFactor = 1.0;

    GetDlgItemText(IDC_SCALEFACTOR, wszStr, sizeof(wszStr) / sizeof(wszStr[0]));
    swscanf_s(wszStr, L"%lf", &fScaleFactor);    

    // make sure scale factor is valid
    if ((fScaleFactor < 0.0) ||
        (fScaleFactor > 1.0))
    {
        if (::LoadString(_Module.GetResourceInstance(), IDS_SCALERANGEERROR, wszStr, sizeof(wszStr) / sizeof(wszStr[0])))
        {
            MessageBox(wszStr);
        }

        return E_FAIL;
    }

    // update the registry
    CRegKey key;
    LONG    lResult;

    lResult = key.Create(HKEY_CURRENT_USER, kwszPrefsRegKey);
    if (ERROR_SUCCESS == lResult)
    {
[!if VSNET]
        DWORD dwValue = (DWORD) (fScaleFactor * 65536);
        lResult = key.SetValue(kwszPrefsScaleFactor, REG_DWORD, &dwValue, sizeof(dwValue));
[!else]
        lResult = key.SetValue((DWORD) (fScaleFactor * 65536), kwszPrefsScaleFactor );
[!endif]
    }