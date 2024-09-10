HRESULT WINAPI CRecycleBinDeskBand::UpdateRegistry(_In_ BOOL bRegister)
{
    LOG("UpdateRegistry()");
    LOG2("  bRegister", bRegister);

    HRESULT hr = S_OK;

    if (bRegister)
    {
        WCHAR szCLSID[MAX_PATH];
        StringFromGUID2(CLSID_RecycleBinDeskBand, szCLSID, ARRAYSIZE(szCLSID));

        WCHAR szSubkey[MAX_PATH];
        HKEY hKey;

        hr = StringCchPrintfW(szSubkey, ARRAYSIZE(szSubkey), L"CLSID\\%s", szCLSID);
        if (SUCCEEDED(hr))
        {
            hr = E_FAIL;
            if (ERROR_SUCCESS == RegCreateKeyExW(HKEY_CLASSES_ROOT,
                szSubkey,
                0,
                NULL,
                REG_OPTION_NON_VOLATILE,
                KEY_WRITE,
                NULL,
                &hKey,
                NULL))
            {
                WCHAR const szName[] = L"Recyclebin"; // TODO: externalize
                //WCHAR szName[MAX_PATH];
                //ExtractRecycleBinName(szName, ARRAYSIZE(szName));

                if (ERROR_SUCCESS == RegSetValueExW(hKey,
                    NULL,
                    0,
                    REG_SZ,
                    (LPBYTE)szName,
                    sizeof(szName)))
                {
                    hr = S_OK;
                }

                RegCloseKey(hKey);
            }
        }

        if (SUCCEEDED(hr))
        {
            hr = StringCchPrintfW(szSubkey, ARRAYSIZE(szSubkey), L"CLSID\\%s\\InprocServer32", szCLSID);
            if (SUCCEEDED(hr))
            {
                hr = HRESULT_FROM_WIN32(RegCreateKeyExW(HKEY_CLASSES_ROOT, szSubkey,
                    0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL));
                if (SUCCEEDED(hr))
                {
                    WCHAR szModule[MAX_PATH];
                    if (GetModuleFileNameW(g_hInst, szModule, ARRAYSIZE(szModule)))
                    {
                        DWORD cch = lstrlen(szModule);
                        hr = HRESULT_FROM_WIN32(RegSetValueExW(hKey, NULL, 0, REG_SZ, (LPBYTE)szModule, cch * sizeof(szModule[0])));
                    }

                    if (SUCCEEDED(hr))
                    {
                        WCHAR const szModel[] = L"Apartment";
                        hr = HRESULT_FROM_WIN32(RegSetValueExW(hKey, L"ThreadingModel", 0, REG_SZ, (LPBYTE)szModel, sizeof(szModel)));
                    }

                    RegCloseKey(hKey);
                }
            }
        }
    }
    else
    {
        WCHAR szCLSID[MAX_PATH];
        StringFromGUID2(CLSID_RecycleBinDeskBand, szCLSID, ARRAYSIZE(szCLSID));
        
        WCHAR szSubkey[MAX_PATH];
        HRESULT hr = StringCchPrintfW(szSubkey, ARRAYSIZE(szSubkey), L"CLSID\\%s", szCLSID);
        if (SUCCEEDED(hr))
        {
            if (ERROR_SUCCESS != RegDeleteTreeW(HKEY_CLASSES_ROOT, szSubkey))
            {
                hr = E_FAIL;
            }
        }
        
        return SUCCEEDED(hr) ? S_OK : SELFREG_E_CLASS;
    }

    LOG2("  hr", hr);

    return hr;
}