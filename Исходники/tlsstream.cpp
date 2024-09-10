/**
 * Constructor for the TlsStream class.
 *
 * @param role The role of the client.
 * @param sslContext The SSL context for the client.
 */
TlsStream::TlsStream(const Socket::Ptr& socket, const String& hostname, ConnectionRole role, const boost::shared_ptr<SSL_CTX>& sslContext)
	: SocketEvents(socket, this), m_Eof(false), m_HandshakeOK(false), m_VerifyOK(true), m_ErrorCode(0),
	  m_ErrorOccurred(false),  m_Socket(socket), m_Role(role), m_SendQ(new FIFO()), m_RecvQ(new FIFO()),
	  m_CurrentAction(TlsActionNone), m_Retry(false), m_Shutdown(false)
{
	std::ostringstream msgbuf;
	char errbuf[120];

	m_SSL = boost::shared_ptr<SSL>(SSL_new(sslContext.get()), SSL_free);

	if (!m_SSL) {
		msgbuf << "SSL_new() failed with code " << ERR_peek_error() << ", \"" << ERR_error_string(ERR_peek_error(), errbuf) << "\"";
		Log(LogCritical, "TlsStream", msgbuf.str());

		BOOST_THROW_EXCEPTION(openssl_error()
			<< boost::errinfo_api_function("SSL_new")
			<< errinfo_openssl_error(ERR_peek_error()));
	}

	if (!m_SSLIndexInitialized) {
		m_SSLIndex = SSL_get_ex_new_index(0, const_cast<char *>("TlsStream"), NULL, NULL, NULL);
		m_SSLIndexInitialized = true;
	}

	SSL_set_ex_data(m_SSL.get(), m_SSLIndex, this);

	SSL_set_verify(m_SSL.get(), SSL_VERIFY_PEER | SSL_VERIFY_CLIENT_ONCE, &TlsStream::ValidateCertificate);

	socket->MakeNonBlocking();

	SSL_set_fd(m_SSL.get(), socket->GetFD());

	if (m_Role == RoleServer)
		SSL_set_accept_state(m_SSL.get());
	else {
#ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
		if (!hostname.IsEmpty())
			SSL_set_tlsext_host_name(m_SSL.get(), hostname.CStr());
#endif /* SSL_CTRL_SET_TLSEXT_HOSTNAME */

		SSL_set_connect_state(m_SSL.get());
	}
}