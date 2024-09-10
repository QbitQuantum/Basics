void CClient::UserPortCommand(CString& sLine) {
	const CString sCommand = sLine.Token(0);

	if (sCommand.Equals("LISTPORTS")) {
		CTable Table;
		Table.AddColumn("Port");
		Table.AddColumn("BindHost");
		Table.AddColumn("SSL");
		Table.AddColumn("Proto");
		Table.AddColumn("IRC/Web");

		vector<CListener*>::const_iterator it;
		const vector<CListener*>& vpListeners = CZNC::Get().GetListeners();

		for (it = vpListeners.begin(); it < vpListeners.end(); ++it) {
			Table.AddRow();
			Table.SetCell("Port", CString((*it)->GetPort()));
			Table.SetCell("BindHost", ((*it)->GetBindHost().empty() ? CString("*") : (*it)->GetBindHost()));
			Table.SetCell("SSL", CString((*it)->IsSSL()));

			EAddrType eAddr = (*it)->GetAddrType();
			Table.SetCell("Proto", (eAddr == ADDR_ALL ? "All" : (eAddr == ADDR_IPV4ONLY ? "IPv4" : "IPv6")));

			CListener::EAcceptType eAccept = (*it)->GetAcceptType();
			Table.SetCell("IRC/Web", (eAccept == CListener::ACCEPT_ALL ? "All" : (eAccept == CListener::ACCEPT_IRC ? "IRC" : "Web")));
		}

		PutStatus(Table);

		return;
	}

	CString sPort = sLine.Token(1);
	CString sAddr = sLine.Token(2);
	EAddrType eAddr = ADDR_ALL;

	if (sAddr.Equals("IPV4")) {
		eAddr = ADDR_IPV4ONLY;
	} else if (sAddr.Equals("IPV6")) {
		eAddr = ADDR_IPV6ONLY;
	} else if (sAddr.Equals("ALL")) {
		eAddr = ADDR_ALL;
	} else {
		sAddr.clear();
	}

	unsigned short uPort = sPort.ToUShort();

	if (sCommand.Equals("ADDPORT")) {
		CListener::EAcceptType eAccept = CListener::ACCEPT_ALL;
		CString sAccept = sLine.Token(3);

		if (sAccept.Equals("WEB")) {
			eAccept = CListener::ACCEPT_HTTP;
		} else if (sAccept.Equals("IRC")) {
			eAccept = CListener::ACCEPT_IRC;
		} else if (sAccept.Equals("ALL")) {
			eAccept = CListener::ACCEPT_ALL;
		} else {
			sAccept.clear();
		}

		if (sPort.empty() || sAddr.empty() || sAccept.empty()) {
			PutStatus("Usage: AddPort <[+]port> <ipv4|ipv6|all> <web|irc|all> [bindhost]");
		} else {
			bool bSSL = (sPort.Left(1).Equals("+"));
			const CString sBindHost = sLine.Token(4);

			CListener* pListener = new CListener(uPort, sBindHost, bSSL, eAddr, eAccept);

			if (!pListener->Listen()) {
				delete pListener;
				PutStatus("Unable to bind [" + CString(strerror(errno)) + "]");
			} else {
				if (CZNC::Get().AddListener(pListener))
					PutStatus("Port Added");
				else
					PutStatus("Error?!");
			}
		}
	} else if (sCommand.Equals("DELPORT")) {
		if (sPort.empty() || sAddr.empty()) {
			PutStatus("Usage: DelPort <port> <ipv4|ipv6|all> [bindhost]");
		} else {
			const CString sBindHost = sLine.Token(3);

			CListener* pListener = CZNC::Get().FindListener(uPort, sBindHost, eAddr);

			if (pListener) {
				CZNC::Get().DelListener(pListener);
				PutStatus("Deleted Port");
			} else {
				PutStatus("Unable to find a matching port");
			}
		}
	}
}