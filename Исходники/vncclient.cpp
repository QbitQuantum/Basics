BOOL
vncClientThread::InitAuthenticate()
{
	// Retrieve the local password
	char password[MAXPWLEN];
	m_server->GetPassword(password);
	vncPasswd::ToText plain(password);

	// Verify the peer host name against the AuthHosts string
	vncServer::AcceptQueryReject verified;
	if (m_auth) {
		verified = vncServer::aqrAccept;
	} else {
		verified = m_server->VerifyHost(m_socket->GetPeerName());
	}
	
	// If necessary, query the connection with a timed dialog
	if (verified == vncServer::aqrQuery) {
		vncAcceptDialog *acceptDlg = new vncAcceptDialog(m_server->QueryTimeout(), m_socket->GetPeerName());
		if ((acceptDlg == 0) || (!(acceptDlg->DoDialog())))
			verified = vncServer::aqrReject;
	}
	if (verified == vncServer::aqrReject) {
		CARD32 auth_val = Swap32IfLE(rfbConnFailed);
		char *errmsg = "Your connection has been rejected.";
		CARD32 errlen = Swap32IfLE(strlen(errmsg));
		if (!m_socket->SendExact((char *)&auth_val, sizeof(auth_val)))
			return FALSE;
		if (!m_socket->SendExact((char *)&errlen, sizeof(errlen)))
			return FALSE;
		m_socket->SendExact(errmsg, strlen(errmsg));
		return FALSE;
	}

	// By default we disallow passwordless workstations!
	if ((strlen(plain) == 0) && m_server->AuthRequired())
	{
		vnclog.Print(LL_CONNERR, VNCLOG("no password specified for server - client rejected\n"));

		// Send an error message to the client
		CARD32 auth_val = Swap32IfLE(rfbConnFailed);
		char *errmsg =
			"This server does not have a valid password enabled.  "
			"Until a password is set, incoming connections cannot be accepted.";
		CARD32 errlen = Swap32IfLE(strlen(errmsg));

		if (!m_socket->SendExact((char *)&auth_val, sizeof(auth_val)))
			return FALSE;
		if (!m_socket->SendExact((char *)&errlen, sizeof(errlen)))
			return FALSE;
		m_socket->SendExact(errmsg, strlen(errmsg));

		return FALSE;
	}

	// By default we filter out local loop connections, because they're pointless
	if (!m_server->LoopbackOk())
	{
		char *localname = strdup(m_socket->GetSockName());
		char *remotename = strdup(m_socket->GetPeerName());

		// Check that the local & remote names are different!
		if ((localname != NULL) && (remotename != NULL))
		{
			BOOL ok = strcmp(localname, remotename) != 0;

			if (localname != NULL)
				free(localname);

			if (remotename != NULL)
				free(remotename);

			if (!ok)
			{
				vnclog.Print(LL_CONNERR, VNCLOG("loopback connection attempted - client rejected\n"));
				
				// Send an error message to the client
				CARD32 auth_val = Swap32IfLE(rfbConnFailed);
				char *errmsg = "Local loop-back connections are disabled.";
				CARD32 errlen = Swap32IfLE(strlen(errmsg));

				if (!m_socket->SendExact((char *)&auth_val, sizeof(auth_val)))
					return FALSE;
				if (!m_socket->SendExact((char *)&errlen, sizeof(errlen)))
					return FALSE;
				m_socket->SendExact(errmsg, strlen(errmsg));

				return FALSE;
			}
		}
	}

	// Authenticate the connection, if required
	if (m_auth || (strlen(plain) == 0))
	{
		// Send no-auth-required message
		CARD32 auth_val = Swap32IfLE(rfbNoAuth);
		if (!m_socket->SendExact((char *)&auth_val, sizeof(auth_val)))
			return FALSE;
	}
	else
	{
		// Send auth-required message
		CARD32 auth_val = Swap32IfLE(rfbVncAuth);
		if (!m_socket->SendExact((char *)&auth_val, sizeof(auth_val)))
			return FALSE;

		BOOL auth_ok = TRUE;
		{
			// Now create a 16-byte challenge
			char challenge[16];
			vncRandomBytes((BYTE *)&challenge);

			// Send the challenge to the client
			if (!m_socket->SendExact(challenge, sizeof(challenge)))
				return FALSE;

			// Read the response
			char response[16];
			if (!m_socket->ReadExact(response, sizeof(response)))\
				return FALSE;

			// Encrypt the challenge bytes
			vncEncryptBytes((BYTE *)&challenge, plain);

			// Compare them to the response
			for (int i=0; i<sizeof(challenge); i++)
			{
				if (challenge[i] != response[i])
				{
					auth_ok = FALSE;
					break;
				}
			}
		}

		// Did the authentication work?
		CARD32 authmsg;
		if (!auth_ok)
		{
			vnclog.Print(LL_CONNERR, VNCLOG("authentication failed\n"));

			authmsg = Swap32IfLE(rfbVncAuthFailed);
			m_socket->SendExact((char *)&authmsg, sizeof(authmsg));
			return FALSE;
		}
		else
		{
			// Tell the client we're ok
			authmsg = Swap32IfLE(rfbVncAuthOK);
			if (!m_socket->SendExact((char *)&authmsg, sizeof(authmsg)))
				return FALSE;
		}
	}

	// Read the client's initialisation message
	rfbClientInitMsg client_ini;
	if (!m_socket->ReadExact((char *)&client_ini, sz_rfbClientInitMsg))
		return FALSE;

	// If the client wishes to have exclusive access then remove other clients
	if (!client_ini.shared && !m_shared)
	{
		// Which client takes priority, existing or incoming?
		if (m_server->ConnectPriority() < 1)
		{
			// Incoming
			vnclog.Print(LL_INTINFO, VNCLOG("non-shared connection - disconnecting old clients\n"));
			m_server->KillAuthClients();
		} else if (m_server->ConnectPriority() > 1)
		{
			// Existing
			if (m_server->AuthClientCount() > 0)
			{
				vnclog.Print(LL_CLIENTS, VNCLOG("connections already exist - client rejected\n"));
				return FALSE;
			}
		}
	}

	// Tell the server that this client is ok
	return m_server->Authenticated(m_client->GetClientId());
}