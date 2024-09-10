DWORD
GetInterfaceIndexForAddress(
    SOCKADDR *pAddr
)
{
    IP_ADAPTER_UNICAST_ADDRESS *pTmpUniAddr = NULL;
    IP_ADAPTER_ADDRESSES       *pAdaptAddr = NULL,
                                *pTmpAdaptAddr = NULL;
    MIB_IPADDRTABLE            *pMibTable = NULL;
    DWORD                       dwRet = 0,
                                dwReturn = (DWORD) SOCKET_ERROR,
                                dwSize = 0,
                                Family = AF_UNSPEC,
                                dwIndex = 0;
    BOOL                        bFound = FALSE;

    typedef ULONG (*LPFN_GETADAPTERSADDRESSES) (ULONG Family,DWORD Flags,PVOID Reserved,PIP_ADAPTER_ADDRESSES pAdapterAddresses,PULONG pOutBufLen);
    LPFN_GETADAPTERSADDRESSES fnGetAdaptersAddresses = (LPFN_GETADAPTERSADDRESSES)GetProcAddress(GetModuleHandleA("iphlpapi"),"GetAdaptersAddresses");

    __try
    {
        if (NULL == pAddr)
        {
            WSASetLastError(ERROR_INVALID_PARAMETER);
            ERR("GetInterfaceIndexForAddress: invalid parameter passed (pAddr == NULL)");
            __leave;
        }

        switch (pAddr->sa_family)
        {
        case AF_INET:
            Family = AF_INET;
            break;
        case AF_INET6:
            Family = AF_INET6;
            break;
        default:
            WSASetLastError(WSAEAFNOSUPPORT);
            __leave;
            break;
        }

        if (fnGetAdaptersAddresses)
        {


            if (ERROR_BUFFER_OVERFLOW != (dwRet = fnGetAdaptersAddresses(Family,
                                                  GAA_FLAG_SKIP_ANYCAST|GAA_FLAG_SKIP_MULTICAST|GAA_FLAG_SKIP_DNS_SERVER,
                                                  NULL,
                                                  NULL,
                                                  &dwSize
                                                                        )))
            {
                WSASetLastError(dwRet);
                ERR("GetAdaptersAddresses");
                __leave;
            }

            if (NULL == (pAdaptAddr = (IP_ADAPTER_ADDRESSES*)MALLOC(dwSize)))
            {
                ERR("HeapAlloc");
                __leave;
            }

            if (ERROR_SUCCESS != (dwRet = fnGetAdaptersAddresses(Family,
                                          GAA_FLAG_SKIP_ANYCAST|GAA_FLAG_SKIP_MULTICAST|GAA_FLAG_SKIP_DNS_SERVER,
                                          NULL,
                                          pAdaptAddr,
                                          &dwSize
                                                                )))
            {
                WSASetLastError(dwRet);
                ERR("GetAdaptersAddresses");
                __leave;
            }

            //look at each IP_ADAPTER_ADDRESSES node

            pTmpAdaptAddr = pAdaptAddr;

            while (pTmpAdaptAddr)
            {

                //look at each IP_ADAPTER_UNICAST_ADDRESS node

                pTmpUniAddr = pTmpAdaptAddr->FirstUnicastAddress;


                while (pTmpUniAddr)
                {



                    if (AF_INET == pTmpUniAddr->Address.lpSockaddr->sa_family)
                    {

                        if (IN4_ADDR_EQUAL(&((SOCKADDR_IN*)pAddr)->sin_addr,&((SOCKADDR_IN*)pTmpUniAddr->Address.lpSockaddr)->sin_addr))
                        {
                            dwReturn = pTmpAdaptAddr->IfIndex;
                            bFound = TRUE;

                            break;
                        }

                    }
                    else
                    {
                        if (IN6_ADDR_EQUAL(&((SOCKADDR_IN6*)pAddr)->sin6_addr, &((SOCKADDR_IN6*)pTmpUniAddr->Address.lpSockaddr)->sin6_addr ))
                        {
                            dwReturn = pTmpAdaptAddr->Ipv6IfIndex;
                            bFound = TRUE;

                            break;
                        }
                    }

                    pTmpUniAddr = pTmpUniAddr->Next;

                }

                if (bFound)
                    break;

                pTmpAdaptAddr = pTmpAdaptAddr->Next;

            }
        }  //end GetAdaptersAddresses
        else //use mibtable
        {
            //call with NULL to get size needed to alloc
            if (ERROR_INSUFFICIENT_BUFFER != (dwRet = GetIpAddrTable(NULL,
                                              &dwSize,
                                              TRUE
                                                                    )))
            {
                WSASetLastError(dwRet);
                ERR("GetIpAddrTable");
                __leave;
            }

            if (NULL == (pMibTable = (MIB_IPADDRTABLE*)MALLOC(dwSize)))
            {
                ERR("HeapAlloc");
                __leave;
            }

            if (NO_ERROR != (dwRet = GetIpAddrTable(pMibTable,
                                                    &dwSize,
                                                    TRUE
                                                   )))
            {
                WSASetLastError(dwRet);
                ERR("GetIpAddrTable");
                __leave;
            }

            for (dwIndex = 0; dwIndex < pMibTable->dwNumEntries; dwIndex++)
            {
                if( ((SOCKADDR_IN*)pAddr)->sin_addr.s_addr == pMibTable->table[dwIndex].dwAddr)
                {
                    dwReturn = pMibTable->table[dwIndex].dwIndex;
                }
            }



        }//end use mibtable

    }
    __finally
    {
        FREE(pAdaptAddr);
        FREE(pMibTable);
    }

    return dwReturn;
}