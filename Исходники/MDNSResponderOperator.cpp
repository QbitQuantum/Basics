nsresult
ResolveOperator::Start()
{
  nsresult rv;
  if (NS_WARN_IF(NS_FAILED(rv = MDNSResponderOperator::Start()))) {
    return rv;
  }

  nsAutoCString name;
  mServiceInfo->GetServiceName(name);
  nsAutoCString type;
  mServiceInfo->GetServiceType(type);
  nsAutoCString domain;
  mServiceInfo->GetDomainName(domain);

  LOG_I("Resolve: (%s), (%s), (%s)", name.get(), type.get(), domain.get());

  DNSServiceRef service = nullptr;
  DNSServiceErrorType err =
    DNSServiceResolve(&service,
                      0,
                      kDNSServiceInterfaceIndexAny,
                      name.get(),
                      type.get(),
                      domain.get(),
                      (DNSServiceResolveReply)&ResolveReplyRunnable::Reply,
                      this);

  if (NS_WARN_IF(kDNSServiceErr_NoError != err)) {
    if (mListener) {
      mListener->OnResolveFailed(mServiceInfo, err);
    }
    return NS_ERROR_FAILURE;
  }

  mDeleteProtector = this;
  return ResetService(service);
}