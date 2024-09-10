bool CZeroconfBrowserMDNS::doAddServiceType(const std::string& fcr_service_type)
{
  DNSServiceErrorType err;
  DNSServiceRef browser = NULL;

#if !defined(HAS_MDNS_EMBEDDED)
  if(m_browser == NULL)
  {
    err = DNSServiceCreateConnection(&m_browser);
    if (err != kDNSServiceErr_NoError)
    {
      CLog::Log(LOGERROR, "ZeroconfBrowserMDNS: DNSServiceCreateConnection failed with error = %ld", (int) err);
      return false;
    }
  }
#endif //!HAS_MDNS_EMBEDDED

  {
    CSingleLock lock(m_data_guard);
    browser = m_browser;
    err = DNSServiceBrowse(&browser, kDNSServiceFlagsShareConnection, kDNSServiceInterfaceIndexAny, fcr_service_type.c_str(), NULL, BrowserCallback, this);
  }

  if( err != kDNSServiceErr_NoError )
  {
    if (browser)
      DNSServiceRefDeallocate(browser);

    CLog::Log(LOGERROR, "ZeroconfBrowserMDNS: DNSServiceBrowse returned (error = %ld)", (int) err);
    return false;
  }

  //store the browser
  {
    CSingleLock lock(m_data_guard);
    m_service_browsers.insert(std::make_pair(fcr_service_type, browser));
  }

  return true;
}