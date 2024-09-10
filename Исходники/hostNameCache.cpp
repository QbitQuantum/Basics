hostNameCache::hostNameCache ( 
    const osiSockAddr & addr, ipAddrToAsciiEngine & engine ) :
    dnsTransaction ( engine.createTransaction() ), nameLength ( 0 )
{
    sockAddrToDottedIP ( &addr.sa, hostNameBuf, sizeof ( hostNameBuf ) );
    hostNameBuf[ sizeof ( hostNameBuf ) - 1 ] = '\0';
    nameLength = strlen ( hostNameBuf );
    this->dnsTransaction.ipAddrToAscii ( addr, *this );
}