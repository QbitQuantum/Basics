msgForMultiplyDefinedPV::msgForMultiplyDefinedPV ( 
    ipAddrToAsciiEngine & engine,
    callbackForMultiplyDefinedPV & cbIn, 
    const char * pChannelName, const char * pAcc ) :
    dnsTransaction ( engine.createTransaction () ), cb ( cbIn )
{
    strncpy ( this->acc, pAcc, sizeof ( this->acc ) );
    this->acc[ sizeof ( this->acc ) - 1 ] = '\0';
    strncpy ( this->channel, pChannelName, sizeof ( this->channel ) );
    this->channel[ sizeof ( this->channel ) - 1 ] = '\0';
}