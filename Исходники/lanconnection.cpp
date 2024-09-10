	void CLANConnection::Run()
	{
		VERIFY(AfxSocketInit());

		// Socket erzeugen, falls noch nicht geschehen
		int nError;
		if (!CreateSocket(nError))
		{
			if (m_pListener)
			{
				m_pListener->OnSocketError(nError, this);
				m_pListener->OnConnectionLost(this);
			}
			return;
		}

		CAsyncSocket socket;
		ASSERT(m_hSocket != INVALID_SOCKET);
		socket.Attach(m_hSocket);

		// IP-Adresse und tatsächlichen Port ermitteln
		SOCKADDR_IN sockaddr;
		memset(&sockaddr, 0, sizeof(sockaddr));
		int nSockAddrLen = sizeof(SOCKADDR_IN);
		if (!socket.GetSockName((SOCKADDR *)&sockaddr, &nSockAddrLen)) goto error;

		m_nPort = ntohs(sockaddr.sin_port);
		m_dwIP = ntohl(sockaddr.sin_addr.S_un.S_addr);

		// main thread loop
		BYTE buf[LAN_BUFSIZE];
		while (!IsInterrupted())
		{
			// Senden
			{
			CReference<CLANMessage> message;
			if (message = GetNextMessage())
			{
				// Magic Number
				memcpy(buf, "BotE", 4);

				// Nachricht serialisieren
				CMemFile memFile(&buf[4], LAN_BUFSIZE - 4);
				CArchive ar(&memFile, CArchive::store);
				message->Serialize(ar);
				ar.Close();
				UINT nSize = memFile.GetPosition() + 4;
				memFile.Detach();

				// Empfänger setzen
				memset(&sockaddr, 0, sizeof(sockaddr));
				sockaddr.sin_family = AF_INET;
				sockaddr.sin_addr.S_un.S_addr = htonl(message->GetReceiverIP());
				sockaddr.sin_port = htons(message->GetReceiverPort());

				// Nachricht versenden, setzt bei Fehler m_bInterrupted
				if (!SendMessageTo(socket, message, buf, nSize, &sockaddr)) break;

				// Broadcast-Nachricht auch an den lokalen Host senden
				if (message->GetReceiverIP() == INADDR_BROADCAST)
				{
					sockaddr.sin_addr.S_un.S_addr = htonl(INADDR_LOOPBACK);
					if (!SendMessageTo(socket, message, buf, nSize, &sockaddr))
						break;
				}
			}
			}

			// Empfangen
			memset(&sockaddr, 0, sizeof(sockaddr));
			int nSockAddrLen = sizeof(sockaddr);
			int nCount = socket.ReceiveFrom(&buf, LAN_BUFSIZE, (SOCKADDR *)&sockaddr, &nSockAddrLen);
			if (nCount > 0)
			{
				// Magic Number prüfen
				if (memcmp(&buf, "BotE", 4) != 0) continue;

				// Nachricht deserialisieren
				CMemFile memFile(&buf[4], nCount - 4);
				CArchive ar(&memFile, CArchive::load);
				CReference<CLANMessage> message(new CLANMessage());
				message->Serialize(ar);
				ar.Close();
				memFile.Detach();

				// IP und Port des Absenders
				DWORD dwIP = ntohl(sockaddr.sin_addr.S_un.S_addr);
				UINT nPort = ntohs(sockaddr.sin_port);
				message->SetSenderIP(dwIP);
				message->SetSenderPort(nPort);

				// Ankunft einer Nachricht melden
				if (m_pListener) m_pListener->OnMessageReceived(message, this);
			}
			else if (nCount == 0)
			{
				// "Verbindung" wurde getrennt
				ASSERT(FALSE);
				break;
			}
			else if (nCount == SOCKET_ERROR)
			{
				int nError = socket.GetLastError();
				if (nError != WSAEWOULDBLOCK)
				{
					if (m_pListener) m_pListener->OnSocketError(nError, this);
					// WSAECONNRESET tritt auf, wenn wir zuvor eine Nachricht an eine Adresse gesendet
					// haben, an der kein Server läuft; Thread dann nicht abbrechen
					if (nError != WSAECONNRESET)
					{
						__super::Interrupt();
						break;
					}
				}
			}

			Sleep(50);
		}

		// verbleibende Nachrichten löschen
		{
			CReference<CLANMessage> message;
			while (message = GetNextMessage())
			{
				if (m_pListener) m_pListener->OnMessageDiscarded(message, this);
			}
		}

		// socket schließen, Thread beenden
		socket.Close();
		m_hSocket = INVALID_SOCKET;
		if (m_bSendLost && m_pListener) m_pListener->OnConnectionLost(this);
		return;

error:
		if (m_pListener) m_pListener->OnSocketError(socket.GetLastError(), this);
		m_hSocket = INVALID_SOCKET;
		if (m_pListener) m_pListener->OnConnectionLost(this);
	}