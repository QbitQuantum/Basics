// DllInstall - Adds/Removes entries to the system registry per user per machine.
STDAPI DllInstall(BOOL bInstall, _In_opt_ LPCWSTR pszCmdLine)
{
    UNREFERENCED_PARAMETER(pszCmdLine);
    HRESULT hr = E_FAIL;
    static const wchar_t szUserSwitch[] = L"user";


    if (bInstall)
    {	
        hr = DllRegisterServer();
        if (FAILED(hr))
        {
            DllUnregisterServer();
        }
    }
    else
    {
        hr = DllUnregisterServer();
    }

    return hr;
}