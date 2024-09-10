HRESULT CRegisterExtension::RegSetKeyValueBinaryPrintf(HKEY hkey, PCWSTR pszKeyFormatString, PCWSTR pszValueName, PCSTR pszBase64, ...) const
{
    va_list argList;
    va_start(argList, pszBase64);

    WCHAR szKeyName[512];
    HRESULT hr = StringCchVPrintf(szKeyName, ARRAYSIZE(szKeyName), pszKeyFormatString, argList);
    if (SUCCEEDED(hr))
    {
        DWORD dwDecodedImageSize, dwSkipChars, dwActualFormat;
        hr = CryptStringToBinaryA(pszBase64, NULL, CRYPT_STRING_BASE64, NULL,
            &dwDecodedImageSize, &dwSkipChars, &dwActualFormat) ? S_OK : E_FAIL;
        if (SUCCEEDED(hr))
        {
            BYTE *pbDecodedImage = (BYTE*)LocalAlloc(LPTR, dwDecodedImageSize);
            hr = pbDecodedImage ? S_OK : E_OUTOFMEMORY;
            if (SUCCEEDED(hr))
            {
                hr = CryptStringToBinaryA(pszBase64, lstrlenA(pszBase64), CRYPT_STRING_BASE64,
                    pbDecodedImage, &dwDecodedImageSize, &dwSkipChars, &dwActualFormat) ? S_OK : E_FAIL;
                if (SUCCEEDED(hr))
                {
                    hr = HRESULT_FROM_WIN32(RegSetKeyValueW(hkey, szKeyName, pszValueName, REG_BINARY, pbDecodedImage, dwDecodedImageSize));
                }
            }
        }
    }

    va_end(argList);

    _UpdateAssocChanged(hr, pszKeyFormatString);
    return hr;
}