void MonitorSink::SetCustomHeaders(LPWSTR *pszAdditionalHeaders)
{
    if (pszAdditionalHeaders && *pszAdditionalHeaders)
    {
        CStringW strHeaders(*pszAdditionalHeaders);
        size_t nOrigLen = strHeaders.GetLength();

        bool bSendDNT1 = abp::AdBlockPlus::shouldSendDNTHeader(m_strURL.GetString());
        bool bSendDNT0 = PrefManager::instance().isDNTEnabled() && PrefManager::instance().getDNTValue() == 0;
        bool bSendDNT = bSendDNT1 || bSendDNT0;
        int nDNTValue = bSendDNT1 ? 1 : 0;
        if (bSendDNT)
        {
            LPWSTR lpDNT = NULL;
            size_t nDNTLen = 0;
            bool hasDNT = false;
            if (Utils::HTTP::ExtractFieldValue(*pszAdditionalHeaders, L"DNT:", &lpDNT, &nDNTLen))
            {
                if (nDNTLen)
                {
                    // Already has DNT header
                    hasDNT = true;
                }
                if (lpDNT) Utils::HTTP::FreeFieldValue(lpDNT);
            }
            // Append DoNotTrack (DNT) header
            if (!hasDNT)
                strHeaders.AppendFormat(L"DNT: %d\r\n", nDNTValue);
        }

        if (strHeaders.GetLength() == nOrigLen)
            return; // Not modified, return immediately

        size_t nLen = strHeaders.GetLength() + 2;
        if (*pszAdditionalHeaders = (LPWSTR)CoTaskMemRealloc(*pszAdditionalHeaders, nLen * sizeof(WCHAR)))
        {
            wcscpy_s(*pszAdditionalHeaders, nLen, strHeaders);
        }
    }
}