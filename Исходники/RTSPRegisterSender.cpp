Boolean RTSPDeregisterSender::setRequestFields(RequestRecord* request,
					       char*& cmdURL, Boolean& cmdURLWasAllocated,
					       char const*& protocolStr,
					       char*& extraHeaders, Boolean& extraHeadersWereAllocated) {
  if (strcmp(request->commandName(), "DEREGISTER") == 0) {
    RequestRecord_DEREGISTER* request_DEREGISTER = (RequestRecord_DEREGISTER*)request;

    setBaseURL(request_DEREGISTER->rtspURLToDeregister());
    cmdURL = (char*)url();
    cmdURLWasAllocated = False;

    // Generate the "Transport:" header that will contain our DEREGISTER-specific parameters.  This will be "extraHeaders".
    // First, generate the "proxy_url_suffix" parameter string, if any:
    char* proxyURLSuffixParameterStr;
    if (request_DEREGISTER->proxyURLSuffix() == NULL) {
      proxyURLSuffixParameterStr = strDup("");
    } else {
      char const* proxyURLSuffixParameterFmt = "proxy_url_suffix=%s";
      unsigned proxyURLSuffixParameterSize = strlen(proxyURLSuffixParameterFmt)
	+ strlen(request_DEREGISTER->proxyURLSuffix());
      proxyURLSuffixParameterStr = new char[proxyURLSuffixParameterSize];
      sprintf(proxyURLSuffixParameterStr, proxyURLSuffixParameterFmt, request_DEREGISTER->proxyURLSuffix());
    }

    char const* transportHeaderFmt = "Transport: %s\r\n";
    unsigned transportHeaderSize = strlen(transportHeaderFmt) + strlen(proxyURLSuffixParameterStr);
    char* transportHeaderStr = new char[transportHeaderSize];
    sprintf(transportHeaderStr, transportHeaderFmt,
	    proxyURLSuffixParameterStr);
    delete[] proxyURLSuffixParameterStr;

    extraHeaders = transportHeaderStr;
    extraHeadersWereAllocated = True;

    return True;
  } else {
    return RTSPClient::setRequestFields(request, cmdURL, cmdURLWasAllocated, protocolStr, extraHeaders, extraHeadersWereAllocated);
  }
}