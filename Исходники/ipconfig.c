static void print_full_information(void)
{
    static const WCHAR newlineW[] = {'\n',0};
    static const WCHAR emptyW[] = {0};

    FIXED_INFO *info;
    IP_ADAPTER_ADDRESSES *adapters;
    ULONG out = 0;

    if (GetNetworkParams(NULL, &out) == ERROR_BUFFER_OVERFLOW)
    {
        info = HeapAlloc(GetProcessHeap(), 0, out);
        if (!info)
            exit(1);

        if (GetNetworkParams(info, &out) == ERROR_SUCCESS)
        {
            WCHAR hostnameW[MAX_HOSTNAME_LEN + 4];

            MultiByteToWideChar(CP_ACP, 0, info->HostName, -1, hostnameW, sizeof(hostnameW)/sizeof(hostnameW[0]));
            print_field(STRING_HOSTNAME, hostnameW);

            /* FIXME: Output primary DNS suffix. */

            print_field(STRING_NODE_TYPE, nodetype_to_string(info->NodeType));
            print_field(STRING_IP_ROUTING, boolean_to_string(info->EnableRouting));

            /* FIXME: Output WINS proxy status and DNS suffix search list. */

            ipconfig_printfW(newlineW);
        }

        HeapFree(GetProcessHeap(), 0, info);
    }

    if (GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_ALL_GATEWAYS,
                             NULL, NULL, &out) == ERROR_BUFFER_OVERFLOW)
    {
        adapters = HeapAlloc(GetProcessHeap(), 0, out);
        if (!adapters)
            exit(1);

        if (GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_ALL_GATEWAYS,
                                 NULL, adapters, &out) == ERROR_SUCCESS)
        {
            IP_ADAPTER_ADDRESSES *p;

            for (p = adapters; p; p = p->Next)
            {
                IP_ADAPTER_UNICAST_ADDRESS *addr;
                WCHAR physaddr_buf[3 * MAX_ADAPTER_ADDRESS_LENGTH];
                IP_ADAPTER_GATEWAY_ADDRESS_LH *gateway;
                WCHAR addr_buf[54];

                ipconfig_message_printfW(STRING_ADAPTER_FRIENDLY, iftype_to_string(p->IfType), p->FriendlyName);
                ipconfig_printfW(newlineW);
                print_field(STRING_CONN_DNS_SUFFIX, p->DnsSuffix);
                print_field(STRING_DESCRIPTION, p->Description);
                print_field(STRING_PHYS_ADDR, physaddr_to_string(physaddr_buf, p->PhysicalAddress, p->PhysicalAddressLength));
                print_field(STRING_DHCP_ENABLED, boolean_to_string(p->Flags & IP_ADAPTER_DHCP_ENABLED));

                /* FIXME: Output autoconfiguration status. */

                for (addr = p->FirstUnicastAddress; addr; addr = addr->Next)
                {
                    if (socket_address_to_string(addr_buf, sizeof(addr_buf)/sizeof(WCHAR), &addr->Address))
                        print_field(STRING_IP_ADDRESS, addr_buf);
                    /* FIXME: Output corresponding subnet mask. */
                }

                if (p->FirstGatewayAddress)
                {
                    if (socket_address_to_string(addr_buf, sizeof(addr_buf)/sizeof(WCHAR), &p->FirstGatewayAddress->Address))
                        print_field(STRING_DEFAULT_GATEWAY, addr_buf);

                    for (gateway = p->FirstGatewayAddress->Next; gateway; gateway = gateway->Next)
                    {
                        if (socket_address_to_string(addr_buf, sizeof(addr_buf)/sizeof(WCHAR), &gateway->Address))
                            print_value(addr_buf);
                    }
                }
                else
                    print_field(STRING_DEFAULT_GATEWAY, emptyW);

                ipconfig_printfW(newlineW);
            }
        }

        HeapFree(GetProcessHeap(), 0, adapters);
    }
}