char* RTSPServer::rtspURLPrefix(int clientSocket) const {
  struct sockaddr_in ourAddress;
  if (clientSocket < 0) {
		// Use our default IP address in the URL:
	  ourAddress.sin_addr.s_addr = ReceivingInterfaceAddr != 0
			? ReceivingInterfaceAddr
			: ourIPAddress(envir()); // hack
	} else {
	  SOCKLEN_T namelen = sizeof ourAddress;
	  getsockname(clientSocket, (struct sockaddr*)&ourAddress, &namelen);
	}

  char urlBuffer[100]; // more than big enough for "rtsp://<ip-address>:<port>/"

  portNumBits portNumHostOrder = ntohs(fServerPort.num());
  if (portNumHostOrder == 554 /* the default port number */) {
	  sprintf(urlBuffer, "rtsp://%s/", our_inet_ntoa(ourAddress.sin_addr));
	} else {
	  sprintf(urlBuffer, "rtsp://%s:%hu/",
		  our_inet_ntoa(ourAddress.sin_addr), portNumHostOrder);
	}

  return strDup(urlBuffer);
}