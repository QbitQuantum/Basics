IPSTATE GetIPState(LPCTSTR pszAdapter, LPTSTR pszAddress, UINT cchAddress)
{
    HRESULT              hr = S_OK;
    IPSTATE              state = IPSTATE_DHCP;
    ULONG                ulAdapterIndex;
    PIP_ADAPTER_INFO     paiBuffer = NULL;
    ULONG                cbBuffer = 0;
    DWORD                dwError;
    PIP_ADAPTER_INFO     paiCurrent;
    PIP_PER_ADAPTER_INFO pper = NULL;

    // Check inputs
    CBRAEx(NULL != pszAdapter, E_INVALIDARG);

    // Get the adapter index
    CBR(NO_ERROR == GetAdapterIndex(const_cast<LPWSTR>(pszAdapter), &ulAdapterIndex));

    // Get the status of all connected adapters
    cbBuffer = sizeof(IP_ADAPTER_INFO);
    paiBuffer = (PIP_ADAPTER_INFO)LocalAlloc(LMEM_FIXED, cbBuffer);
    CPR(paiBuffer);

    while (ERROR_BUFFER_OVERFLOW == (dwError = GetAdaptersInfo(paiBuffer, &cbBuffer)))
    {
        PIP_ADAPTER_INFO paiTemp = (PIP_ADAPTER_INFO)LocalReAlloc(paiBuffer, cbBuffer, LMEM_MOVEABLE);
        CPR(paiTemp);
        paiBuffer = paiTemp;
    }

    CBR(NO_ERROR == dwError);

    // Find our adapter index
    for (paiCurrent = paiBuffer; paiCurrent; paiCurrent = paiCurrent->Next)
    {
        if (paiCurrent->Index == ulAdapterIndex)
        {
            break;
        }
    }

    CBR(NULL != paiCurrent);  // did we find it?
    CBR(NULL != paiCurrent->CurrentIpAddress);

    // Is this adapter using DHCP?
    if (!paiCurrent->DhcpEnabled)
    {
        state = IPSTATE_CONNECTED;
    }
    else
    {
        // Get the per-adapter info
        cbBuffer = sizeof(IP_PER_ADAPTER_INFO);
        pper = (PIP_PER_ADAPTER_INFO)LocalAlloc(LMEM_FIXED, cbBuffer);
        CPR(pper);

        while (ERROR_BUFFER_OVERFLOW == (dwError = GetPerAdapterInfo(ulAdapterIndex, pper, &cbBuffer)))
        {
            PIP_PER_ADAPTER_INFO pperTemp = (PIP_PER_ADAPTER_INFO)LocalReAlloc(pper, cbBuffer, LMEM_MOVEABLE);
            CPR(pperTemp);
            pper = pperTemp;
        }

        CBR(NO_ERROR == dwError);

        // Are we using an automatic IP?
        if (pper->AutoconfigActive || IsAutoIPAddr(paiCurrent->CurrentIpAddress->IpAddress.String))
        {
            state = IPSTATE_AUTOIP;
        }
    }

    // Optionally copy the IP address string to the output
    if (NULL != pszAddress && 0 != cchAddress)
    {
        UINT cchInput = strlen(paiCurrent->CurrentIpAddress->IpAddress.String);
        if (cchInput >= cchAddress)
        {
            cchInput = cchAddress - 1;
        }

        MultiByteToWideChar(CP_ACP, 0,
            paiCurrent->CurrentIpAddress->IpAddress.String, cchInput,
            pszAddress, cchAddress);
        pszAddress[cchAddress-1] = TEXT('\0');
    }

Error:
    LocalFree(pper);
    LocalFree(paiBuffer);
    return (SUCCEEDED(hr) ? state : IPSTATE_DISCONNECTED);
}