static DNSServiceErrorType RegisterService(DNSServiceRef *sdref,
                                           const char *nam, const char *typ, const char *dom, const char *host, const char *port, AutoDiscoveryServerImpl *context)
{
    DNSServiceFlags flags        = 0;
    uint16_t        PortAsNumber = atoi(port);
    Opaque16        registerPort =
    {
        { PortAsNumber >> 8, PortAsNumber & 0xFF }
    };
    unsigned char txt[2048] = "";
    unsigned char *ptr      = txt;

    if (nam[0] == '.' && nam[1] == 0)
        nam = "";                                 // We allow '.' on the command line as a synonym for empty string

    if (dom[0] == '.' && dom[1] == 0)
        dom = "";                                 // We allow '.' on the command line as a synonym for empty string

    OSG_INFO << "AutoDiscoveryImpl :: Registering Service " << (nam[0] ? nam : "<<Default>>") << " " << typ << " " << (dom[0] ? "." : "", dom) << std::endl;
    if (host && *host)
    {
        OSG_INFO << "AutoDiscoveryImpl :: host " << host << " port " << port << std::endl;
    }

    // printf("\n");

    // flags |= kDNSServiceFlagsAllowRemoteQuery;
    // flags |= kDNSServiceFlagsNoAutoRename;

    return(DNSServiceRegister(sdref, flags, kDNSServiceInterfaceIndexAny, nam, typ, dom, host, registerPort.NotAnInteger, (uint16_t) (ptr - txt), txt, reg_reply, context));
}