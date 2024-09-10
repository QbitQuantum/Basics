HRESULT HostDnsServiceWin::updateInfo()
{
    HostDnsInformation info;

    LONG lrc;
    int rc;

    std::string strDomain;
    std::string strSearchList;  /* NB: comma separated, no spaces */


    /*
     * We ignore "DhcpDomain" key here since it's not stable.  If
     * there are two active interfaces that use DHCP (in particular
     * when host uses OpenVPN) then DHCP ACKs will take turns updating
     * that key.  Instead we call GetAdaptersAddresses() below (which
     * is what ipconfig.exe seems to do).
     */
    for (DWORD regIndex = 0; /**/; ++regIndex) {
        char keyName[256];
        DWORD cbKeyName = sizeof(keyName);
        DWORD keyType = 0;
        char keyData[1024];
        DWORD cbKeyData = sizeof(keyData);

        lrc = RegEnumValueA(m->hKeyTcpipParameters, regIndex,
                            keyName, &cbKeyName, 0,
                            &keyType, (LPBYTE)keyData, &cbKeyData);

        if (lrc == ERROR_NO_MORE_ITEMS)
            break;

        if (lrc == ERROR_MORE_DATA) /* buffer too small; handle? */
            continue;

        if (lrc != ERROR_SUCCESS)
        {
            LogRel2(("HostDnsServiceWin: RegEnumValue error %d\n", (int)lrc));
            return E_FAIL;
        }

        if (keyType != REG_SZ)
            continue;

        if (cbKeyData > 0 && keyData[cbKeyData - 1] == '\0')
            --cbKeyData;     /* don't count trailing NUL if present */

        if (RTStrICmp("Domain", keyName) == 0)
        {
            strDomain.assign(keyData, cbKeyData);
            LogRel2(("HostDnsServiceWin: Domain=\"%s\"\n", strDomain.c_str()));
        }
        else if (RTStrICmp("DhcpDomain", keyName) == 0)
        {
            std::string strDhcpDomain(keyData, cbKeyData);
            LogRel2(("HostDnsServiceWin: DhcpDomain=\"%s\"\n", strDhcpDomain.c_str()));
        }
        else if (RTStrICmp("SearchList", keyName) == 0)
        {
            strSearchList.assign(keyData, cbKeyData);
            LogRel2(("HostDnsServiceWin: SearchList=\"%s\"\n", strSearchList.c_str()));
        }
    }

    /* statically configured domain name */
    if (!strDomain.empty())
    {
        info.domain = strDomain;
        info.searchList.push_back(strDomain);
    }

    /* statically configured search list */
    if (!strSearchList.empty())
    {
        vappend(info.searchList, strSearchList, ',');
    }


    /*
     * When name servers are configured statically it seems that the
     * value of Tcpip\Parameters\NameServer is NOT set, inly interface
     * specific NameServer value is (which triggers notification for
     * us to pick up the change).  Fortunately, DnsApi seems to do the
     * right thing there.
     */
    DNS_STATUS status;
    PIP4_ARRAY pIp4Array = NULL;

    // NB: must be set on input it seems, despite docs' claim to the contrary.
    DWORD cbBuffer = sizeof(&pIp4Array);

    status = DnsQueryConfig(DnsConfigDnsServerList,
                            DNS_CONFIG_FLAG_ALLOC, NULL, NULL,
                            &pIp4Array, &cbBuffer);

    if (status == NO_ERROR && pIp4Array != NULL)
    {
        for (DWORD i = 0; i < pIp4Array->AddrCount; ++i)
        {
            char szAddrStr[16] = "";
            RTStrPrintf(szAddrStr, sizeof(szAddrStr), "%RTnaipv4", pIp4Array->AddrArray[i]);

            LogRel2(("HostDnsServiceWin: server %d: %s\n", i+1,  szAddrStr));
            info.servers.push_back(szAddrStr);
        }

        LocalFree(pIp4Array);
    }


    /**
     * DnsQueryConfig(DnsConfigSearchList, ...) is not implemented.
     * Call GetAdaptersAddresses() that orders the returned list
     * appropriately and collect IP_ADAPTER_ADDRESSES::DnsSuffix.
     */
    do {
        PIP_ADAPTER_ADDRESSES pAddrBuf = NULL;
        ULONG cbAddrBuf = 8 * 1024;
        bool fReallocated = false;
        ULONG err;

        pAddrBuf = (PIP_ADAPTER_ADDRESSES) malloc(cbAddrBuf);
        if (pAddrBuf == NULL)
        {
            LogRel2(("HostDnsServiceWin: failed to allocate %zu bytes"
                     " of GetAdaptersAddresses buffer\n",
                     (size_t)cbAddrBuf));
            break;
        }

        while (pAddrBuf != NULL)
        {
            ULONG cbAddrBufProvided = cbAddrBuf;

            err = GetAdaptersAddresses(AF_UNSPEC,
                                         GAA_FLAG_SKIP_ANYCAST
                                       | GAA_FLAG_SKIP_MULTICAST,
                                       NULL,
                                       pAddrBuf, &cbAddrBuf);
            if (err == NO_ERROR)
            {
                break;
            }
            else if (err == ERROR_BUFFER_OVERFLOW)
            {
                LogRel2(("HostDnsServiceWin: provided GetAdaptersAddresses with %zu"
                         " but asked again for %zu bytes\n",
                         (size_t)cbAddrBufProvided, (size_t)cbAddrBuf));

                if (RT_UNLIKELY(fReallocated)) /* what? again?! */
                {
                    LogRel2(("HostDnsServiceWin: ... not going to realloc again\n"));
                    free(pAddrBuf);
                    pAddrBuf = NULL;
                    break;
                }

                PIP_ADAPTER_ADDRESSES pNewBuf = (PIP_ADAPTER_ADDRESSES) realloc(pAddrBuf, cbAddrBuf);
                if (pNewBuf == NULL)
                {
                    LogRel2(("HostDnsServiceWin: failed to reallocate %zu bytes\n", (size_t)cbAddrBuf));
                    free(pAddrBuf);
                    pAddrBuf = NULL;
                    break;
                }

                /* try again */
                pAddrBuf = pNewBuf; /* cbAddrBuf already updated */
                fReallocated = true;
            }
            else
            {
                LogRel2(("HostDnsServiceWin: GetAdaptersAddresses error %d\n", err));
                free(pAddrBuf);
                pAddrBuf = NULL;
                break;
            }
        }

        if (pAddrBuf == NULL)
            break;

        for (PIP_ADAPTER_ADDRESSES pAdp = pAddrBuf; pAdp != NULL; pAdp = pAdp->Next)
        {
            LogRel2(("HostDnsServiceWin: %ls (status %u) ...\n",
                     pAdp->FriendlyName ? pAdp->FriendlyName : L"(null)",
                     pAdp->OperStatus));

            if (pAdp->OperStatus != IfOperStatusUp)
                continue;

            if (pAdp->DnsSuffix == NULL || *pAdp->DnsSuffix == L'\0')
                continue;

            char *pszDnsSuffix = NULL;
            rc = RTUtf16ToUtf8Ex(pAdp->DnsSuffix, RTSTR_MAX,
                                 &pszDnsSuffix, 0, /* allocate */
                                 NULL);
            if (RT_FAILURE(rc))
            {
                LogRel2(("HostDnsServiceWin: failed to convert DNS suffix \"%ls\": %Rrc\n",
                        pAdp->DnsSuffix, rc));
                continue;
            }

            AssertContinue(pszDnsSuffix != NULL);
            AssertContinue(*pszDnsSuffix != '\0');
            LogRel2(("HostDnsServiceWin: ... suffix = \"%s\"\n", pszDnsSuffix));

            vappend(info.searchList, pszDnsSuffix);
            RTStrFree(pszDnsSuffix);
        }

        free(pAddrBuf);
    } while (0);


    if (info.domain.empty() && !info.searchList.empty())
        info.domain = info.searchList[0];

    if (info.searchList.size() == 1)
        info.searchList.clear();

    HostDnsMonitor::setInfo(info);

    return S_OK;
}