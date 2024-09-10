void LogInterfaceType (RTMP *rtmp)
{
    MIB_IPFORWARDROW    route;
    DWORD               destAddr;
    CHAR                hostname[256];

    if (rtmp->Link.hostname.av_len >= sizeof(hostname)-1)
        return;

    strncpy (hostname, rtmp->Link.hostname.av_val, sizeof(hostname)-1);
    hostname[rtmp->Link.hostname.av_len] = 0;

    HOSTENT *h = gethostbyname(hostname);
    if (!h)
        return;

    destAddr = *(DWORD *)h->h_addr_list[0];

    if (!GetBestRoute (destAddr, rtmp->m_bindIP.addr.sin_addr.S_un.S_addr, &route))
    {
        MIB_IFROW row;
        zero (&row, sizeof(row));
        row.dwIndex = route.dwForwardIfIndex;

        if (!GetIfEntry (&row))
        {
            DWORD speed = row.dwSpeed / 1000000;
            TCHAR *type;
            String otherType;

            if (row.dwType == IF_TYPE_ETHERNET_CSMACD)
                type = TEXT("ethernet");
            else if (row.dwType == IF_TYPE_IEEE80211)
                type = TEXT("802.11");
            else
            {
                otherType = FormattedString (TEXT("type %d"), row.dwType);
                type = otherType.Array();
            }

            Log (TEXT("  Interface: %S (%s, %d mbps)"), row.bDescr, type, speed);
        }
    }
}