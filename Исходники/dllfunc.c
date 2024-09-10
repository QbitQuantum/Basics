/*
 * RegisterAllClasses()
 */
static HRESULT SetupRegisterAllClasses(const FactoryTemplate * pList, int num,
                                       LPCWSTR szFileName, BOOL bRegister)
{
    HRESULT hr = NOERROR;
    HKEY hkey;
    OLECHAR szCLSID[CHARS_IN_GUID];
    LONG i, ret = RegCreateKeyW(HKEY_CLASSES_ROOT, clsid_keyname, &hkey);
    if (ERROR_SUCCESS != ret)
        return HRESULT_FROM_WIN32(ret);

    for (i = 0; i < num; i++, pList++)
    {
        /* (un)register CLSID and InprocServer32 */
        hr = StringFromGUID2(pList->m_ClsID, szCLSID, CHARS_IN_GUID);
        if (SUCCEEDED(hr))
        {
            if (bRegister )
                hr = SetupRegisterClass(hkey, szCLSID,
                                        pList->m_Name, szFileName,
                                        ips32_keyname, tmodel_both);
            else
                hr = SHDeleteKeyW(hkey, szCLSID);
        }
    }
    RegCloseKey(hkey);
    return hr;
}