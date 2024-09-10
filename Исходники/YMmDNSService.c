bool YMmDNSServiceStart( YMmDNSServiceRef s_ )
{
    __ym_mdns_service_t *s = (__ym_mdns_service_t *)s_;
    
    DNSServiceRef *serviceRef = (DNSServiceRef *)calloc( 1, sizeof(DNSServiceRef) );
    uint16_t netPort = htons(s->port);
    bool txtExists = (s->txtRecord != NULL);
    uint16_t txtLength = txtExists ? TXTRecordGetLength((TXTRecordRef *)s->txtRecord) : 0;
    const void *txt = txtExists ? TXTRecordGetBytesPtr((TXTRecordRef *)s->txtRecord) : NULL;
    DNSServiceErrorType result = DNSServiceRegister(serviceRef,
                                                    0, // DNSServiceFlags
                                                    0, // interfaceIndex (0=all)
                                                    YMSTR(s->name),
                                                    YMSTR(s->type),
                                                    NULL, // domain
                                                    NULL, // host
                                                    netPort,
                                                    txtLength,
                                                    txt,
                                                    __ymmdns_register_callback, // DNSServiceRegisterReply
                                                    s); // context
    
    if( result != kDNSServiceErr_NoError ) {
        // on error "the callback is never invoked and the DNSServiceRef is not initialized"
        // leading me to think we free instead of DNSServiceRefDeallocate
        free(serviceRef);
        ymlog("mdns: DNSServiceRegister failed: %s/%s:%u: %d",YMSTR(s->type),YMSTR(s->name),(unsigned)s->port,result);
        return false;
    }
    
    s->dnsService = serviceRef;
    s->advertising = true;

    ymlog("mdns: published %s/%s:%u",YMSTR(s->type),YMSTR(s->name),(unsigned)s->port);
    return true;
}