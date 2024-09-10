/**
 * Processes a new client connection.
 *
 * @param client The new client.
 */
void ApiListener::NewClientHandlerInternal(const Socket::Ptr& client, const String& hostname, ConnectionRole role)
{
	CONTEXT("Handling new API client connection");

	String conninfo;

	if (role == RoleClient)
		conninfo = "to";
	else
		conninfo = "from";

	conninfo += " " + client->GetPeerAddress();

	TlsStream::Ptr tlsStream;

	{
		ObjectLock olock(this);
		try {
			tlsStream = new TlsStream(client, hostname, role, m_SSLContext);
		} catch (const std::exception&) {
			Log(LogCritical, "ApiListener")
			    << "Cannot create TLS stream from client connection (" << conninfo << ")";
			return;
		}
	}

	try {
		tlsStream->Handshake();
	} catch (const std::exception& ex) {
		Log(LogCritical, "ApiListener")
		    << "Client TLS handshake failed (" << conninfo << ")";
		return;
	}

	boost::shared_ptr<X509> cert = tlsStream->GetPeerCertificate();
	String identity;
	Endpoint::Ptr endpoint;
	bool verify_ok = false;

	if (cert) {
		try {
			identity = GetCertificateCN(cert);
		} catch (const std::exception&) {
			Log(LogCritical, "ApiListener")
			    << "Cannot get certificate common name from cert path: '" << GetCertPath() << "'.";
			return;
		}

		verify_ok = tlsStream->IsVerifyOK();
		if (!hostname.IsEmpty()) {
			if (identity != hostname) {
				Log(LogWarning, "ApiListener")
					<< "Unexpected certificate common name while connecting to endpoint '"
				    << hostname << "': got '" << identity << "'";
				return;
			} else if (!verify_ok) {
				Log(LogWarning, "ApiListener")
					<< "Certificate validation failed for endpoint '" << hostname
					<< "': " << tlsStream->GetVerifyError();
				return;
			}
		}

		if (verify_ok)
			endpoint = Endpoint::GetByName(identity);

		{
			Log log(LogInformation, "ApiListener");

			log << "New client connection for identity '" << identity << "' " << conninfo;

			if (!verify_ok)
				log << " (certificate validation failed: " << tlsStream->GetVerifyError() << ")";
			else if (!endpoint)
				log << " (no Endpoint object found for identity)";
		}
	} else {
		Log(LogInformation, "ApiListener")
		    << "New client connection " << conninfo << " (no client certificate)";
	}

	ClientType ctype;

	if (role == RoleClient) {
		Dictionary::Ptr message = new Dictionary();
		message->Set("jsonrpc", "2.0");
		message->Set("method", "icinga::Hello");
		message->Set("params", new Dictionary());
		JsonRpc::SendMessage(tlsStream, message);
		ctype = ClientJsonRpc;
	} else {
		tlsStream->WaitForData(5);

		if (!tlsStream->IsDataAvailable()) {
			Log(LogWarning, "ApiListener")
			    << "No data received on new API connection for identity '" << identity << "'. Ensure that the remote endpoints are properly configured in a cluster setup.";
			return;
		}

		char firstByte;
		tlsStream->Peek(&firstByte, 1, false);

		if (firstByte >= '0' && firstByte <= '9')
			ctype = ClientJsonRpc;
		else
			ctype = ClientHttp;
	}

	if (ctype == ClientJsonRpc) {
		Log(LogNotice, "ApiListener", "New JSON-RPC client");

		JsonRpcConnection::Ptr aclient = new JsonRpcConnection(identity, verify_ok, tlsStream, role);
		aclient->Start();

		if (endpoint) {
			bool needSync = !endpoint->GetConnected();

			endpoint->AddClient(aclient);

			m_SyncQueue.Enqueue(boost::bind(&ApiListener::SyncClient, this, aclient, endpoint, needSync));
		} else
			AddAnonymousClient(aclient);
	} else {
		Log(LogNotice, "ApiListener", "New HTTP client");

		HttpServerConnection::Ptr aclient = new HttpServerConnection(identity, verify_ok, tlsStream);
		aclient->Start();
		AddHttpClient(aclient);
	}
}