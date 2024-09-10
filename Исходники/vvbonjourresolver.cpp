vvBonjour::ErrorType vvBonjourResolver::resolveBonjourEntry(const vvBonjourEntry& entry)
{
#ifdef HAVE_BONJOUR
  vvDebugMsg::msg(3, "vvBonjourResolver::resolveBonjourEntry()");
  DNSServiceErrorType error;
  DNSServiceRef  serviceRef;

  error = DNSServiceResolve(&serviceRef,
                 0,                 // no flags
                 0,                 // all network interfaces
                 entry.getServiceName().c_str(),    //name
                 entry.getRegisteredType().c_str(), // service type
                 entry.getReplyDomain().c_str(),    //domain
                 ResolveCallBack,
                 this);             // no context

  if (error == kDNSServiceErr_NoError)
  {
    _eventLoop = new vvBonjourEventLoop(serviceRef);
    _eventLoop->run();
    return vvBonjour::VV_OK;
  }
  else
  {
    vvDebugMsg::msg(2, "vvBonjourResolver::resolveBonjourEntry(): DNSServiceResolve failed with error code ", error);
    return vvBonjour::VV_ERROR;
  }
#else
  (void)entry;
  return vvBonjour::VV_ERROR;
#endif
}