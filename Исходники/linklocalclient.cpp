    bool Client::resolve( const std::string& service, const std::string& type,
                          const std::string& domain )
    {
      m_to = service;
      m_rRef = 0;
      DNSServiceErrorType e = DNSServiceResolve( &m_rRef, 0, m_interface, service.c_str(), type.c_str(),
                                                domain.c_str(), &handleResolveReply, this );
      if( e != kDNSServiceErr_NoError )
      {
        DNSServiceRefDeallocate( m_rRef );
        m_rRef = 0;
        return false;
      }
      m_currentRef = m_rRef;

      return true;
    }