	virtual void OnModCommand(const CString& sCommand)
	{
		CString sCom = sCommand.Token(0);
		CString sArgs = sCommand.Token(1, true);

		if (sCom.Equals("chat") && !sArgs.empty()) {
			CString sNick = "(s)" + sArgs;
			set<CSocket*>::const_iterator it;
			for (it = BeginSockets(); it != EndSockets(); ++it) {
				CSChatSock *pSock = (CSChatSock*) *it;

				if (pSock->GetChatNick().Equals(sNick)) {
					PutModule("Already Connected to [" + sArgs + "]");
					return;
				}
			}

			CSChatSock *pSock = new CSChatSock(this, sNick);
			pSock->SetCipher("HIGH");
			pSock->SetPemLocation(m_sPemFile);

			u_short iPort = m_pManager->ListenRand(pSock->GetSockName() + "::LISTENER",
					m_pUser->GetLocalDCCIP(), true, SOMAXCONN, pSock, 60);

			if (iPort == 0) {
				PutModule("Failed to start chat!");
				return;
			}

			stringstream s;
			s << "PRIVMSG " << sArgs << " :\001";
			s << "DCC SCHAT chat ";
			s << CUtils::GetLongIP(m_pUser->GetLocalDCCIP());
			s << " " << iPort << "\001";

			PutIRC(s.str());

		} else if (sCom.Equals("list")) {
			CTable Table;
			Table.AddColumn("Nick");
			Table.AddColumn("Created");
			Table.AddColumn("Host");
			Table.AddColumn("Port");
			Table.AddColumn("Status");
			Table.AddColumn("Cipher");

			set<CSocket*>::const_iterator it;
			for (it = BeginSockets(); it != EndSockets(); ++it) {
				Table.AddRow();

				CSChatSock *pSock = (CSChatSock*) *it;
				Table.SetCell("Nick", pSock->GetChatNick());
				unsigned long long iStartTime = pSock->GetStartTime();
				time_t iTime = iStartTime / 1000;
				char *pTime = ctime(&iTime);
				if (pTime) {
					CString sTime = pTime;
					sTime.Trim();
					Table.SetCell("Created", sTime);
				}

				if (pSock->GetType() != CSChatSock::LISTENER) {
					Table.SetCell("Status", "Established");
					Table.SetCell("Host", pSock->GetRemoteIP());
					Table.SetCell("Port", CString(pSock->GetRemotePort()));
					SSL_SESSION *pSession = pSock->GetSSLSession();
					if (pSession && pSession->cipher && pSession->cipher->name)
						Table.SetCell("Cipher", pSession->cipher->name);

				} else {
					Table.SetCell("Status", "Waiting");
					Table.SetCell("Port", CString(pSock->GetLocalPort()));
				}
			}
			if (Table.size()) {
				PutModule(Table);
			} else
				PutModule("No SDCCs currently in session");

		} else if (sCom.Equals("close")) {
			if (!sArgs.Equals("(s)", false, 3))
				sArgs = "(s)" + sArgs;

			set<CSocket*>::const_iterator it;
			for (it = BeginSockets(); it != EndSockets(); ++it) {
				CSChatSock *pSock = (CSChatSock*) *it;

				if (sArgs.Equals(pSock->GetChatNick())) {
					pSock->Close();
					return;
				}
			}
			PutModule("No Such Chat [" + sArgs + "]");
		} else if (sCom.Equals("showsocks") && m_pUser->IsAdmin()) {
			CTable Table;
			Table.AddColumn("SockName");
			Table.AddColumn("Created");
			Table.AddColumn("LocalIP:Port");
			Table.AddColumn("RemoteIP:Port");
			Table.AddColumn("Type");
			Table.AddColumn("Cipher");

			set<CSocket*>::const_iterator it;
			for (it = BeginSockets(); it != EndSockets(); ++it) {
				Table.AddRow();
				Csock *pSock = *it;
				Table.SetCell("SockName", pSock->GetSockName());
				unsigned long long iStartTime = pSock->GetStartTime();
				time_t iTime = iStartTime / 1000;
				char *pTime = ctime(&iTime);
				if (pTime) {
					CString sTime = pTime;
					sTime.Trim();
					Table.SetCell("Created", sTime);
				}

				if (pSock->GetType() != Csock::LISTENER) {
					if (pSock->GetType() == Csock::OUTBOUND)
						Table.SetCell("Type", "Outbound");
					else
						Table.SetCell("Type", "Inbound");
					Table.SetCell("LocalIP:Port", pSock->GetLocalIP() + ":" +
							CString(pSock->GetLocalPort()));
					Table.SetCell("RemoteIP:Port", pSock->GetRemoteIP() + ":" +
							CString(pSock->GetRemotePort()));
					SSL_SESSION *pSession = pSock->GetSSLSession();
					if (pSession && pSession->cipher && pSession->cipher->name)
						Table.SetCell("Cipher", pSession->cipher->name);
					else
						Table.SetCell("Cipher", "None");

				} else {
					Table.SetCell("Type", "Listener");
					Table.SetCell("LocalIP:Port", pSock->GetLocalIP() +
							":" + CString(pSock->GetLocalPort()));
					Table.SetCell("RemoteIP:Port", "0.0.0.0:0");
				}
			}
			if (Table.size())
				PutModule(Table);
			else
				PutModule("Error Finding Sockets");

		} else if (sCom.Equals("help")) {
			PutModule("Commands are:");
			PutModule("    help           - This text.");
			PutModule("    chat <nick>    - Chat a nick.");
			PutModule("    list           - List current chats.");
			PutModule("    close <nick>   - Close a chat to a nick.");
			PutModule("    timers         - Shows related timers.");
			if (m_pUser->IsAdmin()) {
				PutModule("    showsocks      - Shows all socket connections.");
			}
		} else if (sCom.Equals("timers"))
			ListTimers();
		else
			PutModule("Unknown command [" + sCom + "] [" + sArgs + "]");
	}