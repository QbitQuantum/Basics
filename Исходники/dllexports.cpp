/**
 * DllInstall - Adds/Removes entries to the system registry per user per machine.
 */
STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
    logger->debug(L"BHO::dllexports::DllInstall");
    HRESULT hr = E_FAIL;
    static const wchar_t szUserSwitch[] = L"user";

    if (pszCmdLine != NULL) {
        if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0) {
            ATL::AtlSetPerUserRegistration(true);
        }
    }

    if (bInstall) {	
        hr = DllRegisterServer();
        if (FAILED(hr)) {
            DllUnregisterServer();
        }
    } else {
        hr = DllUnregisterServer();
    }

    return hr;
}