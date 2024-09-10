bool vvBonjourRegistrar::registerService(const vvBonjourEntry& entry, const ushort port)
{
#ifdef HAVE_BONJOUR
  vvDebugMsg::msg(3, "vvBonjourRegistrar::registerService() Enter");

  DNSServiceErrorType error = DNSServiceRegister(&::serviceRef,
                0,                // no flags
                0,                // all network interfaces
                entry.getServiceName().c_str(),
                entry.getRegisteredType().c_str(),
                entry.getReplyDomain().c_str(),
                NULL,             // use default host name
                htons(port),      // port number
                0,                // length of TXT record
                NULL,             // no TXT record
                RegisterCallBack, // call back function
                this);            // no context

  if (error == kDNSServiceErr_NoError)
  {
    _eventLoop = new vvBonjourEventLoop(::serviceRef);
    _eventLoop->run(false, -1.0);
    return true;
  }
  else
  {
    vvDebugMsg::msg(2, "vvBonjourRegistrar::registerService(): DNSServiceResolve failed with error code ", error);
    return false;
  }
#else
  (void)entry;
  (void)port;
  return false;
#endif
}