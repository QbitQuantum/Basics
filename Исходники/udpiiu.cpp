bool udpiiu::exceptionRespAction ( 
    const caHdr &msg, 
    const osiSockAddr & net_addr, const epicsTime & currentTime )
{
    const caHdr &reqMsg = * ( &msg + 1 );
    char name[64];
    sockAddrToDottedIP ( &net_addr.sa, name, sizeof ( name ) );
    char date[64];
    currentTime.strftime ( date, sizeof ( date ), "%a %b %d %Y %H:%M:%S");

    if ( msg.m_postsize > sizeof ( caHdr ) ){
        errlogPrintf ( 
            "error condition \"%s\" detected by %s with context \"%s\" at %s\n", 
            ca_message ( msg.m_available ), 
            name, reinterpret_cast <const char *> ( &reqMsg + 1 ), date );
    }
    else{
        errlogPrintf ( 
            "error condition \"%s\" detected by %s at %s\n", 
            ca_message ( msg.m_available ), name, date );
    }

    return true;
}