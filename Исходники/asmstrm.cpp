HRESULT CAssemblyStream::Init (LPCOLESTR pszPath, DWORD dwFormat)
{
    HRESULT                            hr = S_OK;
    DWORD                              cwPath;
    BOOL                               bRet;

    _ASSERTE(pszPath);

    _dwFormat = dwFormat;
    cwPath = lstrlenW(pszPath) + 1;

    _ASSERTE(cwPath < MAX_PATH);
    memcpy(_szPath, pszPath, sizeof(TCHAR) * cwPath);

    _hf = WszCreateFile(pszPath, GENERIC_WRITE, 0 /* no sharing */,
                     NULL, CREATE_NEW, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (_hf == INVALID_HANDLE_VALUE) {
        hr = HRESULT_FROM_WIN32(GetLastError());
        ReleaseParent(hr);
        goto Exit;
    }

    if (!g_hProv) {
        HCRYPTPROV hProv;
  
        bRet = CryptAcquireContextA(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
        if (!bRet) {
            hr = HRESULT_FROM_WIN32(GetLastError());
            ReleaseParent(hr);
            goto Exit;

        }

        if (InterlockedCompareExchangePointer((void **)&g_hProv, (void *)hProv, 0)) {
            // Lost the race. Release our provider.
            CryptReleaseContext(hProv, 0);
        }
    }

    bRet = CryptCreateHash(g_hProv, CALG_SHA1, 0, 0, &_hHash);
    if (!bRet) {
        hr = HRESULT_FROM_WIN32(GetLastError());
        ReleaseParent(hr);
        goto Exit;
    }

Exit:
    return hr;
}