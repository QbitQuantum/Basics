static int httpTransact(char* szUrl, char* szResult, int resSize, char* szActionName, ReqType reqtype)
{
	// Parse URL
	char szHost[256], szPath[256], szRes[16];
	int sz = 0, res = 0;
	unsigned short sPort;
	bool needClose = false;

	const char* szPostHdr = soap_post_hdr;
	char* szData = (char*)mir_alloc(4096);
	char* szReq = NULL;

	parseURL(szUrl, szHost, &sPort, szPath);

	if (sPort != sConnPort || _stricmp(szHost, szConnHost))
		closeRouterConnection();
	else
		validateSocket();

	while(true)
	{
		retryCount = 0;
		switch(reqtype)
		{
		case DeviceGetReq:
			sz = mir_snprintf (szData, 4096, xml_get_hdr, szPath, szHost, sPort);
			break;

		case ControlAction:
			{
				char szData1[1024];

				szReq = mir_strdup(szResult);
				sz = mir_snprintf (szData1, SIZEOF(szData1),
					soap_action, szActionName, szDev, szReq, szActionName);

				sz = mir_snprintf (szData, 4096,
					szPostHdr, szPath, szHost, sPort,
					sz, szDev, szActionName, szData1);
			}
			break;

		case ControlQuery:
			{
				char szData1[1024];

				sz = mir_snprintf (szData1, SIZEOF(szData1),
					soap_query, szActionName);

				sz = mir_snprintf (szData, 4096,
					szPostHdr, szPath, szHost, sPort,
					sz, "urn:schemas-upnp-org:control-1-0", "QueryStateVariable", szData1);
			}
			break;
		}
		szResult[0] = 0;
		{
			static const TIMEVAL tv = { 6, 0 };
			static unsigned ttl = 4;
			static u_long mode = 1;
			fd_set rfd, wfd, efd;
			SOCKADDR_IN enetaddr;

retrycon:
			if (sock == INVALID_SOCKET)
			{
				sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

				enetaddr.sin_family = AF_INET;
				enetaddr.sin_port = htons(sPort);
				enetaddr.sin_addr.s_addr = inet_addr(szHost);

				// Resolve host name if needed
				if (enetaddr.sin_addr.s_addr == INADDR_NONE)
				{
					PHOSTENT he = gethostbyname(szHost);
					if (he)
						enetaddr.sin_addr.s_addr = *(unsigned*)he->h_addr_list[0];
				}

				NetlibLogf(NULL, "UPnP HTTP connection Host: %s Port: %u", szHost, sPort);

				FD_ZERO(&rfd); FD_ZERO(&wfd); FD_ZERO(&efd);
				FD_SET(sock, &rfd); FD_SET(sock, &wfd); FD_SET(sock, &efd);

				// Limit the scope of the connection (does not work for
				setsockopt(sock, IPPROTO_IP, IP_TTL, (char *)&ttl, sizeof(unsigned));

				// Put socket into non-blocking mode for timeout on connect
				ioctlsocket(sock, FIONBIO, &mode);

				// Connect to the remote host
				if (connect(sock, (SOCKADDR*)&enetaddr, sizeof(enetaddr)) == SOCKET_ERROR)
				{
					int err = WSAGetLastError();

					// Socket connection failed
					if (err != WSAEWOULDBLOCK)
					{
						closeRouterConnection();
						NetlibLogf(NULL, "UPnP connect failed %d", err);
						break;
					}
					// Wait for socket to connect
					else if (select(1, &rfd, &wfd, &efd, &tv) != 1)
					{
						closeRouterConnection();
						NetlibLogf(NULL, "UPnP connect timeout");
						break;
					}
					else if (!FD_ISSET(sock, &wfd))
					{
						closeRouterConnection();
						NetlibLogf(NULL, "UPnP connect failed");
						break;
					}
				}
				strcpy(szConnHost, szHost); sConnPort = sPort;
			}

			if (send(sock, szData, sz, 0) != SOCKET_ERROR)
			{
				char *hdrend = NULL;
				int acksz = 0, pktsz = 0;

				if (szActionName == NULL)
				{
					int len = sizeof(locIP);
					getsockname(sock, (SOCKADDR*)&locIP, &len);
					if (locIP.sin_addr.S_un.S_addr == 0x0100007f)
					{
						struct hostent *he;

						gethostname(szPath, sizeof(szPath));
						he = gethostbyname(szPath);
						if (he != NULL)
							locIP.sin_addr.S_un.S_addr = *(PDWORD)he->h_addr_list[0];
					}
				}

				LongLog(szData);
				sz = 0;
				while(true)
				{
					int bytesRecv;

					FD_ZERO(&rfd);
					FD_SET(sock, &rfd);

					// Wait for the next packet
					if (select(1, &rfd, NULL, NULL, &tv) != 1)
					{
						closeRouterConnection();
						NetlibLogf(NULL, "UPnP recieve timeout");
						break;
					}

					//
					bytesRecv = recv(sock, &szResult[sz], resSize-sz, 0);

					// Connection closed or aborted, all data received
					if (bytesRecv == 0 || bytesRecv == SOCKET_ERROR)
					{
						closeRouterConnection();
						if ((bytesRecv == SOCKET_ERROR || sz == 0) && retryCount < 2)
						{
							++retryCount;
							goto retrycon;
						}
						break;
					}

					sz += bytesRecv;

					// Insert null terminator to use string functions
					if (sz >= (resSize-1))
					{
						szResult[resSize-1] = 0;
						break;
					}
					else
						szResult[sz] = 0;

					// HTTP header found?
					if (hdrend == NULL)
					{
						// Find HTTP header end
						hdrend = strstr(szResult, "\r\n\r\n");
						if (hdrend == NULL)
						{
							hdrend = strstr(szResult, "\n\n");
							if (hdrend) hdrend += 2;
						}

						else
							hdrend += 4;

						if (hdrend != NULL)
						{
							// Get packet size if provided
							if (txtParseParam(szResult, NULL, "Content-Length:", "\n", szRes, sizeof(szRes))  ||
								txtParseParam(szResult, NULL, "CONTENT-LENGTH:", "\n", szRes, sizeof(szRes)))
							{
								// Add size of HTTP header to the packet size to compute full transmission size
								pktsz = atol(ltrimp(szRes)) + (hdrend - szResult);
							}
							// Get encoding type if provided
							else if (txtParseParam(szResult, NULL, "Transfer-Encoding:", "\n", szRes, sizeof(szRes)))
							{
								if (_stricmp(lrtrimp(szRes), "Chunked") == 0)
									acksz = hdrend - szResult;
							}
							if (txtParseParam(szResult, NULL, "Connection:", "\n", szRes, sizeof(szRes)))
							{
								needClose = (_stricmp(lrtrimp(szRes), "close") == 0);
							}
						}
					}

					// Content-Length bytes reached, all data received
					if (sz >= pktsz && pktsz != 0)
					{
						szResult[pktsz] = 0;
						break;
					}

					// Chunked encoding processing
					if (sz > acksz && acksz != 0)
					{
retry:
						// Parse out chunk size
						char* data = szResult + acksz;
						char* peol1 = data == hdrend ? data - 1 : strchr(data, '\n');
						if (peol1 != NULL)
						{
							char *peol2 = strchr(++peol1, '\n');
							if (peol2 != NULL)
							{
								// Get chunk size
								int chunkBytes = strtol(peol1, NULL, 16);
								acksz += chunkBytes;
								peol2++;

								memmove(data, peol2, strlen(peol2) + 1);
								sz -= peol2 - data;

								// Last chunk, all data received
								if (chunkBytes == 0) break;
								if (sz > acksz) goto retry;
							}
						}
					}
				}
				LongLog(szResult);
			}
			else
			{
				if (retryCount < 2)
				{
					closeRouterConnection();
					++retryCount;
					goto retrycon;
				}
				else
					NetlibLogf(NULL, "UPnP send failed %d", WSAGetLastError());
			}
		}
		txtParseParam(szResult, "HTTP", " ", " ", szRes, sizeof(szRes));
		res = atol(szRes);
		if (szActionName != NULL && res == 405 && szPostHdr == soap_post_hdr)
			szPostHdr = soap_post_hdr_m;
		else
			break;
	}

	if (needClose)
		closeRouterConnection();

	mir_free(szData);
	mir_free(szReq);
	return res;
}