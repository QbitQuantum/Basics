KSDDKAPI
HRESULT
WINAPI
DllUnregisterServer(void)
{
    ULONG Index = 0;
    LPOLESTR pStr;
    HRESULT hr = S_OK;
    HKEY hClass;


    hr = StringFromCLSID(KSCATEGORY_BDA_NETWORK_PROVIDER, &pStr);
    if (FAILED(hr))
        return hr;

    if (RegOpenKeyExW(HKEY_CLASSES_ROOT, L"CLSID", 0, KEY_SET_VALUE, &hClass) != ERROR_SUCCESS)
    {
        CoTaskMemFree(pStr);
        return E_FAIL;
    }

    RegDeleteKeyW(hClass, pStr);
    CoTaskMemFree(pStr);

    do
    {
        hr = StringFromCLSID(*InterfaceTable[Index].riid, &pStr);
        if (FAILED(hr))
            break;

        RegDeleteKeyW(hClass, pStr);
        CoTaskMemFree(pStr);
        Index++;
    }while(InterfaceTable[Index].lpfnCI != 0);

    RegCloseKey(hClass);
    return hr;
}