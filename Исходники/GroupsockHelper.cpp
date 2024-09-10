netAddressBits ourIPAddress(UsageEnvironment& env) {
  static netAddressBits ourAddress = 0;
  int sock = -1;
  struct in_addr testAddr;

  if (ReceivingInterfaceAddr != INADDR_ANY) {
    // Hack: If we were told to receive on a specific interface address, then 
    // define this to be our ip address:
    ourAddress = ReceivingInterfaceAddr;
  }

  if (ourAddress == 0) {
    // We need to find our source address
    struct sockaddr_in fromAddr;
    fromAddr.sin_addr.s_addr = 0;

    // Get our address by sending a (0-TTL) multicast packet,
    // receiving it, and looking at the source address used.
    // (This is kinda bogus, but it provides the best guarantee
    // that other nodes will think our address is the same as we do.)
    do {
      loopbackWorks = 0; // until we learn otherwise

      testAddr.s_addr = our_inet_addr("228.67.43.91"); // arbitrary
      Port testPort(15947); // ditto

      sock = setupDatagramSocket(env, testPort);
      if (sock < 0) break;

      if (!socketJoinGroup(env, sock, testAddr.s_addr)) break;

      unsigned char testString[] = "hostIdTest";
      unsigned testStringLength = sizeof testString;

      if (!writeSocket(env, sock, testAddr, testPort, 0,
		       testString, testStringLength)) break;

      // Block until the socket is readable (with a 5-second timeout):
      fd_set rd_set;
      FD_ZERO(&rd_set);
      FD_SET((unsigned)sock, &rd_set);
      const unsigned numFds = sock+1;
      struct timeval timeout;
      timeout.tv_sec = 5;
      timeout.tv_usec = 0;
      int result = select(numFds, &rd_set, NULL, NULL, &timeout);
      if (result <= 0) break;

      unsigned char readBuffer[20];
      int bytesRead = readSocket(env, sock,
				 readBuffer, sizeof readBuffer,
				 fromAddr);
      if (bytesRead != (int)testStringLength
	  || strncmp((char*)readBuffer, (char*)testString, testStringLength) != 0) {
	break;
      }

      // We use this packet's source address, if it's good:
      loopbackWorks = !badAddressForUs(fromAddr.sin_addr.s_addr);
    } while (0);

    if (sock >= 0) {
      socketLeaveGroup(env, sock, testAddr.s_addr);
      closeSocket(sock);
    }

    if (!loopbackWorks) do {
      // We couldn't find our address using multicast loopback,
      // so try instead to look it up directly - by first getting our host name, and then resolving this host name
      char hostname[100];
      hostname[0] = '\0';
      int result = gethostname(hostname, sizeof hostname);
      if (result != 0 || hostname[0] == '\0') {
	env.setResultErrMsg("initial gethostname() failed");
	break;
      }

      // Try to resolve "hostname" to an IP address:
      NetAddressList addresses(hostname);
      NetAddressList::Iterator iter(addresses);
      NetAddress const* address;

      // Take the first address that's not bad:
      netAddressBits addr = 0;
      while ((address = iter.nextAddress()) != NULL) {
	netAddressBits a = *(netAddressBits*)(address->data());
	if (!badAddressForUs(a)) {
	  addr = a;
	  break;
	}
      }

      // Assign the address that we found to "fromAddr" (as if the 'loopback' method had worked), to simplify the code below: 
      fromAddr.sin_addr.s_addr = addr;
    } while (0);

    // Make sure we have a good address:
    netAddressBits from = fromAddr.sin_addr.s_addr;
    if (badAddressForUs(from)) {
      char tmp[100];
      sprintf(tmp, "This computer has an invalid IP address: %s", AddressString(from).val());
      env.setResultMsg(tmp);
      from = 0;
    }

    ourAddress = from;

    // Use our newly-discovered IP address, and the current time,
    // to initialize the random number generator's seed:
    struct timeval timeNow;
    gettimeofday(&timeNow, NULL);
    unsigned seed = ourAddress^timeNow.tv_sec^timeNow.tv_usec;
    our_srandom(seed);
  }
  return ourAddress;
}