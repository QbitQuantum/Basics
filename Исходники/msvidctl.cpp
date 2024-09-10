KSDDKAPI
HRESULT
WINAPI
DllUnregisterServer(void)
{
    ULONG Index = 0;
    LPOLESTR pStr;
    HRESULT hr = S_OK;
    HKEY hClass;

    if (RegOpenKeyExW(HKEY_CLASSES_ROOT, L"CLSID", 0, KEY_SET_VALUE, &hClass) != ERROR_SUCCESS)
        return E_FAIL;

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