bool CZeroconfBrowserWIN::doResolveService(CZeroconfBrowser::ZeroconfService& fr_service, double f_timeout)
{
  DNSServiceErrorType err;
  DNSServiceRef sdRef = NULL;

  err = DNSServiceResolve(&sdRef, 0, kDNSServiceInterfaceIndexAny, fr_service.GetName(), fr_service.GetType(), fr_service.GetDomain(), ResolveCallback, &fr_service);

  if( err != kDNSServiceErr_NoError )
  {
    if (sdRef)
      DNSServiceRefDeallocate(sdRef);

    CLog::Log(LOGERROR, "ZeroconfBrowserWIN: DNSServiceResolve returned (error = %ld)", (int) err);
    return false;
  }

  err = DNSServiceProcessResult(sdRef);

  if (err != kDNSServiceErr_NoError)
      CLog::Log(LOGERROR, "ZeroconfBrowserWIN::doResolveService DNSServiceProcessResult returned (error = %ld)", (int) err);

  if (sdRef)
    DNSServiceRefDeallocate(sdRef);

  return true;
}