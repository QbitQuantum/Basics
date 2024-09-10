HRESULT RefreshIPv6CfgDialog(HWND hwndDlg)
{
    HRESULT             hr = S_OK;
    ULONG               ulBufferSize = 0;
    DWORD               dwRetVal;

    TCHAR               szAddr[INET6_ADDRSTRLEN];
    TCHAR               szAddrNotAvail[INET6_ADDRSTRLEN];
    BOOL                bDefaultGateway = FALSE;
    BOOL                bPrefGlobal = FALSE;
    BOOL                bPrefLinkLocal = FALSE;
    BOOL                bPrefSiteLocal = FALSE;
    BOOL                b6to4 = FALSE;
    BOOL                bAuto1 = FALSE;
    BOOL                bAuto2 = FALSE;
    BOOL                bAuto3 = FALSE;

    PIP_ADAPTER_ADDRESSES pAdapterAddresses = NULL, pThisAdapterAddresses;
    PIP_ADAPTER_UNICAST_ADDRESS pUnicastAddresses;
    char                szAdapterName[MAX_ADAPTERNAME_STR];

    // Get IP address info
    dwRetVal = GetAdaptersAddresses(AF_INET6,GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST,
                                    NULL,NULL,&ulBufferSize);

    if (dwRetVal != ERROR_BUFFER_OVERFLOW) {
        DEBUGMSG(ZONE_ERROR, (TEXT("NETUIQC: Error from GetAdaptersAddresses():%u"),dwRetVal));
        hr = E_FAIL;
        goto exit;
    }

    pAdapterAddresses = (PIP_ADAPTER_ADDRESSES)malloc(ulBufferSize);
    if (pAdapterAddresses == NULL) {
        hr = E_FAIL;
        goto exit;
    }

    dwRetVal = GetAdaptersAddresses(AF_INET6,GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST,
                                    NULL,pAdapterAddresses,&ulBufferSize);
    if (dwRetVal != ERROR_SUCCESS) {
        DEBUGMSG(ZONE_ERROR, (TEXT("NETUIQC: Error from GetAdaptersAddresses():%u"),dwRetVal));
        hr = E_FAIL;
        goto exit;
    }
    // Get our adapter name
    if (GetAdapterNameA(hwndDlg,szAdapterName,sizeof(szAdapterName)) != S_OK) {
        DEBUGMSG(ZONE_ERROR, (TEXT("Error getting adapter name")));
        hr = E_FAIL;
        goto exit;
    }

    // Walk adapter list
    for (pThisAdapterAddresses = pAdapterAddresses; 
        pThisAdapterAddresses;
        pThisAdapterAddresses = pThisAdapterAddresses->Next) {

        BOOL bCurrentAdapter;

        DEBUGMSG(ZONE_MISC,(TEXT("GetAdaptersAddresses adapter <%s>\n"),pThisAdapterAddresses->FriendlyName));

        if (! strcmp(szAdapterName,pThisAdapterAddresses->AdapterName)) {

            // IPv6 stack will return address info even if media disconnected.  Don't display
            // addresses in this case.
            if (!(pThisAdapterAddresses->OperStatus & IfOperStatusUp)) {
                DEBUGMSG(ZONE_MISC,(TEXT("GetAdaptersAddresses -- Media Disconnected\n")));
                break;
            }

            bCurrentAdapter = TRUE;
            if (GetIPv6DefaultGateway(pThisAdapterAddresses, szAddr)) {
                UpdateIPv6AddressField(hwndDlg, IDC_V6GATEWAY_LBL_INF, szAddr);
                bDefaultGateway = TRUE;
            }
        }
        else {
            bCurrentAdapter = FALSE;
            if (pThisAdapterAddresses->IfType != IF_TYPE_TUNNEL) {
                // Skip other non tunneling adapters 
                continue;
            }
            // TBD - For tunneling interfaces, we want to choose the one matching the v4 address on this interface

        }

        for (pUnicastAddresses = pThisAdapterAddresses->FirstUnicastAddress ;
            pUnicastAddresses;
            pUnicastAddresses = pUnicastAddresses->Next) {
            PSOCKADDR_IN6 pSA = (PSOCKADDR_IN6)pUnicastAddresses->Address.lpSockaddr;
            ULONG AddrFieldLbl;

            GetIPv6AddressString(szAddr, pSA);

            DEBUGMSG(ZONE_MISC,(TEXT("   GetAdaptersAddresses return addr <%s>\n"),szAddr));

            AddrFieldLbl = 0;

            if (IN6_IS_ADDR_SITELOCAL(&pSA->sin6_addr)) {
                if (bCurrentAdapter) {
                    AddrFieldLbl = IDC_V6PREFSITEADDR_LBL_INF;
                    bPrefSiteLocal = TRUE;
                } else if (IN6_IS_ADDR_ISATAP(&pSA->sin6_addr)) {
                    AddrFieldLbl = IDC_V6TUNNELADDR_LBL_INF2;
                    bAuto2 = TRUE;
                }
            } else if (IN6_IS_ADDR_LINKLOCAL(&pSA->sin6_addr)) {
                if (bCurrentAdapter) {
                    AddrFieldLbl = IDC_V6PREFLINKADDR_LBL_INF;
                    bPrefLinkLocal = TRUE;
                } else if (IN6_IS_ADDR_ISATAP(&pSA->sin6_addr)) {
                    AddrFieldLbl = IDC_V6TUNNELADDR_LBL_INF3;
                    bAuto3 = TRUE;
                }
            } else {
                if (bCurrentAdapter) {
                    AddrFieldLbl = IDC_V6PREFGLOBADDR_LBL_INF;
                    bPrefGlobal = TRUE;
                } else if (IN6_IS_ADDR_6TO4(&pSA->sin6_addr)) {
                    AddrFieldLbl = IDC_V66TO4ADDR_LBL_INF;
                    b6to4 = TRUE;
                } else if (IN6_IS_ADDR_ISATAP(&pSA->sin6_addr)) {
                    AddrFieldLbl = IDC_V6TUNNELADDR_LBL_INF1;
                    bAuto1 = TRUE;
                }
            }

            if (AddrFieldLbl)
                UpdateIPv6AddressField(hwndDlg, AddrFieldLbl, szAddr);
        }

    }


    exit:
    // Display address not available for fields we couldn't populate

    LoadString(v_hInst, IDS_QC_V6_ADDR_UNAVAIL, szAddrNotAvail, INET6_ADDRSTRLEN);
    if (!bDefaultGateway)
        UpdateIPv6AddressField(hwndDlg, IDC_V6GATEWAY_LBL_INF, szAddrNotAvail);
    if (!bPrefGlobal)
        UpdateIPv6AddressField(hwndDlg, IDC_V6PREFGLOBADDR_LBL_INF, szAddrNotAvail);
    if (!bPrefSiteLocal)
        UpdateIPv6AddressField(hwndDlg, IDC_V6PREFSITEADDR_LBL_INF, szAddrNotAvail);
    if (!bPrefLinkLocal)
        UpdateIPv6AddressField(hwndDlg, IDC_V6PREFLINKADDR_LBL_INF, szAddrNotAvail);
    if (!b6to4)
        UpdateIPv6AddressField(hwndDlg, IDC_V66TO4ADDR_LBL_INF, szAddrNotAvail);
    if (!bAuto1)
        UpdateIPv6AddressField(hwndDlg, IDC_V6TUNNELADDR_LBL_INF1, szAddrNotAvail);
    if (!bAuto2)
        UpdateIPv6AddressField(hwndDlg, IDC_V6TUNNELADDR_LBL_INF2, szAddrNotAvail);
    if (!bAuto3)
        UpdateIPv6AddressField(hwndDlg, IDC_V6TUNNELADDR_LBL_INF3, szAddrNotAvail);

    if (pAdapterAddresses) {
        free(pAdapterAddresses);
    }
    return hr;
}