void getSDPDescription(RTSPClient::responseHandler* afterFunc) {
  extern char* proxyServerName;
  if (proxyServerName != NULL) {
    // Tell the SIP client about the proxy:
    NetAddressList addresses(proxyServerName);
    if (addresses.numAddresses() == 0) {
      ourSIPClient->envir() << "Failed to find network address for \"" << proxyServerName << "\"\n";
    } else {
      NetAddress address = *(addresses.firstAddress());
      unsigned proxyServerAddress // later, allow for IPv6 #####
	= *(unsigned*)(address.data());
      extern unsigned short proxyServerPortNum;
      if (proxyServerPortNum == 0) proxyServerPortNum = 5060; // default

      ourSIPClient->setProxyServer(proxyServerAddress, proxyServerPortNum);
    }
  }

  extern unsigned short desiredPortNum;
  unsigned short clientStartPortNum = desiredPortNum;
  if (clientStartPortNum == 0) clientStartPortNum = 8000; // default
  ourSIPClient->setClientStartPortNum(clientStartPortNum);

  extern char const* streamURL;
  char const* username = ourAuthenticator == NULL ? NULL : ourAuthenticator->username();
  char const* password = ourAuthenticator == NULL ? NULL : ourAuthenticator->password();
  char* result;
  if (username != NULL && password != NULL) {
    result = ourSIPClient->inviteWithPassword(streamURL, username, password);
  } else {
    result = ourSIPClient->invite(streamURL);
  }

  int resultCode = result == NULL ? -1 : 0;
  afterFunc(NULL, resultCode, strDup(result));
}