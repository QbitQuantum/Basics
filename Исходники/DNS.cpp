  DNS::HostMap DNS::resolve( const std::string& service, const std::string& proto,
                             const std::string& domain, const LogSink& logInstance )
  {
    const std::string dname = "_" +  service + "._" + proto + "." + domain;
    bool error = false;

    DNS::HostMap servers;
    DNS_RECORD* pRecord = NULL;
    DNS_STATUS status = DnsQuery_UTF8( dname.c_str(), DNS_TYPE_SRV, DNS_QUERY_STANDARD, NULL, &pRecord, NULL );
    if( status == ERROR_SUCCESS )
    {
      // NOTE: DnsQuery_UTF8 and DnsQuery_A really should have been defined with
      // PDNS_RECORDA instead of PDNS_RECORD, since that's what it is (even with _UNICODE defined).
      // We'll correct for that mistake with a cast.
      DNS_RECORDA* pRec = (DNS_RECORDA*)pRecord;
      do
      {
        if( pRec->wType == DNS_TYPE_SRV )
        {
          servers[pRec->Data.SRV.pNameTarget] = pRec->Data.SRV.wPort;
        }
        pRec = pRec->pNext;
      }
      while( pRec != NULL );
      DnsRecordListFree( pRecord, DnsFreeRecordList );
    }
    else
    {
      logInstance.warn( LogAreaClassDns, "DnsQuery_UTF8() failed: " + util::int2string( status ) );
      error = true;
    }

    if( error || !servers.size() )
    {
      servers = defaultHostMap( domain, logInstance );
    }

    return servers;
  }