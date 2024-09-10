void NetPlatform_addAddress(const char* interfaceName,
                            char* addrBytes,
                            int prefixLen,
                            int addrFam,
                            struct Log* logger,
                            struct Except* eh)
{
    unsigned long ifIndex;
    WinFail_check(eh, GetAdapterIndex(interfaceName, &ifIndex));

    MIB_UNICASTIPADDRESS_ROW ipRow;
    InitializeUnicastIpAddressEntry(&ipRow);
    ipRow.InterfaceIndex = ifIndex;

    ipRow.Address.si_family = addrFamily;
    if (addrFam == Socket_AF_INET6) {
        Bits_memcpy(&ipRow.Address.Ipv6.sin6_addr, addr, 16);
    } else if (addrFam == Socket_AF_INET) {
        Bits_memcpy(&ipRow.Address.Ipv4.sin_addr, addr, 4);
    } else {
        Assert_always(0);
    }

    ipRow.OnLinkPrefixLength = prefixLen;

    WinFail_check(eh, CreateUnicastIpAddressEntry(&ipRow));
}