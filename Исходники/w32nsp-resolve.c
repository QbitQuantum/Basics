int
main (int argc, char **argv)
{
    int ret;
    int r = 1;
    WSADATA wsd;
    GUID prov;
    GUID sc;
    wchar_t *cmdl;
    int wargc;
    wchar_t **wargv;

    if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
    {
        fprintf (stderr, "WSAStartup() failed: %lu\n", GetLastError());
        return 5;
    }

    cmdl = GetCommandLineW ();
    if (cmdl == NULL)
    {
        WSACleanup();
        return 2;
    }
    wargv = CommandLineToArgvW (cmdl, &wargc);
    if (wargv == NULL)
    {
        WSACleanup();
        return 3;
    }
    r = 4;

    if (wargc == 5)
    {
        if (wcscmp (wargv[1], L"A") == 0)
            sc = SVCID_DNS_TYPE_A;
        else if (wcscmp (wargv[1], L"AAAA") == 0)
            sc = SVCID_DNS_TYPE_AAAA;
        else if (wcscmp (wargv[1], L"name") == 0)
            sc = SVCID_HOSTNAME;
        else if (wcscmp (wargv[1], L"addr") == 0)
            sc = SVCID_INET_HOSTADDRBYNAME;
        else
            wargc -= 1;
        if (wcscmp (wargv[4], L"mswdns") == 0)
            prov = W32_DNS;
        else if (wcscmp (wargv[4], L"gnunetdns") == 0)
            prov = GNUNET_NAMESPACE_PROVIDER_DNS;
        else
            wargc -= 1;
    }
    else if (wargc == 3)
    {
    }
    else
    {
        fprintf (stderr, "Usage: %S <record type> <service name> <NSP library path> <NSP id>\n"
                 "record type      - one of the following: A | AAAA | name | addr\n"
                 "service name     - a string to resolve; \" \" (a space) means 'blank'\n"
                 "NSP library path - path to libw32nsp\n"
                 "NSP id           - one of the following: mswdns | gnunetdns\n",
                 wargv[0]);
    }

    if (wargc == 5)
    {
        HMODULE nsp;

        nsp = LoadLibraryW (wargv[3]);
        if (nsp == NULL)
        {
            fprintf (stderr, "Failed to load library `%S'\n", wargv[3]);
        }
        else
        {
            LPNSPSTARTUP startup = (LPNSPSTARTUP) GetProcAddress (nsp, "NSPStartup");
            if (startup == NULL)
                startup = (LPNSPSTARTUP) GetProcAddress (nsp, "NSPStartup@8");
            if (startup != NULL)
            {
                NSP_ROUTINE api;
                api.cbSize = sizeof (api);
                ret = startup (&prov, &api);
                if (NO_ERROR != ret)
                    fprintf (stderr, "startup failed: %lu\n", GetLastError ());
                else
                {
                    HANDLE lookup;
                    WSAQUERYSETW search;
                    char buf[4096];
                    WSAQUERYSETW *result = (WSAQUERYSETW *) buf;
                    DWORD resultsize;
                    DWORD err;
                    memset (&search, 0, sizeof (search));
                    search.dwSize = sizeof (search);
                    search.lpszServiceInstanceName = (wcscmp (wargv[2], L" ") == 0) ? NULL : wargv[2];
                    search.lpServiceClassId = &sc;
                    search.lpNSProviderId = &prov;
                    search.dwNameSpace = NS_ALL;
                    ret = api.NSPLookupServiceBegin (&prov, &search, NULL, LUP_RETURN_ALL, &lookup);
                    if (ret != NO_ERROR)
                    {
                        fprintf (stderr, "lookup start failed\n");
                    }
                    else
                    {
                        resultsize = 4096;
                        ret = api.NSPLookupServiceNext (lookup, LUP_RETURN_ALL, &resultsize, result);
                        err = GetLastError ();
                        if (ret != NO_ERROR)
                        {
                            fprintf (stderr, "lookup next failed: %lu\n", err);
                        }
                        else
                        {
                            int i;
                            printf ("Got result:\n");
                            printf ("  lpszServiceInstanceName: %S\n", result->lpszServiceInstanceName ? result->lpszServiceInstanceName : L"NULL");
                            if (result->lpServiceClassId)
                                printf ("  lpServiceClassId:        { 0x%08lX,0x%04X,0x%04X, { 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X } }\n",
                                        result->lpServiceClassId->Data1, result->lpServiceClassId->Data2, result->lpServiceClassId->Data3, result->lpServiceClassId->Data4[0],
                                        result->lpServiceClassId->Data4[1], result->lpServiceClassId->Data4[2], result->lpServiceClassId->Data4[3], result->lpServiceClassId->Data4[4],
                                        result->lpServiceClassId->Data4[5], result->lpServiceClassId->Data4[6], result->lpServiceClassId->Data4[7]);
                            else
                                printf ("  lpServiceClassId:        NULL\n");
                            if (result->lpVersion)
                                printf ("  lpVersion:               0x%08lX, %d\n", result->lpVersion->dwVersion, result->lpVersion->ecHow);
                            else
                                printf ("  lpVersion:               NULL\n");
                            printf ("  lpszComment:             %S\n", result->lpszComment ? result->lpszComment : L"NULL");
                            printf ("  dwNameSpace:             %lu\n", result->dwNameSpace);
                            if (result->lpNSProviderId)
                                printf ("  lpNSProviderId:          { 0x%08lX,0x%04X,0x%04X, { 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X } }\n",
                                        result->lpNSProviderId->Data1, result->lpNSProviderId->Data2, result->lpNSProviderId->Data3, result->lpNSProviderId->Data4[0],
                                        result->lpNSProviderId->Data4[1], result->lpNSProviderId->Data4[2], result->lpNSProviderId->Data4[3], result->lpNSProviderId->Data4[4],
                                        result->lpNSProviderId->Data4[5], result->lpNSProviderId->Data4[6], result->lpNSProviderId->Data4[7]);
                            else
                                printf ("  lpNSProviderId:          NULL\n");
                            printf ("  lpszContext:             %S\n", result->lpszContext ? result->lpszContext : L"NULL");
                            printf ("  dwNumberOfProtocols:     %lu\n", result->dwNumberOfProtocols);
                            printf ("  lpszQueryString:         %S\n", result->lpszQueryString ? result->lpszQueryString : L"NULL");
                            printf ("  dwNumberOfCsAddrs:       %lu\n", result->dwNumberOfCsAddrs);
                            for (i = 0; i < result->dwNumberOfCsAddrs; i++)
                            {
                                switch (result->lpcsaBuffer[i].iSocketType)
                                {
                                case SOCK_STREAM:
                                    printf ("    %d: iSocketType = SOCK_STREAM\n", i);
                                    break;
                                case SOCK_DGRAM:
                                    printf ("    %d: iSocketType = SOCK_DGRAM\n", i);
                                    break;
                                default:
                                    printf ("    %d: iSocketType = %d\n", i, result->lpcsaBuffer[i].iSocketType);
                                }
                                switch (result->lpcsaBuffer[i].iProtocol)
                                {
                                case IPPROTO_TCP:
                                    printf ("    %d: iProtocol   = IPPROTO_TCP\n", i);
                                    break;
                                case IPPROTO_UDP:
                                    printf ("    %d: iProtocol   = IPPROTO_UDP\n", i);
                                    break;
                                default:
                                    printf ("    %d: iProtocol   = %d\n", i, result->lpcsaBuffer[i].iProtocol);
                                }
                                switch (result->lpcsaBuffer[i].LocalAddr.lpSockaddr->sa_family)
                                {
                                case AF_INET:
                                    printf ("    %d: loc family  = AF_INET\n", i);
                                    break;
                                case AF_INET6:
                                    printf ("    %d: loc family  = AF_INET6\n", i);
                                    break;
                                default:
                                    printf ("    %d: loc family  = %hu\n", i, result->lpcsaBuffer[i].LocalAddr.lpSockaddr->sa_family);
                                }
                                switch (result->lpcsaBuffer[i].RemoteAddr.lpSockaddr->sa_family)
                                {
                                case AF_INET:
                                    printf ("    %d: rem family  = AF_INET\n", i);
                                    break;
                                case AF_INET6:
                                    printf ("    %d: rem family  = AF_INET6\n", i);
                                    break;
                                default:
                                    printf ("    %d: rem family = %hu\n", i, result->lpcsaBuffer[i].RemoteAddr.lpSockaddr->sa_family);
                                }
                                char buf[1024];
                                DWORD buflen = 1024;
                                if (NO_ERROR == WSAAddressToStringA (result->lpcsaBuffer[i].LocalAddr.lpSockaddr, result->lpcsaBuffer[i].LocalAddr.iSockaddrLength, NULL, buf, &buflen))
                                    printf("\tLocal Address #%d: %s\n", i, buf);
                                else
                                    printf("\tLocal Address #%d: Can't convert: %lu\n", i, GetLastError ());
                                buflen = 1024;
                                if (NO_ERROR == WSAAddressToStringA (result->lpcsaBuffer[i].RemoteAddr.lpSockaddr, result->lpcsaBuffer[i].RemoteAddr.iSockaddrLength, NULL, buf, &buflen))
                                    printf("\tRemote Address #%d: %s\n", i, buf);
                                else
                                    printf("\tRemote Address #%d: Can't convert: %lu\n", i, GetLastError ());
                            }
                            printf ("  dwOutputFlags:           0x%08lX\n", result->dwOutputFlags);
                            printf ("  lpBlob:                  0x%p\n", result->lpBlob);
                            if (result->lpBlob)
                            {
                                struct hostent *he = malloc (result->lpBlob->cbSize);
                                if (he != NULL)
                                {
                                    GNUNET_memcpy (he, result->lpBlob->pBlobData, result->lpBlob->cbSize);
                                    UnpackHostEnt (he);
                                    print_hostent (he);
                                    free (he);
                                }
                            }
                        }
                        ret = api.NSPLookupServiceEnd (lookup);
                        if (ret != NO_ERROR)
                            printf ("NSPLookupServiceEnd() failed: %lu\n", GetLastError ());
                    }
                    api.NSPCleanup (&prov);
                }
            }
            FreeLibrary (nsp);
        }
    }
    else if (wargc == 3)
    {
        int s;
        ADDRINFOW hints;
        ADDRINFOW *result;
        ADDRINFOW *pos;

        memset (&hints, 0, sizeof (struct addrinfo));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        if (0 != (s = GetAddrInfoW (wargv[2], NULL, &hints, &result)))
        {
            fprintf (stderr, "Cound not resolve `%S' using GetAddrInfoW: %lu\n",
                     wargv[2], GetLastError ());
        }
        else
        {
            for (pos = result; pos != NULL; pos = pos->ai_next)
            {
                wchar_t tmpbuf[1024];
                DWORD buflen = 1024;
                if (0 == WSAAddressToStringW (pos->ai_addr, pos->ai_addrlen, NULL, tmpbuf, &buflen))
                    fprintf (stderr, "Result:\n"
                             "  flags: 0x%X\n"
                             "  family: 0x%X\n"
                             "  socktype: 0x%X\n"
                             "  protocol: 0x%X\n"
                             "  addrlen: %u\n"
                             "  addr: %S\n"
                             "  canonname: %S\n",
                             pos->ai_flags,
                             pos->ai_family,
                             pos->ai_socktype,
                             pos->ai_protocol,
                             pos->ai_addrlen,
                             tmpbuf,
                             pos->ai_canonname);
                else
                    fprintf (stderr, "Result:\n"
                             "  flags: 0x%X\n"
                             "  family: 0x%X\n"
                             "  socktype: 0x%X\n"
                             "  protocol: 0x%X\n"
                             "  addrlen: %u\n"
                             "  addr: %S\n"
                             "  canonname: %S\n",
                             pos->ai_flags,
                             pos->ai_family,
                             pos->ai_socktype,
                             pos->ai_protocol,
                             pos->ai_addrlen,
                             L"<can't stringify>",
                             pos->ai_canonname);
            }
            if (NULL != result)
                FreeAddrInfoW (result);
        }
    }
    WSACleanup();
    return r;
}