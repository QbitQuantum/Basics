vvBonjour::ErrorType vvBonjourBrowser::browseForServiceType(const std::string& serviceType, const std::string domain, const double to)
{
#ifdef HAVE_BONJOUR
  DNSServiceErrorType error;
  DNSServiceRef  serviceRef;

  _bonjourEntries.clear();

  error = DNSServiceBrowse(&serviceRef,
              0,                    // no flags
              0,                    // all network interfaces
              serviceType.c_str(),  // service type
              domain.c_str(),       // default domains
              BrowseCallBack,       // call back function
              this);                // adress of pointer to eventloop
  if (error == kDNSServiceErr_NoError)
  {
    _timeout = to;
    _eventLoop = new vvBonjourEventLoop(serviceRef);
    if(to != -1.0)
      _eventLoop->run(false, to);
    else
      _eventLoop->run(true, to);
  }
  else
  {
    std::ostringstream errmsg;
    errmsg << "vvBonjourBrowser::browseForServiceType(): DNSServiceBrowse() returned with error no " << error;
    vvDebugMsg::msg(2, errmsg.str().c_str());
    return vvBonjour::VV_ERROR;
  }

  return vvBonjour::VV_OK;
#else
  (void)serviceType;
  (void)domain;
  (void)to;
  return vvBonjour::VV_ERROR;
#endif
}