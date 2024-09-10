BOOLEAN
WINAPI
Dns_StringToDnsAddrEx(OUT PDNS_ADDRESS DnsAddr,
                      IN PVOID AddressName,
                      IN DWORD AddressFamily,
                      IN BOOLEAN Unicode,
                      IN BOOLEAN Reverse)
{
    IN6_ADDR Addr;
    BOOLEAN Return;
    INT ErrorCode = ERROR_SUCCESS;
    CHAR AnsiName[INET6_ADDRSTRLEN + sizeof("ip6.arpa.")];
    ULONG Size = sizeof(AnsiName);

    /* First check if this is a reverse address string */
    if ((Reverse) && (Unicode))
    {
        /* Convert it right now to ANSI as an optimization */
        Dns_StringCopy(AnsiName,
                       &Size,
                       AddressName,
                       0,
                       UnicodeString,
                       AnsiString);

        /* Use the ANSI Name instead */
        AddressName = AnsiName;
    }

    /* 
     * If the caller doesn't know what the family is, we'll assume IPv4 and
     * check if we failed or not. If the caller told us it's IPv4, then just
     * do IPv4...
     */
    if ((AddressFamily == AF_UNSPEC) || (AddressFamily == AF_INET))
    {
        /* Now check if the caller gave us the reverse name or not */
        if (Reverse)
        {
            /* Get the Address */
            Return = Dns_Ip4ReverseNameToAddress_A((PIN_ADDR)&Addr, AddressName);
        }
        else
        {
            /* Check if the caller gave us unicode or not */
            if (Unicode)
            {
                /* Get the Address */
                Return = Dns_Ip4StringToAddress_W((PIN_ADDR)&Addr, AddressName);
            }
            else
            {
                /* Get the Address */
                Return = Dns_Ip4StringToAddress_A((PIN_ADDR)&Addr, AddressName);
            }
        }

        /* Check if we suceeded */
        if (Return)
        {
            /* Build the IPv4 Address */
            DnsAddr_BuildFromIp4(DnsAddr, *(PIN_ADDR)&Addr, 0);

            /* So we don't go in the code below... */
            AddressFamily = AF_INET;
        }
    }

    /* If we are here, either AF_INET6 was specified or IPv4 failed */
    if ((AddressFamily == AF_UNSPEC) || (AddressFamily == AF_INET6))
    {
        /* Now check if the caller gave us the reverse name or not */
        if (Reverse)
        {
            /* Get the Address */
            Return = Dns_Ip6ReverseNameToAddress_A(&Addr, AddressName);
            if (Return)
            {
                /* Build the IPv6 Address */
                DnsAddr_BuildFromIp6(DnsAddr, &Addr, 0, 0);
            }
            else
            {
                goto Quickie;
            }
        }
        else
        {
            /* Check if the caller gave us unicode or not */
            if (Unicode)
            {
                /* Get the Address */
                if (NT_SUCCESS(RtlIpv6StringToAddressExW(AddressName,
                                                         &DnsAddr->Ip6Address.sin6_addr,
                                                         &DnsAddr->Ip6Address.sin6_scope_id,
                                                         &DnsAddr->Ip6Address.sin6_port)))
                    Return = TRUE;
                else
                    Return = FALSE;
            }
            else
            {
                /* Get the Address */
                if (NT_SUCCESS(RtlIpv6StringToAddressExA(AddressName,
                                                         &DnsAddr->Ip6Address.sin6_addr,
                                                         &DnsAddr->Ip6Address.sin6_scope_id,
                                                         &DnsAddr->Ip6Address.sin6_port)))
                   Return = TRUE;
                else
                   Return = FALSE;
            }
        }

        /* Check if we suceeded */
        if (Return)
        {
            /* Finish setting up the structure */
            DnsAddr->Ip6Address.sin6_family = AF_INET6;
            DnsAddr->AddressLength = sizeof(SOCKADDR_IN6);
        }
    }
    else if (AddressFamily != AF_INET)
    {
        /* You're like.. ATM or something? Get outta here! */
        RtlZeroMemory(DnsAddr, sizeof(DNS_ADDRESS));
        SetLastError(WSA_INVALID_PARAMETER);
    }

Quickie:
    /* Return success or failure */
    return (ErrorCode == ERROR_SUCCESS);
}