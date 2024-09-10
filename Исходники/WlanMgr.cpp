HRESULT 
CWlanManager::GetHostedNetworkKey(
    CAtlString& strKey
    )
{
    HRESULT hr = S_OK;
    DWORD dwError = ERROR_SUCCESS;

    BOOL bIsPassPhrase = FALSE;
    BOOL bPersistent = FALSE;
    PUCHAR pucSecondaryKey = NULL;
    DWORD dwSecondaryKeyLength = 0;
    WCHAR strSecondaryKey[WLAN_MAX_NAME_LENGTH];
    
    // get the user security key
    dwError = WlanHostedNetworkQuerySecondaryKey(
                m_WlanHandle,
                &dwSecondaryKeyLength,
                &pucSecondaryKey,
                &bIsPassPhrase,
                &bPersistent,
                NULL,
                NULL
                );

    BAIL_ON_WIN32_ERROR(dwError, hr);

    int cchKey = 0;
    if (dwSecondaryKeyLength > 0)
    {
        // Must be passphrase
        _ASSERT(bIsPassPhrase);
        // convert the key
        if (bIsPassPhrase)
        {
            #pragma prefast(suppress:26035, "If the key is a pass phrase, it is guaranteed to be null-terminated.")
            cchKey = MultiByteToWideChar(
                        CP_ACP, 
                        MB_ERR_INVALID_CHARS,
                        (LPCSTR)pucSecondaryKey,
                        dwSecondaryKeyLength,
                        strSecondaryKey, 
                        sizeof(strSecondaryKey) / sizeof(strSecondaryKey[0]) -1
                        );
        }
    }

    if(cchKey == 0)
    {
        // secondary key is not set or not passphrase
        // set a temporary one
        CAtlString strTmpKey = L"HostedNetwork12345";

        hr = SetHostedNetworkKey(strTmpKey);
        BAIL_ON_FAILURE(hr);
        strKey = strTmpKey;
    }
    else
    {
        // got the key
        strKey = strSecondaryKey;
    }

error:    
    if (pucSecondaryKey != NULL)
    {
        WlanFreeMemory(pucSecondaryKey);
        pucSecondaryKey = NULL;
    }

    return hr;
}