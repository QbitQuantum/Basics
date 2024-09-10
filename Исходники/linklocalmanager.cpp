void Manager::registerService()
{
    if( m_publishRef )
        deregisterService();

    m_server.connect();

    std::string txtRecord;
    txtRecord += (char)9; // length of mandatory txtvers=1
    txtRecord += "txtvers=1"; // this is here because it SHOULD be the first entry
    StringMap::const_iterator it = m_txtData.begin();
    for( ; it != m_txtData.end(); ++it )
    {
        txtRecord += (char)( (*it).first.length() + (*it).second.length() + 1 );
        txtRecord += (*it).first;
        txtRecord += '=';
        txtRecord += (*it).second;
    }

    std::string service = m_user + "@";
    if( m_host.empty() )
    {
        char host[65];
        gethostname( host, 65 );
        service += host;
    }
    else
        service += m_host;

    /*DNSServiceErrorType e =*/ DNSServiceRegister( &m_publishRef,
            0,                                      // flags
            m_interface,                            // interface, 0 = any, -1 = local only
            service.c_str(),                        // service name, 0 = local computer name
            LINKLOCAL_SERVICE_TYPE.c_str(),         // service type
            m_domain.c_str(),                       // domain, 0 = default domain(s)
            m_host.c_str(),                         // host, 0 = default host name(s)
            htons( m_port ),                        // port
            (short unsigned int)txtRecord.length(), // TXT record length
            (const void*)txtRecord.c_str(),         // TXT record
            0,                                      // callback
            0 );                                    // context
}