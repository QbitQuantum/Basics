/*
 * @implemented
 */
INT
WSAAPI
GetAddrInfoW(IN PCWSTR pszNodeName,
             IN PCWSTR pszServiceName,
             IN const ADDRINFOW *ptHints,
             OUT PADDRINFOW *pptResult)
{
    INT iError = 0;
    INT iFlags = 0;
    INT iFamily = PF_UNSPEC;
    INT iSocketType = 0;
    INT iProtocol = 0;
    WORD wPort = 0;
    DWORD dwAddress = 0;
    PSERVENT ptService = NULL;
    PCHAR pc = NULL;
    BOOL bClone = FALSE;
    WORD wTcpPort = 0;
    WORD wUdpPort = 0;
    WCHAR CanonicalName[0x42];
    CHAR AnsiServiceName[256];
    CHAR AnsiNodeName[256];
    DPRINT("GetAddrInfoW: %S, %S, %p, %p\n", pszNodeName, pszServiceName, ptHints, pptResult);

    /* Assume error */
    *pptResult  = NULL;

    /* We must have at least one name to work with */
    if (!(pszNodeName) && !(pszServiceName))
    {
        /* Fail */
        SetLastError(EAI_NONAME);
        return EAI_NONAME;
    }

    /* Check if we got hints */
    if (ptHints)
    {
        /* Make sure these are empty */
        if ((ptHints->ai_addrlen) ||
            (ptHints->ai_canonname) ||
            (ptHints->ai_addr) ||
            (ptHints->ai_next))
        {
            /* Fail if they aren't */
            SetLastError(EAI_FAIL);
            return EAI_FAIL;
        }
        
        /* Save the flags and validate them */
        iFlags = ptHints->ai_flags;
        if ((iFlags & AI_CANONNAME) && !pszNodeName)
        {
            SetLastError(EAI_BADFLAGS);
            return EAI_BADFLAGS;
        }

        /* Save family and validate it */
        iFamily = ptHints->ai_family;
        if ((iFamily != PF_UNSPEC) && (iFamily != PF_INET))
        {
            SetLastError(EAI_FAMILY);
            return EAI_FAMILY;
        }

        /* Save socket type and validate it */
        iSocketType = ptHints->ai_socktype;
        if ((iSocketType != 0) &&
            (iSocketType != SOCK_STREAM) &&
            (iSocketType != SOCK_DGRAM) &&
            (iSocketType != SOCK_RAW))
        {
            SetLastError(EAI_SOCKTYPE);
            return EAI_SOCKTYPE;
        }

        /* Save the protocol */
        iProtocol = ptHints->ai_protocol;
    }

    /* Check if we have a service name */
    if (pszServiceName)
    {
        /* We need to convert it to ANSI */
        WideCharToMultiByte(CP_ACP,
                            0,
                            pszServiceName, 
                            -1, 
                            AnsiServiceName, 
                            sizeof(AnsiServiceName),
                            NULL,
                            0);

        /* Get the port */
        wPort = (WORD)strtoul(AnsiServiceName, &pc, 10);

        /* Check if the port string is numeric */
        if (*pc == '\0')
        {
            /* Get the port directly */
            wPort = wTcpPort = wUdpPort = htons(wPort);

#if 0
            /* Check if this is both TCP and UDP */
            if (iSocketType == 0)
            {
                /* Set it to TCP for now, but remember to clone */
                bClone = TRUE;
                iSocketType = SOCK_STREAM;
            }
#endif
        }
        else
        {
            wPort = 0;
            /* The port name was a string. Check if this is a UDP socket */
            if ((iSocketType == 0) || (iSocketType == SOCK_DGRAM))
            {
                /* It's UDP, do a getservbyname */
                ptService = getservbyname(AnsiServiceName, "udp");

                /* If we got a servent, return the port from it */
                if (ptService) wPort = wUdpPort = ptService->s_port;
            }

            /* Check if this is a TCP socket */
            if ((iSocketType == 0) || (iSocketType == SOCK_STREAM))
            {
                /* It's TCP, do a getserbyname */
                ptService = getservbyname(AnsiServiceName, "tcp");

                /* Return the port from the servent */
                if (ptService) wPort = wTcpPort = ptService->s_port;
            }
            
            /* If we got 0, then fail */
            if (wPort == 0)
            {
                SetLastError(EAI_SERVICE);
                return EAI_SERVICE;
            }

            /* Check if this was for both */
            if (iSocketType == 0)
            {
                /* Do the TCP case right now */
                if (wTcpPort && !wUdpPort)
                    iSocketType = SOCK_STREAM;
                if (!wTcpPort && wUdpPort)
                    iSocketType = SOCK_DGRAM;
                //bClone = (wTcpPort && wUdpPort); 
            }
        }
    }

    /* Check if no node was given or if this is is a valid IPv4 address */
    if ((!pszNodeName) || (ParseV4Address(pszNodeName, &dwAddress)))
    {
        /* Check if we don't have a node name */
        if (!pszNodeName)
        {
            /* Make one up based on the flags */
            dwAddress = htonl((iFlags & AI_PASSIVE) ?
                              INADDR_ANY : INADDR_LOOPBACK);
        }
        
        /* Create the Addr Info */
        *pptResult = NewAddrInfo(iSocketType, iProtocol, wPort, dwAddress);

        /* If we didn't get one back, assume out of memory */
        if (!(*pptResult)) iError = EAI_MEMORY;
        
        /* Check if we have success and a nodename */
        if (!iError && pszNodeName)
        {
            /* Set AI_NUMERICHOST since this is a numeric string */
            (*pptResult)->ai_flags |= AI_NUMERICHOST;
            
            /* Check if the canonical name was requested */
            if (iFlags & AI_CANONNAME)
            {
                /* Get the canonical name */
                GetNameInfoW((*pptResult)->ai_addr,
                             (socklen_t)(*pptResult)->ai_addrlen,
                             CanonicalName,
                             0x41,
                             NULL,
                             0,
                             2);

                /* Allocate memory for a copy */
                (*pptResult)->ai_canonname = HeapAlloc(WsSockHeap,
                                                       0,
                                                       wcslen(CanonicalName));
                
                if (!(*pptResult)->ai_canonname)
                {
                    /* No memory for the copy */
                    iError = EAI_MEMORY;
                }
                else
                {
                    /* Duplicate the string */
                    RtlMoveMemory((*pptResult)->ai_canonname,
                                  CanonicalName,
                                  wcslen(CanonicalName));
                }
            }
        }
    }
    else if (iFlags & AI_NUMERICHOST)
    {
        /* No name for this request (we have a non-numeric name) */
        iError = EAI_NONAME;
    }
    else
    {
        /* We need to convert it to ANSI */
        WideCharToMultiByte(CP_ACP,
                            0,
                            pszNodeName, 
                            -1, 
                            AnsiNodeName, 
                            sizeof(AnsiNodeName),
                            NULL,
                            0);

        /* Non-numeric name, do DNS lookup */
        iError = LookupAddressForName(AnsiNodeName,
                                      iSocketType,
                                      iProtocol,
                                      wPort,
                                      (iFlags & AI_CANONNAME),
                                      pptResult);
    }

    /* If all was good and the caller requested UDP and TCP */
    if (!iError && bClone)
    {
        /* Process UDP now, we already did TCP */
        iError = CloneAddrInfo(wUdpPort, *pptResult);
    }

    /* If we've hit an error till here */
    if (iError)
    {
        /* Free the address info and return nothing */
        FreeAddrInfoW(*pptResult);
        *pptResult = NULL;        
    }

    /* Return to caller */
    SetLastError(iError);
    return iError;
}