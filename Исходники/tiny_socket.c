static TinyRet udp_join_multicast_group_with_all_ip(int fd, const char *group)
{
    IP_ADAPTER_INFO * pNextAdapter = NULL;
    IP_ADAPTER_INFO * ipAdaptersInfo = NULL;
    ULONG infolen = sizeof(IP_ADAPTER_INFO);

    ipAdaptersInfo = (IP_ADAPTER_INFO *)tiny_malloc(infolen);

    if (GetAdaptersInfo(ipAdaptersInfo, &infolen) == ERROR_BUFFER_OVERFLOW)
    {
        tiny_free(ipAdaptersInfo);
        ipAdaptersInfo = (IP_ADAPTER_INFO *)tiny_malloc(infolen);
    }

    if (GetAdaptersInfo(ipAdaptersInfo, &infolen))
    {
        tiny_free(ipAdaptersInfo);
        return TINY_RET_E_INTERNAL;
    }

    for (pNextAdapter = ipAdaptersInfo; pNextAdapter; pNextAdapter = pNextAdapter->Next)
    {
        IP_ADDR_STRING *pNextIp = NULL;
        for (pNextIp = &(pNextAdapter->IpAddressList); pNextIp; pNextIp = pNextIp->Next)
        {
            unsigned long ip = inet_addr(pNextIp->IpAddress.String);
            if (ip == 0)
            {
                break;
            }

            LOG_D(TAG, "join MultiGroup ip: %s", pNextIp->IpAddress.String);

            udp_join_multicast_group_with_ip(fd, group, ip);
        }
    }

    tiny_free(ipAdaptersInfo);

    return TINY_RET_OK;
}