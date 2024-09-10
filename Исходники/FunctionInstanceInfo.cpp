HRESULT TFunctionInstanceInfo::CreateInstance(
        __in GUID* pDeviceId,
        __in_opt TDeviceInfo* pDeviceInfo,
        __in SOCKADDR_STORAGE* pFromAddr,
        INT FromAddrLen,
        ULONG InterfaceIndex,
        __deref_out TFunctionInstanceInfo** ppFunctionInstanceInfo)
{
    HRESULT hr = S_OK;
    TFunctionInstanceInfo* pFunctionInstanceInfo = NULL;
    MIB_IPNET_ROW2 IpNetRow2 = {0};
    int err = 0;
    static const WCHAR szDelimeters[] = L" ,;";
    PWSTR pszToken = NULL;
    PWSTR pszNextToken = NULL;
    ULONG iCategoryIndex = 0;

    *ppFunctionInstanceInfo = NULL;

    // Create new Function Instance info
    if (S_OK == hr)
    {
        pFunctionInstanceInfo = new(std::nothrow) TFunctionInstanceInfo();
        if (!pFunctionInstanceInfo)
        {
            hr = E_OUTOFMEMORY;
        }
    }

    // Get the MAC address for the From address
    if (S_OK == hr)
    {
        memcpy(
            &IpNetRow2.Address, 
            pFromAddr, 
            (FromAddrLen <= sizeof(IpNetRow2.Address)) ? FromAddrLen : sizeof(IpNetRow2.Address));
        IpNetRow2.InterfaceIndex = InterfaceIndex;
        err = GetIpNetEntry2(&IpNetRow2);
        if (NO_ERROR != err)
        {
            // Could not find the MAC address in the cache, lets hit the wire.
             err = ResolveIpNetEntry2(&IpNetRow2, NULL);
        }

        if (NO_ERROR == err)
        {
            memcpy(pFunctionInstanceInfo->m_PhysicalAddress, IpNetRow2.PhysicalAddress, IpNetRow2.PhysicalAddressLength);
            pFunctionInstanceInfo->m_PhysicalAddressLength = IpNetRow2.PhysicalAddressLength;
        }
        else
        {
            hr = HRESULT_FROM_WIN32(err);
        }
    }

    // Convert the From Address to String form.
    if (S_OK == hr)
    {
        err = GetNameInfo(
            (PSOCKADDR) pFromAddr,
            FromAddrLen,
            pFunctionInstanceInfo->m_szIPAddress,
            ARRAYSIZE(pFunctionInstanceInfo->m_szIPAddress),
            NULL, 
            0,
            NI_NUMERICHOST | NI_NOFQDN);
        if (err != 0)
        {
            hr = HRESULT_FROM_WIN32(WSAGetLastError());
        }
    }

    // Convert the GUID into String Form
    if (S_OK == hr)
    {
        err = UuidToString(
            pDeviceId,
            (RPC_WSTR*) &pFunctionInstanceInfo->m_pszDeviceId);
        if (RPC_S_OK != err)
        {
            hr = E_OUTOFMEMORY;
        }
    }

    // Copy device info
    if (S_OK == hr)
    {
        if (pDeviceInfo)
        {
            pFunctionInstanceInfo->m_DeviceInfo = *pDeviceInfo;
        }
    }

    // Create an array of device categories
    if (   (S_OK == hr)
        && *pFunctionInstanceInfo->m_DeviceInfo.szDeviceCategory)
    {
        // Count the number of delimeters in the string
        pFunctionInstanceInfo->m_cDeviceCategoriesCount = 1;
        pszToken = pFunctionInstanceInfo->m_DeviceInfo.szDeviceCategory;
        while (*pszToken)
        {
            if (wcschr(szDelimeters, *pszToken))
            {
                ++pFunctionInstanceInfo->m_cDeviceCategoriesCount;
            }
            ++pszToken;
        }

        // Allocate an array to hold the string pointers
        pFunctionInstanceInfo->m_ppszDeviceCategories = (PWSTR*) malloc(pFunctionInstanceInfo->m_cDeviceCategoriesCount * sizeof(PWSTR));

        if (pFunctionInstanceInfo->m_ppszDeviceCategories)
        {
            // Tokenize the device categories and save the pointers

            pszToken = wcstok_s(pFunctionInstanceInfo->m_DeviceInfo.szDeviceCategory,
                szDelimeters,
                &pszNextToken);

            while (   pszToken
                   && (iCategoryIndex < pFunctionInstanceInfo->m_cDeviceCategoriesCount))
            {
                pFunctionInstanceInfo->m_ppszDeviceCategories[iCategoryIndex] = pszToken;
                ++iCategoryIndex;
                  
                pszToken = wcstok_s(
                    NULL,
                    szDelimeters,
                    &pszNextToken);
            }
        }
        else
        {
            hr = E_OUTOFMEMORY;
        }

    }

    // Cleanup
    if (S_OK == hr)
    {
        *ppFunctionInstanceInfo = pFunctionInstanceInfo;
    }
    else
    {
        delete pFunctionInstanceInfo;
    }

    return hr;
}  // TFunctionInstanceInfo::CreateInstance